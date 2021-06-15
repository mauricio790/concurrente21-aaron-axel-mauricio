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
 * @brief Reads numbers from a string and stores on a std::vector<int64_t>*
 * @details Reads numbers from a string and stores on a std::vector<int64_t>*
 *  then sends them to start solving the goldbach sums. 
 * @param std::vector<int64_t>* user_numbers user entered numbers to solve 
 * */
void GoldbachCalculator::leerDatos(std::vector<int64_t>* user_numbers) {
  for (std::vector<int64_t>::iterator it = user_numbers->begin() ;it != user_numbers->end(); it++) {
    goldbach(*it);
  }
  formarString(user_numbers);
  std::string sums = sums_goldbach.str();
}

/**
 * @brief This method verifies that the number entered has a solution 
 * @details Verifies that the number entered has a solution. If it's lower than 0, raises a flag so the program 
 * shows its sums
 * @param int64_t dato is the number to solve
 * */
void GoldbachCalculator::goldbach(int64_t dato) {
	bool esNegativo = false;
    /* Verifica si el numero ingresado es negativo para convertirlo a 
     * positivo pero guardando que es negativo.*/
    if (dato < 0 && dato < -5) {
      esNegativo = true;
      dato = dato*(-1);
    }
    if (esPar(dato)) {
      conFuerte(dato, esNegativo);
    } else {
        conDebil(dato, esNegativo);
      }
  }
/**
 * @brief solves strong conjecture
 * @details checks if the first sum digit is a prime number, then checks the second digit. If both are
 * prime numbers, then adds them to the sum struc and continues looking for valid sums
 * @param numero this is the number we're trying to find sums for
 * @param esNegativo if true, shows the sums. if not, shows the amount of sums for this number
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
 * @brief solves weak conjecture
 * @details checks if the first sum digit is a prime number, then checks the second digit. If both are
 * prime numbers, then adds them to the sum struc and continues looking for valid sums
 * @param numero this is the number we're trying to find sums for
 * @param esNegativo if true, shows the sums. if not, shows the amount of sums for this number
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
/**
 * @brief this method creats a string with all the information needed to give a solution 
 * @details this method creats a string with the final result for the user.
 * @param user_numbers std::vector with all the numbers given by the user
 * */
void GoldbachCalculator::formarString(std::vector<int64_t>* user_numbers){
  
  std::vector<int64_t>::iterator it_nums = user_numbers->begin();
  std::vector<int>::iterator it_cantsums = cant_sumGoldbach.begin();
  int index_sumas = 0;
  int maximo_index = 0;
  while(it_cantsums != cant_sumGoldbach.end()){

    int cant_sumas = *it_cantsums;
    if(*it_nums >= -5 && *it_nums <= 5){
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
  }
}
 
/**
 * @brief Verifies if the given number is an even number
 * @details this method receives a number and checks if it's an even number. 
 * @param numero number used to verify
 * @return true if is an even numer, false if not
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
 * @brief @brief Verifies if the given number is an prime number
 * @details this method receives a number and checks if it's an prime number dividing it by all its successors. 
 * @param numero number used to verify
 * @return true if is an even numer, false if not
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