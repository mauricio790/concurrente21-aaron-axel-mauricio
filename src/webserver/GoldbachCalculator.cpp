#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "GoldbachCalculator.hpp"

GoldbachCalculator::GoldbachCalculator() {
 }
 GoldbachCalculator::~GoldbachCalculator() {
 }
/**
 * @brief Lee cada numero 
 * @details Lee los numeros como una cadena y los covierte a int64_t y despues los envia para comenzar a sacar la conjetura.Se define la longitud del vector de structs
 * @param retorna si el programa se ejecuto correctamente o si fallo algo durante la ejecucion y se detiene si fallo algo.
 * */
void GoldbachCalculator::leerDatos(std::vector<int64_t>* user_numbers) {
  //std::vector<GoldbachCalculator::Sumas>* ejemplo = (std::vector<GoldbachCalculator::Sumas>*);
  for (std::vector<int64_t>::iterator it = user_numbers->begin() ;it != user_numbers->end(); it++) {
    goldbach(*it);
  }
  formarString(user_numbers);
  std::string sums = sums_goldbach.str();
  //std::cout << sums;
}

/**
 * @brief Verificacion de los datos leidos 
 * @details Verifica que los numeros sean mayores que 5, si es negativo o positivo y determina cual es la conjetura de dicho numero si es fuerte o debil. Se crea el vector
 * de una estrutura que almacenara las sumas
 * @param recibe el dato del cual queremos sacar su conjetura y la longitud del vector que se creara mas abajo
 * */
void GoldbachCalculator::goldbach(int64_t dato) {
	bool esNegativo = false;
    /* Verifica si el numero ingresado es negativo para convertirlo a 
     * positivo pero guardando que es negativo.*/
    if (dato < 0) {
      esNegativo = true;
      dato = dato*(-1);
    }
    // Verifica si el numero ingresado es mayor que 5 como se pide.
    //if (dato > 5) {
      // Verifica si el numero es par para ver cual conjuncion se le asigna
      if (esPar(dato)) {
       	conFuerte(dato, esNegativo);
       } else {
         	conDebil(dato, esNegativo);
        }
	   //} //else {
        //sums_goldbach << dato << ": <br>";
        //sums_goldbach << "<b>NA </b>" ;
      //}
  }
/**
 * @brief Saca la conjetura fuerte de los numeros
 * @details Se verifica si el primer sumando es primo, si los es se busca el segundo sumando que es la resta entre el numero
 * y el primer sumando, se verifica si es primo, si lo es se almacena en el vector de sumas, se verifica que dicho vector tenga espacio sino se incrementa
 * @param numero del que vamos a sacar la conjetura, signo del numero, vector donde se almacenaran las sumas
 * */
void GoldbachCalculator::conFuerte(int64_t numero,bool esNegativo) {
  int cantidad = 0;
  for (int64_t num_1 = 2; num_1 < numero; num_1++) {
    if (esPrimo(num_1) && esPrimo(numero - num_1)) {
      if (num_1 <= numero - num_1) {
        cantidad++;
        /* Verifica si dicho numero activo el booleano de 
         * que si es negativo para guardar las sumas.*/
        if (esNegativo) {
          /* Verifica si la cantidad de sumas se puede almacenar 
           * en el arreglo y sino da un doble tamanio al arreglo.*/
            GoldbachCalculator::Sumas sumas;
            sumas.num1 = num_1;
            sumas.num2 = numero - num_1;
            sumas.num3 =0;
            sumGoldbach.push_back(sumas);
        }
      }
    }
  }
  cant_sumGoldbach.push_back(cantidad);

}
/**
 * @brief Saca la conjetura debil de los numeros
 * @details Se verifica si el primer y segundo sumando es primo, si lo es pasa a verificar si el tercer sumando lo cumple,
 * si lo cumple entonces verifica si la suma de esos tres sumandos es igual al numero del que queriamos sacar la conjetura
 * y se determina si se puede sacar la conjetura del numero si se puede lo almacena en el vector, si este vector no cuenta con espascio
 * lo incrementa
 * @param numero del que vamos a sacar la conjetura, signo del numero, vector donde se almacenaran las sumas
 * */
