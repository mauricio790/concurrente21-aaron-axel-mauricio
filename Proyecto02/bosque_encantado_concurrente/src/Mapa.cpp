#include "Mapa.hpp"

#include<iostream>
#include<cstring>
#include<stdexcept>
/**
 * @brief Constructor de mapa
 * @details Abre y extrae la informacion y los valores del archivo mapa
 * @param ruta La ruta donde se encuentra el mapa 
 * */
Mapa::Mapa(std::string ruta, std::string rutaSalida) {
  std::ifstream mapa_archivo;
  this->rutaSalida = rutaSalida;
  mapa_archivo.open(ruta);
  if (mapa_archivo.is_open()) {
    std::string linea;
    std::getline(mapa_archivo, linea);
    size_t espacio = linea.find(' ');
    this->filas = std::stoi(linea.substr(0, espacio));
    this->columnas = std::stoi(linea.substr(espacio + 1));
    this->area = filas*columnas;
    this->mapa = "";
    size_t lineas_leidas = 0;
    bool advertencia = false;
    while (std::getline(mapa_archivo, linea) && lineas_leidas < this->filas) {
      if (linea.length() == this->columnas) {
        if (linea.length() > this->columnas && !advertencia) {
          std::cout << ruta << " contiene lineas mas largas que lo establecido."
          << "Se omiten los caracteres restantes" << std::endl;
          advertencia = true;
        }
        mapa += linea;
        ++lineas_leidas;
      } else {
        throw std::runtime_error("línea inválida");
      }
    }
  } else {
    throw std::runtime_error("No se pudo abrir el mapa");
  }
}
/**
 * @brief Destructor de Mapa
 * */
Mapa::~Mapa() {
}
/**
 * @brief Extrae todos los vecinos de una celda dada
 * @param i indice de la posicion de la celda
 * @return todos los vecinos de la posicion solicitada en un string
 * */ 
std::string Mapa::obtenerVecinos(const size_t &i) {
    bool norte = false;
    bool sur = false;
    std::string vecinos = "";
    if (i >= columnas) {  // norte
        vecinos += mapa[i - columnas];
        norte = true;
    }
    if (i < area - columnas) {  // sur
        vecinos += mapa[i + columnas];
        sur = true;
    }
    if ((i + 1) % columnas != 0) {  // este
        vecinos += mapa[i + 1];
        if (norte) {  // NorEste
            vecinos += mapa[i - columnas + 1];
        }
        if (sur) {  // Sureste
            vecinos += mapa[i + columnas + 1];
        }
    }
    if ((i) % columnas != 0) {  // oeste
        vecinos += mapa[i - 1];
        if (norte) {  // Noroeste
            vecinos += mapa[i - columnas - 1];
        }
        if (sur) {  // Suroeste
            vecinos += mapa[i + columnas - 1];
        }
    }

    return vecinos;
}

/**
 * @brief Crea un nuevo mapa de ser necesario en un archivo .txt
 * @param mapa Mapa inicial del que se partirá para realizar los cambios
 * @param medias_noches cantidad de noches que se verificará para el Mago
 * @return void
 * */
void Mapa::escribirNuevoMapa(size_t noche) {
  std::ofstream salida; 
  salida.open(this->rutaSalida + std::to_string(noche) + ".txt");
  std::string linea = "";
  for (size_t i = 0; i < this->area; i++) {
    linea += this->mapa[i];
    if ((i + 1) % this->columnas == 0) {
      salida << linea;
      linea = "";
      if (i != this->area - 1) {
        salida << std::endl;
        linea = "";
      }
    }
  }
  salida << std::endl;
}
