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

        //crea un mapa y se deja la cantidad de medias noches
        void hechizar(std::string mapa); 

    private:
    protected:
};

#endif