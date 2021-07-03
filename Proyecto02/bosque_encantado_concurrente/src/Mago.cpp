#include "Mago.hpp"
#include "Hechizo.hpp"
#include<iostream>
#include<fstream>
#include<stdexcept>

int Mago::start(int argc,char* argv[]){
    int error = 0;
    std::string linea;
    
    if(analyze_arguments(argc,argv)){
        std::vector<std::string> mapas = get_mapas();
        Hechizo hechizo;

        for(auto mapa : mapas){
           hechizo.hechizar(mapa);
        }

    }else{ error = 1; }
    
    return error;
}

/**
    *@brief recibe archivo con órdenes de trabajo y 
    *       las retorna en un std::vector<string> 
    *
**/
std::vector<std::string> Mago::get_mapas(){
    std::vector<std::string> mapas;
    std::ifstream order(job_order);

    if(order.is_open()){
        std::string linea;
        while ((std::getline(order,linea))){
            if(linea.length() > 0){
                mapas.push_back(linea);
            }
        }
        
    }else{
        throw std::runtime_error("No se pudo abrir archivo");
    }
    return mapas;
}

Mago::Mago(){

}

Mago::~Mago(){
}

int Mago::analyze_arguments(int argc, char* argv[]){

    if(argc == 2){
        job_order = argv[1];
        return 1;   
    }

    return 0;
}
