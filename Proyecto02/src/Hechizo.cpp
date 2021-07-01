#include "Hechizo.hpp"

Hechizo::Hechizo(){

}

Hechizo::~Hechizo(){
    
}

void Hechizo::hechizar(std::string order){
    std::string ruta;
    int medias_noches = 1;

    std::ifstream archivo_mapa(order); 
    size_t espacio = order.find(' ');

    if(espacio != std::string::npos){
        ruta = order.substr(0,espacio);
        medias_noches = std::stoi(order.substr(espacio));
        medias_noches += 0;
    }

    //Crear archivo de salida y hechizar el mapa Hechizar(mapa)
    Mapa mapa(ruta);
    
    
    
}