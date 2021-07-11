// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include<unistd.h>

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

/**
 * @brief This method starts all the connections possible and assigns a reference to the consuming queue to each thread  
 * @param int max_connections holds the number of maximum connections of the server
 */
void HttpServer::startThreads(int max_connections) {
  // Create each consumer
  this->connectionHandlers.resize(max_connections);
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index] = new HttpConnectionHandler();
    assert(this->connectionHandlers[index]);
    this->connectionHandlers[index]->setConsumingQueue(&clients_queue);
  }

  this->calculators.resize(sysconf(_SC_NPROCESSORS_ONLN));
  for ( int index = 0; index < max_connections; ++index ) {
    this->calculators[index] = new Calculator();
    assert(this->calculators[index]);
    this->calculators[index]->setConsumingQueue(&tasks_queue);
    this->calculators[index]->setProducingQueue(&producedTasks_queue);
  }

  // Start consuming clients queue
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->startThread();
  }

  // Start consuming from tasks queue
  for ( int index = 0; index < sysconf(_SC_NPROCESSORS_ONLN); ++index ) {
    this->calculators[index]->startThread();
  }
}

/**
 * @brief This method stops all threads from consuming by sending stop conditions and waits for all secondary threads to stop  
 * @param int max_connections holds the number of maximum connections of the server
 */
void HttpServer::stop(int max_connections) {
  // Send stop conditions
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->sendStopCondition();
  }
  for ( int index = 0; index < max_connections; ++index ) {
    this->connectionHandlers[index]->waitToFinish();
  }
}

/**
 * @brief This method stores client connections into a Queue
 */
void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent.
  clients_queue.push(client);
  // Listo
}
