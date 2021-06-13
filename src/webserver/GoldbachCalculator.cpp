#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include "GoldbachCalculator.hpp"

struct Sumas{
  int64_t cantSumas;
  int64_t num1;
  int64_t num2;
  int64_t num3;
    };
/**
 * @brief subrutina principal
 * @details llama a la subrutina encargada de leer los datos
 * @param no recibe ningun parametro
 * @return retorna el numero de error
 * */
  GoldbachCalculator::GoldbachCalculator() {
  }
  GoldbachCalculator::~GoldbachCalculator() {
  }
/*int main(void) {
  int numeros =-250;
  std::vector<int64_t>* user_numbers;
  for (std::vector<int64_t>::iterator it = user_numbers->begin() ;it != user_numbers->end(); it++) {
      *it = numeros++;
  } 
  
  GoldbachCalculator calculator;
  calculator.leerDatos(user_numbers);
  return 0;
}*/

/**
 * @brief Lee cada numero 
 * @details Lee los numeros como una cadena y los covierte a int64_t y despues los envia para comenzar a sacar la conjetura.Se define la longitud del vector de structs
 * @param retorna si el programa se ejecuto correctamente o si fallo algo durante la ejecucion y se detiene si fallo algo.
 * */
struct* GoldbachCalculator::leerDatos(std::vector<int64_t>* user_numbers) {
  //FILE* input = stdin;
  int error = 0;
  Sumas * ejemplo = (Sumas *)calloc(5, sizeof(Sumas));
  for (std::vector<int64_t>::iterator it = user_numbers->begin() ;it != user_numbers->end(); it++) { 
      error = goldbach(*it);
    /*if (error == 1) {
        printf("Memoria insuficiente para imprimir las sumas\n");
        return EXIT_FAILURE;
    }*/
  }
  return ejemplo;
}

/**
 * @brief Verificacion de los datos leidos 
 * @details Verifica que los numeros sean mayores que 5, si es negativo o positivo y determina cual es la conjetura de dicho numero si es fuerte o debil. Se crea el vector
 * de una estrutura que almacenara las sumas
 * @param recibe el dato del cual queremos sacar su conjetura y la longitud del vector que se creara mas abajo
 * */
int GoldbachCalculator::goldbach(int64_t dato) {
  size_t tamanio = 5;
  bool esNegativo = false;
  int indxVec = 0;
  Sumas *sumandos;
  int error = 0;
  // Verifica si se reservo correctamente la memoria
    printf("%lld: ", dato);
    /* Verifica si el numero ingresado es negativo para convertirlo a 
     * positivo pero guardando que es negativo.*/
    if (dato < 0) {
      esNegativo = true;
      dato = dato*(-1);
    }
    // Verifica si el numero ingresado es mayor que 5 como se pide.
    if (dato > 5) {
      sumandos = (Sumas *)calloc(tamanio, sizeof(Sumas));
      assert(sumandos);
      // Verifica si el numero es par para ver cual conjuncion se le asigna
      if (esPar(dato)) {
        error = conFuerte(dato, esNegativo, sumandos, indxVec, tamanio);
      } else {
          error = conDebil(dato, esNegativo, sumandos, indxVec, tamanio);
        }
    } else {
        printf("NA\n");
      }
  return error;
}
/**
 * @brief Saca la conjetura fuerte de los numeros
 * @details Se verifica si el primer sumando es primo, si los es se busca el segundo sumando que es la resta entre el numero
 * y el primer sumando, se verifica si es primo, si lo es se almacena en el vector de sumas, se verifica que dicho vector tenga espacio sino se incrementa
 * @param numero del que vamos a sacar la conjetura, signo del numero, vector donde se almacenaran las sumas
 * */
int GoldbachCalculator::conFuerte(int64_t numero,
bool esNegativo, Sumas *sumandos,
int indxVec, int tamanio) {
  int cantidad = 0;
  //sumandos[0].cantSumas = 0;
  int error = 0;
  for (int64_t num_1 = 2; num_1 < numero; num_1++) {
    if (esPrimo(num_1) && esPrimo(numero - num_1)) {
      if (num_1 <= numero - num_1) {
        cantidad++;
        //sumandos[0].cantSumas++;
        /* Verifica si dicho numero activo el booleano de 
         * que si es negativo para guardar las sumas.*/
        if (esNegativo) {
          /* Verifica si la cantidad de sumas se puede almacenar 
           * en el arreglo y sino da un doble tamanio al arreglo.*/
          if (cantidad > tamanio) {
            tamanio = tamanio * 2;
            sumandos = (Sumas *)realloc(sumandos,
            (tamanio * 2) * sizeof(Sumas));
            // Preguntar si el assert esta bien o usar otra forma de validar
          }
          // Verifica si se aumento el tamanio del arreglo correctamente.
          // if (!sumandos) {
          assert(sumandos);
          sumandos[indxVec].num1 = num_1;
          sumandos[indxVec].num2 = numero - num_1;
          sumandos[indxVec].num3 = 0;
            indxVec++;
          //} else {
              // error = 1;
          //}
        }
      }
    }
  }
  /* Verifica si debe imprimir los datos, esto si se cumplieron todos los 
   * requisitos y sino se imprime un mensaje de error*/
  if (error == 0) {
    //imprimir(cantidad,esNegativo,sumandos);
    free(sumandos);
  }
  return error;
}
/**
 * @brief Saca la conjetura debil de los numeros
 * @details Se verifica si el primer y segundo sumando es primo, si lo es pasa a verificar si el tercer sumando lo cumple,
 * si lo cumple entonces verifica si la suma de esos tres sumandos es igual al numero del que queriamos sacar la conjetura
 * y se determina si se puede sacar la conjetura del numero si se puede lo almacena en el vector, si este vector no cuenta con espascio
 * lo incrementa
 * @param numero del que vamos a sacar la conjetura, signo del numero, vector donde se almacenaran las sumas
 * */
