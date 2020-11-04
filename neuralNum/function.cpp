#include <cmath>

double sigmoidFunction(double x)  //Функция преобразования внутри нейрона
{
    return 1 / (1 + exp(-x));
}