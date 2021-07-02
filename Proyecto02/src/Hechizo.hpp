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
        Hechizo();
        ~Hechizo();
        int cant_arboles;
        int cant_lagos;
        std::string bosqu;
        std::string mapa;
        //crea un mapa y se deja la cantidad de medias noches
        void hechizar(std::string mapa); 
        void verificarReglas(const size_t &i);
        void verificarCelda(std::string prueba,size_t i);

    private:
    protected:
};

#endif