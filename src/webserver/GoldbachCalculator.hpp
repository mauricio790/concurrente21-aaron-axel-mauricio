#ifndef GOLDBACHCALCULATOR_H
#define GOLDBACHCALCULATOR_H
class GoldbachCalculator {

public:
  struct Sumas{
    int64_t cantSumas;
    int64_t num1;
    int64_t num2;
    int64_t num3;
  };
    //std::vector<Sumas>* sumas_goldbach;
    Sumas* sumandos;
    std::vector<Sumas> sumGoldbach;
    GoldbachCalculator();
    ~GoldbachCalculator();
    std::vector<GoldbachCalculator::Sumas>* leerDatos(std::vector<int64_t>* user_numbers);
    bool esPrimo(int64_t numero);
    bool esPar(int64_t numero);
    int conFuerte(int64_t numero, bool esNegativo,Sumas *sumandos,int indxVec,int tamanio);
    int conDebil(int64_t numero,bool esNegativo,Sumas *sumandos, int indxVec, int tamanio);
    int goldbach(int64_t dato);
    void imprimir(int cantidad, bool esNegativo, Sumas *sumandos);
}; 
#endif  //GOLDBACHCALCULATOR_H
