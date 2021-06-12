// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization



#ifdef WEBSERVER

#include "WebServer.hpp"
#include <csignal>




int main(int argc, char* argv[]) {
  
  int retorno = WebServer::getInstance().start(argc, argv);
  return retorno;

}

#endif  // WEBSERVER
