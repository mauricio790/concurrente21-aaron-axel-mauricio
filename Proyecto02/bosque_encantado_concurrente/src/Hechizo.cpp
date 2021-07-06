#include "Hechizo.hpp"
#include <stdexcept>
#include <omp.h>
/**
 * @brief Constructor de Hechizo
 * */ 
Hechizo::Hechizo() {
}
/**
 * @brief Destructor de Hechizo
 * */ 
Hechizo::~Hechizo() {
}
/**
 * @brief Recibe una orden de trabajo y si puede extraer todos los datos del mapa
 * manda a realizar los cambios al mapa de ser necesario
 * @param order orden de trabajo
 * @return void
 * */
void Hechizo::hechizar(std::string order) {
  std::string ruta;
  int medias_noches = 1;
  std::ifstream archivo_mapa(order);
  size_t espacio = order.find(' ');
  if (espacio != std::string::npos) {
    ruta = order.substr(0, espacio);
    medias_noches = std::stoi(order.substr(espacio));
    medias_noches += 0;
  }

  // Crear archivo de salida y hechizar el mapa Hechizar(mapa)
  Mapa mapa("input/" + ruta);
  std::string extention = ".txt";
  mapa.rutaSalida = "output/" +
  ruta.substr(0, ruta.length() - extention.length()) + "-";
    this->hechizarMapa(mapa, medias_noches);
}
/**
 * @brief Se encarga de realizar todos los cambios necesarios al mapa durante todas las medias noches
 * @details Metodo concurrente, uso de OMP para paralelizar el trabajo
 * @param mapa Mapa inicial del que se partirá para realizar los cambios
 * @param medias_noches cantidad de noches que se verificará para el Mago
 * @return void
 * */
void Hechizo::hechizarMapa(Mapa &mapa, int medias_noches) {
  size_t noches;
  bool imprimirHechizos = medias_noches > 0;
  if (!imprimirHechizos) {
      noches = medias_noches * -1;
  } else {
      noches = medias_noches;
  }
  std::string nuevoMapa;
  int thread_count = omp_get_max_threads();
  for (size_t noche = 0; noche < noches; ++noche) {
        nuevoMapa = mapa.mapa;
#pragma omp parallel num_threads(thread_count) default(none) shared(mapa, nuevoMapa)
#pragma omp for schedule(static)
    for (size_t celda = 0; celda < mapa.area; ++celda) {
      std::string vecinos = mapa.obtenerVecinos(celda);
      nuevoMapa[celda] = this->verificarVecinos(mapa, vecinos, celda);
    }
    mapa.mapa = nuevoMapa;
    if (!imprimirHechizos) {
      if (noche == noches - 1) {
        this->escribirMapa(mapa, noche + 1);
      }
    } else {
        this->escribirMapa(mapa, noche + 1);
      }
  }
}
/**
 * @brief Crea un nuevo mapa de ser necesario en un archivo .txt
 * @param mapa Mapa inicial del que se partirá para realizar los cambios
 * @param medias_noches cantidad de noches que se verificará para el Mago
 * @return void
 * */
void Hechizo::escribirMapa(Mapa &mapa, size_t noche) {
  this->salida.open(mapa.rutaSalida + std::to_string(noche) + ".txt");
  std::string linea = "";
  for (size_t i = 0; i < mapa.area; i++) {
    linea += mapa.mapa[i];
    if ((i + 1) % mapa.columnas == 0) {
      this->salida << linea;
      linea = "";
      if (i != mapa.area - 1) {
        this->salida << std::endl;
        linea = "";
      }
    }
  }
  this->salida << std::endl;
  this->salida.close();
}
/**
 * @brief Verifica cuantos vecinos de cierta clase tiene un caracter en el mapa
 * @param mapa Mapa inicial del que se partirá para realizar los cambios
 * @param prueba string de los vecinos del caracter a verificar
 * @param i indice del caracter a verificar
 * @return caracter modificado
 * */
char Hechizo::verificarVecinos(Mapa &mapa, std::string prueba, size_t i) {
  size_t cant_arboles = 0;
  size_t cant_lagos = 0;
  for (size_t j = 0; j < prueba.length(); j++) {
    if (prueba[j] == ARBOL) {
      cant_arboles++;
    }
    if (prueba[j] == LAGO) {
      cant_lagos++;
    }
  }
  return verificarReglas(mapa, i, cant_arboles, cant_lagos);
}
/**
 * @brief Verifica las reglas del Mago, si alguna se cumple, el caracter se modifica
 * @param mapa Mapa inicial del que se partirá para realizar los cambios
 * @param i indice del caracter a verificar
 * @param cant_arboles cantidad de arboles vecinos al caracter a verificar
 * @param cant_lagos cantidad de lagos vecinos al caracter a verificar
 * @return caracter modificado
 * */
char Hechizo::verificarReglas(Mapa &mapa, const size_t &i,
size_t cant_arboles, size_t cant_lagos) {
    char bosque = mapa.mapa[i];
    if (mapa.mapa[i] == ARBOL && cant_lagos >= 4) {  // Inundacion
        bosque = 'l';
    }
    if (mapa.mapa[i] == LAGO && cant_lagos < 3) {  // Sequia
        bosque = '-';
    }
    if (mapa.mapa[i] == PRADERA && cant_arboles >= 3) {  // Reforestacion
        bosque = 'a';
    }
    if (mapa.mapa[i] == ARBOL && cant_arboles > 4) {  // Hacinamiento
        bosque = '-';
    }

    return bosque;
}
