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
    //for (int i = 0; i<medias_noches; i++) {
        //for (int i = 0; i < area; i++) {
            //mapa.verificarVecinos(mapa);
        //}
    //}
}
void Hechizo::verificarCelda(std::string prueba, size_t i){
    for (size_t j=0; j<prueba.length(); j++){
        if (prueba[j] == 'a'){
            cant_arboles++;
        }
        if (prueba[j] == 'l'){
            cant_lagos++;
        }
    }
    verificarReglas(i);
    cant_arboles = 0;
    cant_lagos = 0;
}
void Hechizo::verificarReglas(const size_t &i){
    char bandera = false;
    //if(i<area){
        if (mapa[i] == ARBOL && cant_lagos >= 4)
        { //Inundacion
            bandera = true;
            bosqu += LAGO;
        }
        if (mapa[i] == LAGO && cant_lagos < 3)
        { //Sequia
            bosqu += PRADERA;
            bandera = true;
        }
        if (mapa[i] == PRADERA && cant_arboles >= 3)
        { //Reforestacion
            bosqu += ARBOL;
            bandera = true;
        }
        if (mapa[i] == ARBOL && cant_arboles > 4)
        { // Hacinamiento
            bosqu += PRADERA;
            bandera = true;
        }
        if(!bandera){
            bosqu += mapa[i];
        }
    //}
}