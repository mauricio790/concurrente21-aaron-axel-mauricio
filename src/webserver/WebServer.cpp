// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "GoldbachWebApp.hpp"
#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "WebServer.hpp"

const char* const usage =
  "Usage: webserv [port] [max_connections]\n"
  "\n"
  "  port             Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  max_connections  Maximum number of allowed client connections\n";

// TODO(you) Make WebServer a singleton class. See the Log class -- Done
WebServer::WebServer() {
}

WebServer::~WebServer() {
}

WebServer& WebServer::getInstance(){
  static WebServer webServer;
  return webServer;
}


int WebServer::start(int argc, char* argv[]) {
  try {
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