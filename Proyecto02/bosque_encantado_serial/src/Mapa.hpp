#ifndef MAPA_H
#define MAPA_H

#include<string>
#include<fstream>

class Mapa{
    public:
        Mapa() = delete;
        explicit Mapa(std::string ruta);
        ~Mapa();
        size_t filas;
        size_t columnas;
        size_t area;
        std::string mapa;
        std::string obtenerVecinos(const size_t &i);
};

#endif