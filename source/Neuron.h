#pragma once

#include <cstdlib>
#include <cmath>
#include <ctime>

class Neuron {
public:
    size_t linesNum, columnsNum;
    double** weights;
    double* layer;
    double* sigma;

    void setRandomWeights(size_t n, size_t m);   //Weights initialization and randomization.
    void forwardPropagation(double* previousLayer);  //Forward propagation needs previous layer values.
    void mistake(double* output);    //Margion of error calculation, from this point backwars propagation starts.
    void backwardPropagation(size_t previousLayerSize, double** previousWeights, double* previousSigma, double k); //Calculation of sigma (aka error) for each layer.
    void changeWeights(double k, double* previousLayer); //Final change of weights, using sigma.
    void clearWeights(); //Dynamic arrays are need to be deleted.

private:
    double sigmoidFunction(double x);  //Function that calculates value INSIDE neuron.
};