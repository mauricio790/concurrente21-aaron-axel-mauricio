#ifndef GOLDBACHCALCULATOR_H
#define GOLDBACHCALCULATOR_H
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
class GoldbachCalculator {

public:
  struct Sumas{
    int64_t cantSumas;
    int64_t num1;
    int64_t num2;
    int64_t num3;
  };
    std::vector<Sumas> sumGoldbach;
    GoldbachCalculator();
    ~GoldbachCalculator();
    std::vector<GoldbachCalculator::Sumas>* leerDatos(std::vector<int64_t>* user_numbers);
    bool esPrimo(int64_t numero);
    bool esPar(int64_t numero);
    void conFuerte(int64_t numero, bool esNegativo);
    void conDebil(int64_t numero,bool esNegativo);
    void goldbach(int64_t dato);
}; 
#endif  //GOLDBACHCALCULATOR_H
