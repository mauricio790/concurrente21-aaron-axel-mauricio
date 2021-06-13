// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <signal.h>

#include "GoldbachWebApp.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "WebServer.hpp"
#include "Consumer.hpp"


const char* const usage =
  "Usage: webserv [port] [max_connections]\n"
  "\n"
  "  port             Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  max_connections  Maximum number of allowed client connections\n";


WebServer::WebServer() {
}

WebServer::~WebServer() {
}
/**
 * @brief This is a singleton class, this method returns the only instance of this class 
 * @return Returns the only WebServer instance
 */
WebServer& WebServer::getInstance(){
  static WebServer webServer;
  return webServer;
}
/**
 * @brief This method calls HttpServer::stop() to stop all threads from consuming
 */
void WebServer::stopServer(){
   this->stop(max_connections);
}

/**
 * @brief This method is called when a SIGINT or SIGTERM signal is raised
 */
void WebServer::signalHandler(int signal){
  if(signal == SIGINT || signal == SIGTERM){
    WebServer::getInstance().stopServer();
    WebServer::getInstance().stopListening();
    exit(0);
  }
}

int WebServer::start(int argc, char* argv[]) {
  try {
   
    signal(SIGINT, signalHandler);
    if (this->analyzeArguments(argc, argv)) {
      // TODO(you) Handle signal 2 (SIGINT) and 15 (SIGTERM), see man signal
      // Signal handler should call WebServer::stopListening(), send stop
      // conditions and wait for all secondary threads that it created
      
      this->listenForConnections(this->port);
      this->startThreads(max_connections);
      const NetworkAddress& address = this->getNetworkAddress();
      std::cout << "web server listening on " << address.getIP()
        << " port " << address.getPort() << "...\n";
      this->acceptAllConnections();
      
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

bool WebServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 3) {
    this->port = argv[1];
    sscanf(argv[2],"%i",&max_connections);
    printf("max connections: %i\n",this->max_connections);
  }

  return true;
}

bool WebServer::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  GoldbachWebApp Goldbach_WebApp;
  // Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  std::cout << "connection established with client " << address.getIP()
    << " port " << address.getPort() << std::endl;

  // Print HTTP request
  std::cout << "  " << httpRequest.getMethod()
    << ' ' << httpRequest.getURI()
    << ' ' << httpRequest.getHttpVersion() << std::endl;

  return Goldbach_WebApp.route(httpRequest, httpResponse);
}