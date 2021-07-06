// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization
#include "Mago.hpp"
/**
 * @brief Hace un llamado a Mago para iniciar el programa
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return codigo de error, si es 0 finaliza exitosamente
 * */ 
int main(int argc, char* argv[]) {
  Mago mago;
  return mago.start(argc, argv);
}

