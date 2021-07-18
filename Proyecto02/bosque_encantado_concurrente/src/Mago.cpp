#include "Mago.hpp"
#include "Hechizo.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <mpi.h>
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
    if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
      int rank = -1;
      MPI_Comm_rank (MPI_COMM_WORLD, &rank);

      int process_count = 0;
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);

      if (process_count <= 1) {
        std::vector<std::string> mapas;
        try{
          mapas = get_mapas();
        }catch(const std::runtime_error& error){
          std::cout << error.what() << std::endl;
          return 1;
        }
        Hechizo hechizo(num_threads);
        for (auto mapa : mapas) {
        hechizo.prepararHechizo(mapa);
        }
      } else { 
        std::cout << "Proceso: " << rank << std::endl;
        if (rank == 0) {
          this->send_maps();
        } else {
          this->receive_maps();
        }
      }
      MPI_Finalize();
    }
  } else {
      error = 1;
    }
  return error;
}

void Mago::receive_maps(){

}
void Mago::send_maps(){ 
  int TAG_REQUEST = 0;
  int TAG_LONG_ROUTE = 1;
  int TAG_ROUTE = 2;
  std::vector<std::string> mapas = get_mapas();
  size_t index_maps = 0;
  int process_request = -1;
  while (index_maps < mapas.size()) {
    //Solicitudes otros porcesos
    MPI_Recv(&process_request, 1 , MPI_INT, MPI_ANY_SOURCE, TAG_REQUEST, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
   //longitud del string
  int32_t long_route = mapas[index_maps].length()  + 1;
  MPI_Send(&long_route, 1, MPI_INT32_T, process_request, TAG_LONG_ROUTE, MPI_COMM_WORLD);

  //String 
  MPI_Send(mapas[index_maps].c_str(), long_route, MPI_SIGNED_CHAR, process_request, TAG_ROUTE, MPI_COMM_WORLD);

  ++index_maps;
// Condicion de parada 
  int process_count = -1;
  int stop_condition = 0;
  MPI_Comm_size (MPI_COMM_WORLD,&process_count);

  for (int range = 1; range < process_count; ++range) {
    MPI_Recv (&process_request, 1, MPI_INT, MPI_ANY_SOURCE, TAG_REQUEST, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     MPI_Send(&stop_condition, 1, MPI_INT32_T, range, TAG_LONG_ROUTE, MPI_COMM_WORLD);
  }
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
