// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "HttpServer.hpp"

#define DEFAULT_PORT "8080"


class WebServer : public HttpServer {
  DISABLE_COPY(WebServer);

 private:
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  int max_connections;

 public:
  /// Get access to the unique instance of this Singleton class
  static WebServer& getInstance();
  // Start
  int start(int argc, char* argv[]);
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  void stopServer();
  static void signalHandler(int signal);

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
 private:
  /// Constructor
  WebServer();
  /// Destructor
  ~WebServer();
};

#endif  // WEBSERVER_H
