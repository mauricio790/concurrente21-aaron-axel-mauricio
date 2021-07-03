#include "Hechizo.hpp"

Hechizo::Hechizo()
{
}

Hechizo::~Hechizo()
{
}

void Hechizo::hechizar(std::string order)
{
    std::string ruta;
    int medias_noches = 1;

    std::ifstream archivo_mapa(order);
    size_t espacio = order.find(' ');

    if (espacio != std::string::npos)
    {
        ruta = order.substr(0, espacio);
        medias_noches = std::stoi(order.substr(espacio));
        medias_noches += 0;
    }

    //Crear archivo de salida y hechizar el mapa Hechizar(mapa)
    Mapa mapa(ruta);
    std::string extention = ".txt";
    std::string rutaSalida = ruta.substr(0, ruta.length() - extention.length()) + "-";
    rutaSalida += std::to_string(medias_noches < 0 ? medias_noches * -1 : medias_noches) + extention;
    //std::cout << rutaSalida << std::endl;

    this->salida.open(rutaSalida);

    if (salida.is_open())
    {
        this->hechizarMapa(mapa, medias_noches);
    }
    else
    {
        throw std::runtime_error("No se pudo abrir archivo de salida");
    }

    salida.close();
}

void Hechizo::hechizarMapa(Mapa &mapa, int medias_noches)
{
    size_t noches;
    bool imprimirHechizos = medias_noches < 0;
    if(imprimirHechizos){
        noches = medias_noches * -1;
    }else{
        noches = medias_noches;
    }
    std::string nuevoMapa;
    escribirMapa(mapa, 0);
    for(size_t noche = 0; noche <noches; ++noche){
        nuevoMapa = mapa.mapa;
        for(size_t celda = 0; celda < mapa.area;++celda){
            std::string vecinos = mapa.obtenerVecinos(celda);
            nuevoMapa[celda] = this->verificarVecinos(mapa,vecinos,celda);
        }  
        mapa.mapa = nuevoMapa;
        this->escribirMapa(mapa,noche+1);
        
    }
    
}

void Hechizo::escribirMapa(Mapa &mapa, size_t noche)
{
    this->salida << noche << ":" << std::endl;
    std::string linea = "";
    for (size_t i = 0; i < mapa.area; i++)
    {
        linea += mapa.mapa[i];

        if ((i + 1) % mapa.columnas == 0)
        {
            this->salida << linea;
            linea = "";
            if (i != mapa.area - 1)
            {
                this->salida << std::endl;
                linea = "";
            }
        }
    }
    this->salida << std::endl;
}

char Hechizo::verificarVecinos(Mapa& mapa,std::string prueba, size_t i)
{
    size_t cant_arboles = 0;
    size_t cant_lagos = 0;
    for (size_t j = 0; j < prueba.length(); j++)
    {
        if (prueba[j] == ARBOL)
        {
            cant_arboles++;
        }
        if (prueba[j] == LAGO)
        {
            cant_lagos++;
        }
    }
    return verificarReglas(mapa,i, cant_arboles, cant_lagos);
}

char Hechizo::verificarReglas(Mapa& mapa,const size_t &i, size_t cant_arboles, size_t cant_lagos)
{
    char bosque = mapa.mapa[i];
    //if(i<area){
    if (mapa.mapa[i] == ARBOL && cant_lagos >= 4)
    { //Inundacion       
        bosque = 'l';
    }
    if (mapa.mapa[i] == LAGO && cant_lagos < 3)
    { //Sequia
        bosque = '-';
    }
    if (mapa.mapa[i] == PRADERA && cant_arboles >= 3)
    { //Reforestacion
        bosque = 'a';
    }
    if (mapa.mapa[i] == ARBOL && cant_arboles > 4)
    { // Hacinamiento
        bosque += '-';
    }

    return bosque;
}