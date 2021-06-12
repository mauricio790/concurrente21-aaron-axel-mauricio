// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"
#include "Queue.hpp"



HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::startThreads(int max_connections) {
  
  // Create each consumer
  this->connectionHandlers.resize(max_connections);
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index] = new HttpConnectionHandler();
    assert(this->connectionHandlers[index]);
    this->connectionHandlers[index]->setConsumingQueue(&clients_queue);
  }
  // Start the simulation
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->startThread();
  }

}

void HttpServer::stop(int max_connections){
  //Send stop conditions
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->sendStopCondition();
  }
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->waitToFinish();
  }
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop -- Done
  clients_queue.push(client);
  //Listo
}