void GoldbachCalculator::conDebil(int64_t numero,bool esNegativo) {
  int cantidad = 0;
  for (int64_t num_1 = 2; num_1 < numero; num_1++) {
    if (esPrimo(num_1)) {
      for (int64_t num_2 = num_1; num_2 < numero; num_2++) {
        if (esPrimo(num_2)) {
          for (int64_t num_3 = num_2; num_3 < numero; num_3++) {
            /*Verifica si la suma de los numeros 
             * primos es igual al numero ingresado*/
            if (num_1 + num_2 + num_3 == numero && esPrimo(num_3)) {
              cantidad++;
                /*Verifica si dicho numero activo el booleano de 
                 * que si es negativo para guardar las sumas.*/
              if (esNegativo) {
                /*Verifica si la cantidad de sumas se puede almacenar en el 
                 * arreglo y sino da un doble tamanio al arreglo.*/
                GoldbachCalculator::Sumas sumas;
                sumas.num1 = num_1;
                sumas.num2 = num_2;
                sumas.num3 = num_3;
                sumGoldbach.push_back(sumas);
              }
            }
          }
        }
      }
    }
  }
  cant_sumGoldbach.push_back(cantidad);
}
void GoldbachCalculator::formarString(std::vector<int64_t>* user_numbers){
  
  std::vector<int64_t>::iterator it_nums = user_numbers->begin();
  std::vector<int>::iterator it_cantsums = cant_sumGoldbach.begin();
  int index_sumas = 0;
  int maximo_index = 0;
  while(it_cantsums != cant_sumGoldbach.end()){

    int cant_sumas = *it_cantsums;
    if(*it_nums > -5 && *it_nums < 5){
        sums_goldbach << "<B><FONT COLOR=red><h2>"<< *it_nums<<"</h2></FONT></B>";
        sums_goldbach << *it_nums << ": ";
        sums_goldbach << "NA";
    } else {
      sums_goldbach << "<h2>"<< *it_nums << "</h2 <br>";
      sums_goldbach << *it_nums << ": ";
      sums_goldbach << cant_sumas << " sums <br>";
    }
    if(*it_nums < 0){
      maximo_index = *it_cantsums + maximo_index;
      //std::cout<<"maximo_index"<<maximo_index<<std::endl;
      //std::cout<<"index_sumas"<<index_sumas<<std::endl;
      int contador_sumas = 1;
      while(index_sumas < maximo_index){
       sums_goldbach << contador_sumas << ". " << sumGoldbach[index_sumas].num1 << " + " << sumGoldbach[index_sumas].num2;
        if (sumGoldbach[index_sumas].num3 != 0){
          sums_goldbach << " + " << sumGoldbach[index_sumas].num3;
        }
        sums_goldbach << "<br>";
        ++index_sumas;
        ++contador_sumas;
      }
      sums_goldbach << "<br>";
    }
    ++it_cantsums; 
    ++it_nums;
    //std::string sums = sums_goldbach.str();
    //std::cout << sums <<std::endl;
    //sums_goldbach.clear();
  }
}
 
/**
 * @brief Determina si un numero es par
 * @details divide el numero para ver si es divisible entre 2
 * @param numero del que queremos saber si es par
 * @return un booleano que dice si es par o no
 * */ 
bool GoldbachCalculator::esPar(int64_t numero) {
  bool numPar = false;
  // Verifica si el numero es divisible entre dos.
  if (numero % 2 == 0) {
    numPar = true;
  }
  return numPar;
}

/**
 * @brief Determina si un numero es primo
 * @details va diviendo el numero para comprobar si tiene mas de un divisor
 * @param numero del que queremos saber si es primo
 * @return un booleano que dice si es primo o no
 * */ 
bool GoldbachCalculator::esPrimo(int64_t numero) {
  bool numPrimo = true;
  for (int64_t divisor = 2; divisor < numero; ++divisor) {
    // Verifica si el numero tiene algun divisor, que no sea el mismo o 1.
    if (numero % divisor == 0) {
      numPrimo =  false;
    }
  }
  return numPrimo;
}