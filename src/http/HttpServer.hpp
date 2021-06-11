// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <vector>

#include "HttpConnectionHandler.hpp"
#include "TcpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Queue.hpp"

#include "common.hpp"


class HttpServer : public TcpServer {
  DISABLE_COPY(HttpServer);

 public:
  Queue <Socket> clients_queue;
  std::vector<HttpConnectionHandler*> connectionHandlers;
  
  int consumerDelay = 0;

protected:
  /// Lookup criteria for searching network information about this host
  struct addrinfo hints;

 public:
  /// Constructor
  HttpServer() = default;
  /// Destructor
  ~HttpServer();
  /// Infinetelly listen for client connection requests and accept all of them.
  /// For each accepted connection request, the virtual onConnectionAccepted()
  /// will be called. Inherited classes must override that method
  void listenForever(const char* port);
  void startThreads(const int* max_connections);
  virtual bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) = 0;
 
 protected:
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
  /// Called each time an HTTP request is received. Web server should analyze
  /// the request object and assemble a response with the response object.
  /// Finally send the response calling the httpResponse.send() method.
  /// @return true on success and the server will continue handling further
  /// HTTP requests, or false if server should stop accepting requests from
  /// this client (e.g: HTTP/1.0)
  
       
};

#endif  // HTTPSERVER_H
