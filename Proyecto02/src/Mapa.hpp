#ifndef MAPA_H
#define MAPA_H

#include<string>
#include<fstream>

class Mapa{
    public:
        Mapa() = delete;
        explicit Mapa(std::string ruta);
        ~Mapa();
    private:
    protected:

    public:
        size_t filas;
        size_t columnas;
        size_t area;

        char* mapa = nullptr;
};

#endif