#ifndef GOLDBACHCALCULATOR_H
#define GOLDBACHCALCULATOR_H
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <string>
#include <stdlib.h>
#include <sstream>
class GoldbachCalculator {

public:
  struct Sumas{
    int64_t num1;
    int64_t num2;
    int64_t num3;
  };
    std::vector<int> cant_sumGoldbach;
    std::stringstream sums_goldbach;
    std::vector<Sumas> sumGoldbach;
    std::vector<std::string> sumas_gold;
    GoldbachCalculator();
    ~GoldbachCalculator();
    void leerDatos(std::vector<int64_t>* user_numbers);
    bool esPrimo(int64_t numero);
    bool esPar(int64_t numero);
    void conFuerte(int64_t numero, bool esNegativo);
    void conDebil(int64_t numero,bool esNegativo);
    void goldbach(int64_t dato);
    void formarString(std::vector<int64_t>* user_numbers);
}; 
#endif  //GOLDBACHCALCULATOR_H
