#ifndef GOLDBACHCALCULATOR_H
#define GOLDBACHCALCULATOR_H

class GoldbachCalculator {

public:
    struct Sumas{
      int64_t num1;
      int64_t num2;
      int64_t num3;
    };
    GoldbachCalculator();
    ~GoldbachCalculator();
    int leerDatos();
    bool esPrimo(int64_t numero);
    bool esPar(int64_t numero);
    int conFuerte(int64_t numero, bool esNegativo,Sumas *sumandos,int indxVec,int tamanio);
    int conDebil(int64_t numero,bool esNegativo,Sumas *sumandos, int indxVec, int tamanio);
    int goldbach(int64_t dato, int tamanio);
    void imprimir(int cantidad, bool esNegativo, Sumas *sumandos);
}; 
#endif  //GOLDBACHCALCULATOR_H
