#include "Mapa.hpp"

#include<iostream>
#include<cstring>

Mapa::Mapa(std::string ruta){
   std::ifstream mapa_archivo;
   mapa_archivo.open(ruta);
   if(mapa_archivo.is_open()){
        std::string linea;
        std::getline(mapa_archivo,linea);
        size_t espacio = linea.find(' ');
        this->filas = std::stoi(linea.substr(0,espacio));
        this->columnas = std::stoi(linea.substr(espacio + 1));
        this->area = filas*columnas;
        this->mapa = new char(this->area);

        size_t lineas_leidas = 0;
        bool advertencia = false;
        while (std::getline(mapa_archivo,linea) 
               && lineas_leidas < this->filas)
        {
            if(linea.length() == this->columnas){

                if(linea.length()>this->columnas 
                    && !advertencia){
                    std::cout<<ruta<<" contiene lineas mas largas que lo establecido."
                     <<"Se omiten los caracteres restantes"<<std::endl;
                    advertencia = true;
                }
                char* inicio = this->mapa + (lineas_leidas * this->columnas); 
                std::memcpy(inicio,linea.c_str(),this->columnas);
                ++lineas_leidas;
            }else{
                throw std::runtime_error("línea inválida");
            }
        }
   }else{
       throw std::runtime_error("No se pudo abrir el mapa");
   }
}

Mapa::~Mapa(){
    delete[] this->mapa;
}