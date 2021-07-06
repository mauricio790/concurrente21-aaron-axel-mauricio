#ifndef HECHIZO_H
#define HECHIZO_H

#include "Mapa.hpp"
#include <string>
#include <iostream>
#include <fstream>

#define ARBOL 'a'
#define LAGO 'l'
#define PRADERA '-'

class Hechizo{
 public:
  std::ofstream salida;
  Hechizo();
  ~Hechizo();
   // crea un mapa y se deja la cantidad de medias noches
  void hechizar(std::string mapa);
  void hechizarMapa(Mapa& mapa, int medias_noches);
  char verificarReglas(Mapa& mapa, const size_t &i ,
  size_t cant_arboles, size_t cant_lagos);
  char verificarVecinos(Mapa& mapa, std::string prueba, size_t i);
 private:
  void escribirMapa(Mapa& mapa, size_t noche);
 protected:
};

#endif