int GoldbachCalculator::conDebil(int64_t numero,
bool esNegativo, Sumas * sumandos,
int indxVec, int tamanio) {
  int cantidad = 0;
  //sumandos[0].cantSumas = 0;
  int error = 0;
  for (int64_t num_1 = 2; num_1 < numero; num_1++) {
    if (esPrimo(num_1)) {
      for (int64_t num_2 = num_1; num_2 < numero; num_2++) {
        if (esPrimo(num_2)) {
          for (int64_t num_3 = num_2; num_3 < numero; num_3++) {
            /*Verifica si la suma de los numeros 
             * primos es igual al numero ingresado*/
            if (num_1 + num_2 + num_3 == numero && esPrimo(num_3)) {
              cantidad++;
              //sumandos[0].cantSumas++;
                /*Verifica si dicho numero activo el booleano de 
                 * que si es negativo para guardar las sumas.*/
              if (esNegativo) {
                /*Verifica si la cantidad de sumas se puede almacenar en el 
                 * arreglo y sino da un doble tamanio al arreglo.*/
                if (cantidad > tamanio) {
                  tamanio = tamanio * 2;
                  sumandos = (Sumas *) realloc(sumandos,
                  tamanio * 2 * sizeof(Sumas));
                }
                // Verifica si se aumento el tamanio del arreglo correctamente.
                // if (sumandos) {
                assert(sumandos);
                sumandos[indxVec].num1 = num_1;
                sumandos[indxVec].num2 = num_2;
                sumandos[indxVec].num3 = num_3;
                indxVec++;
                // } else {
                    // error = 1;
                  // }
              }
            }
          }
        }
      }
    }
  }
  /* Verifica si debe imprimir los datos, esto si se cumplieron todos los 
   * requisitos y sino se imprime un mensaje de error*/
  if (error == 0) {
    free(sumandos);
  }
  return error;
}

/**
 * @brief Imprime las sumas de los numeros
 * @details Imprime la cantidad de sumas y sus respectivas sumas de cada numero en los casos que se requieran.Determina cual es la ultima suma para asi no imprimir la ','
 * @param la cantidad de sumas de cada numero, el signo del numero, arreglo donde se almacenan las sumas
 * */
void GoldbachCalculator::imprimir(int cantidad,
bool esNegativo, Sumas *sumandos) {
  FILE* output = stdout;
  /* Verifica si el numero es negativo para imprimir 
   * todas las sumas y sino solo imprimi la cantidad de sumas.*/
  if (!esNegativo) {
    fprintf(output, "%d sums \n", cantidad);
  } else {
    fprintf(output, "%d sums:", cantidad);
    for (int indice = 0; indice < cantidad; indice++) {
      /* Verifica si la estructura Sumas en el numero 3 es 0, para imprimir 
       * solo dos numeros y sino imprime los tres.*/
      if (sumandos[indice].num3 == 0) {
        /*Verifica si es la ultima suma encontrada para 
         * imprimirla sin como y sino imprime con la coma*/
        if (indice != cantidad - 1) {
          fprintf(output, " %lld + %lld,",
          sumandos[indice].num1,
          sumandos[indice].num2);
        } else {
            fprintf(output, " %lld + %lld",
            sumandos[indice].num1,
            sumandos[indice].num2);
          }
            /* Verifica si la cantidad de sumas se puede almacenar en 
             * el arreglo y sino da un doble tamanio al arreglo.*/
      } else if (indice != cantidad - 1) {
          fprintf(output, " %lld + %lld + %lld,", sumandos[indice].num1,
          sumandos[indice].num2,
          sumandos[indice].num3);
        } else {
            fprintf(output, " %lld + %lld + %lld",
            sumandos[indice].num1,
            sumandos[indice].num2,
            sumandos[indice].num3);
          }
    }
    printf("\n");
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
