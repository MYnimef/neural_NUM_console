//Class Neuron. More info soon...

#pragma once
#include <cstdlib>
#include <cmath>
#include <ctime>

class Neuron
{
public:
    size_t linesNum, columnsNum;
    double** weights;
    double* layer;
    double* sigma;

    void setRandomWeights(size_t n, size_t m)   //Weights initialization and randomization.
    {
        linesNum = n, columnsNum = m;
        weights = new double* [linesNum];
        srand(time(0));
        for (size_t i = 0; i < linesNum; i++)
        {
            weights[i] = new double[columnsNum];
            for (size_t j = 0; j < columnsNum; j++)
            {
                weights[i][j] = (5.0 - rand() % 10) * 0.1;
            }
        }
    }

    void forwardPropagation(double* previousLayer)  //Forward propagation needs previous layer values.
    {
        layer = new double[columnsNum];
        for (size_t i = 0; i < columnsNum; i++)
        {
            double sum = 0;
            for (size_t j = 0; j < linesNum; j++)
            {
                sum += previousLayer[j] * weights[j][i];
            }
            layer[i] = sigmoidFunction(sum);
        }
    }

    void mistake(double* output)    //Margion of error calculation, from this point backwars propagation starts.
    {
        sigma = new double[columnsNum];
        for (size_t i = 0; i < columnsNum; i++)
        {
           sigma[i] = (output[i] - layer[i]) * layer[i] * (1 - layer[i]);
        }
        delete[] layer;
    }

    void backwardPropagation(size_t previousLayerSize, double** previousWeights, double* previousSigma, double k) //Calculation of sigma (aka error) for each layer.
    {
        sigma = new double[columnsNum];
        for (size_t i = 0; i < columnsNum; i++)
        {
            double sigma_in = 0;
            for (size_t j = 0; j < previousLayerSize; j++)
            {
                sigma_in += previousSigma[j] * previousWeights[i][j];
                previousWeights[i][j] += k * previousSigma[j] * layer[i];
            }
            sigma[i] = sigma_in * layer[i] * (1 - layer[i]);
        }
        delete[] layer;
        delete[] previousSigma;
    }

    void changeWeights(double k, double* previousLayer) //Final change of weights, using sigma.
    {
        for (size_t i = 0; i < linesNum; i++)
        {
            for (size_t j = 0; j < columnsNum; j++)
            {
                weights[i][j] += k * sigma[j] * previousLayer[i];
            }
        }
        delete[] sigma;
    }

    void clearWeights() //Dynamic arrays are need to be deleted.
    {
        for (size_t i = 0; i < linesNum; i++)
        {
            delete[] weights[i];
        }
    }

private:
    double sigmoidFunction(double x)  //Function that calculates value INSIDE neuron.
    {
        return (1 / (1 + exp(-x)));
    }
};