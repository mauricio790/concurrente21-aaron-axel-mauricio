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
  int cantSumas;
    std::vector<int> cant_sumGoldbach;
    std::stringstream sums_goldbach;
    std::vector<Sumas> sumGoldbach;
    GoldbachCalculator();
    ~GoldbachCalculator();
    void leerDatos(int64_t number);
    bool esPrimo(int64_t numero);
    bool esPar(int64_t numero);
    void conFuerte(int64_t numero, bool esNegativo);
    void conDebil(int64_t numero, bool esNegativo);
    void goldbach(int64_t dato);
    void formarString(int64_t number, int cantidad);
    void generadorHtml();
};
#endif  // GOLDBACHCALCULATOR_H
