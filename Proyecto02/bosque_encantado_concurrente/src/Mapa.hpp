#ifndef MAPA_H
#define MAPA_H

#include<string>
#include<fstream>

class Mapa{
 public:
  size_t filas;
  size_t columnas;
  size_t area;
  std::string mapa;
  std::string rutaSalida;
  

  Mapa() = delete;
  explicit Mapa(std::string ruta, std::string rutaSalida);
  ~Mapa();
  std::string obtenerVecinos(const size_t &i);
  void escribirNuevoMapa(size_t noche);
};

#endif
