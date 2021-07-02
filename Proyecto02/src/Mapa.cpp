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
        this->mapa = "";

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
                mapa += linea;
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
}
std::string Mapa::obtenerVecinos(const size_t &i){
    bool norte = false;
    bool sur = false;
    bool este = false;
    bool oeste = false;
    std::string vecinos = "";
    if (i >= columnas)
    { //norte
        vecinos += mapa[i - columnas];
        norte = true;
    }
    if (i <= area-columnas)
    { //sur
        vecinos += mapa[i + columnas];
        sur = true;
    }
    if ((i + 1) % columnas != 0)
    { //este
        vecinos += mapa[i + 1];
        este = true;
    }
    if ((i) % columnas  != 0)
    { //oeste
       vecinos += mapa[i - 1];
        oeste = true;
    }
    if (norte && este)
    { //NorEste
        vecinos += mapa[i - columnas + 1];
    }
    if (norte && oeste)
    { //Noroeste
        vecinos += mapa[i - columnas - 1];
    }                                               
    if (sur && este )                              
    { //Sureste                                     
        vecinos += mapa[i + columnas + 1];        
    }
    if (sur && oeste )
    { //Suroeste
        vecinos += mapa[i + columnas - 1];
    }
    return vecinos;
}