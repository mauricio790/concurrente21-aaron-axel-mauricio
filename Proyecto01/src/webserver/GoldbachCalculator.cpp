#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "GoldbachCalculator.hpp"
#include "GeneradorHtml.hpp"

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
void GoldbachCalculator::leerDatos(int64_t number) {
  GeneradorHtml generadorHtml;
    goldbach(number);
    //sums_goldbach << number << ": ";
  /* After traversing the vector, it is invoked
   * to the method that forms the string of sums */
  sums_goldbach = generadorHtml.generarHtml(&sumGoldbach,cant_sumGoldbach[0],number);
}
/**
 * @brief This method verifies that the number entered has a solution 
 * @details Verifies that the number entered has a solution. If it's lower than 0, raises a flag so the program 
 * shows its sums
 * @param int64_t dato is the number to solve
 * */
void GoldbachCalculator::goldbach(int64_t dato) {
  bool esNegativo = false;
  /* Check if the entered number is negative to convert it to
  * positive but keeping that it is negative.*/
  if (dato < 0 && dato < -5) {
    esNegativo = true;
    dato = dato*(-1);
  }
  // Check if the number is odd or even to determine your "conjetura"
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
void GoldbachCalculator::conFuerte(int64_t numero, bool esNegativo) {
  int cantidad = 0;
  cantSumas = 0;
  for (int64_t num_1 = 2; (num_1 * 2) <= numero; num_1+=2) {
    if (esPrimo(num_1) && esPrimo(numero - num_1)) {
      if (num_1 <= numero - num_1) {
        cantidad++;
        cantSumas++;
        /*Check if this number activates the boolean of if it is negative to save the sums.*/
        if (esNegativo) {
            GoldbachCalculator::Sumas sumas;
            sumas.num1 = num_1;
            sumas.num2 = numero - num_1;
            sumas.num3 = 0;
            sumGoldbach.push_back(sumas);
        }
      }
    }
    if (num_1 == 2) {
      num_1 = 1;
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
void GoldbachCalculator::conDebil(int64_t numero, bool esNegativo) {
  int cantidad = 0;
  int num_3 = 0;
  for (int64_t num_1 = 2; (num_1 * 2) < numero; num_1+=2) {
    if (esPrimo(num_1)) {
      for (int64_t num_2 = num_1; (num_2 * 2) < numero; num_2+=2) {
        if (esPrimo(num_2)) {
            /*Check if the sum of the numbers prime equals the number entered*/
            if (num_1 + num_2 < numero){
              num_3 = numero - num_1 - num_2;
            }
            if (num_3 > 2 && num_1 <= num_2 && num_2 <= num_3
              && esPrimo(num_3)) {
              cantidad++;
                /*Check if this number activates the boolean of * if it is negative to save the sums.*/
              if (esNegativo) {
                GoldbachCalculator::Sumas sumas;
                sumas.num1 = num_1;
                sumas.num2 = num_2;
                sumas.num3 = num_3;
                sumGoldbach.push_back(sumas);
              }
            }
          }
        if (num_2 == 2) {
          num_2 = 1;
        }
      }
    }
    if (num_1 == 2) {
      num_1 = 1;
    }
  }
  cant_sumGoldbach.push_back(cantidad);
}

/**
 * @brief Verifies if the given number is an even number
 * @details this method receives a number and checks if it's an even number. 
 * @param numero number used to verify
 * @return true if is an even numer, false if not
 * */ 
bool GoldbachCalculator::esPar(int64_t numero) {
  bool numPar = false;
  // Check if the number is divisible by two.
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
  if (numero % 2 == 0 && numero > 2) {
    return false;
  }
  for (int64_t divisor = 3; divisor <= sqrt(numero) && numPrimo; divisor+=2) {
    // Verifica si el numero tiene algun divisor, que no sea el mismo o 1.
    if (numero % divisor == 0) {
      return false;
    }
  }
  return numPrimo;
}
