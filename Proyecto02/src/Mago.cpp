#include "Mago.hpp"
#include<iostream>
#include<fstream>


int Mago::start(int argc,char* argv[]){
    int error = 0;
    std::string linea;
    if(analyze_arguments(argc,argv)){
       std::vector<std::string> mapas = get_mapas();
    }else{ error = 1; }
    return error;
}

std::vector<std::string> Mago::get_mapas(){
    std::vector<std::string> mapas;
    std::ifstream order(job_order);

    if(order.is_open()){
        std::string linea;
        while ((std::getline(order,linea))){
            if(linea.length() > 0){
                mapas.push_back(linea);
                std::cout<<linea<<std::endl;
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
        std::cout<<job_order<<std::endl;
        return 1;   
    }

    return 0;
}
