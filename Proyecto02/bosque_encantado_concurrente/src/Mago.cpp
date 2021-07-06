#include "Mago.hpp"
#include "Hechizo.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
/**
 * @brief Inicia el programa y verifica argumentos
 * @param argc cantidad de argumentos en la entrada
 * @param argv argumentos
 * @return codigo de error
 * */ 
int Mago::start(int argc, char* argv[]) {
  int error = 0;
  std::string linea;
  if (analyze_arguments(argc, argv)) {
    std::vector<std::string> mapas;
    try{
      mapas = get_mapas();
    }catch(const std::runtime_error& error){
      std::cout << error.what() << std::endl;
      return 1;
    }
    Hechizo hechizo(num_threads);
    for (auto mapa : mapas) {
      hechizo.hechizar(mapa);
    }
  } else {
      error = 1;
    }
  return error;
}

/**
    *@brief recibe archivo con órdenes de trabajo y 
    *       las retorna en un std::vector<string> 
    *
**/
std::vector<std::string> Mago::get_mapas() {
  std::vector<std::string> mapas;
  std::ifstream order(job_order);
  if (order.is_open()) {
    std::string linea;
    while ((std::getline(order, linea))) {
      if (linea.length() > 0) {
        mapas.push_back(linea);
      }
    }
  } else {
      throw std::runtime_error("No se pudo abrir archivo");
    }
  return mapas;
}
/**
 * @brief Constructor de Mago
 * */ 
Mago::Mago() {
}
/**
 * @brief Destructor de Mago
 * */ 
Mago::~Mago() {
}
/**
 * @brief analiza los argumentos ingresados como parametro
 * @param argc cantidad de argumentos en la entrada
 * @param argv argumentos
 * @return codigo de error
 * */ 
int Mago::analyze_arguments(int argc, char* argv[]) {
  if (argc == 2) {
    job_order = argv[1];
    num_threads = 0;
    return 1;
  } else {
    if(argc == 3){
      job_order = argv[1];
      try{
        num_threads = std::stoi(argv[2]);
      }catch(std::exception const & e){
        std::cout << "Error: invalid number of threads\n" << std::endl;
        return 0;
      }
      return 1;
    }
  }
  return 0;
}
