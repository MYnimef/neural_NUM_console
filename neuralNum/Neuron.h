//Class Neuron. More info soon...

#pragma once
#include <cstdlib>
#include <cmath>
#include <ctime>

class Neuron
{
public:
    size_t linesNum;
    size_t columnsNum;
    double** weights;
    double* layer;
    double* sigma;

    void setRandomWeights(size_t n, size_t m)   //Weights initialization and randomization.
    {
        linesNum = n, columnsNum = m;
        weights = new double* [linesNum];
        for (size_t i = 0; i < linesNum; i++)
        {
            weights[i] = new double[columnsNum];
            for (size_t j = 0; j < columnsNum; j++)
            {
                weights[i][j] = (5 - rand() % 10) * 0.1;
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
    }

    void backwardPropagation(size_t previousLayerSize, double** previousWeights, double* previousSigma) //Calculation of sigma (aka error) for each layer.
    {
        sigma = new double[columnsNum];
        for (size_t i = 0; i < columnsNum; i++)
        {
            double sigma_in = 0;
            for (size_t j = 0; j < previousLayerSize; j++)
            {
                sigma_in += previousSigma[j] * previousWeights[i][j];
            }
            sigma[i] = sigma_in * layer[i] * (1 - layer[i]);
        }
    }

    void changeWeights(double k, double* previousLayer) //Final change of weights, using sigma.
    {
        double** deltaWeights = new double* [linesNum];
        for (size_t i = 0; i < linesNum; i++)
        {
            deltaWeights[i] = new double[columnsNum];
            for (size_t j = 0; j < columnsNum; j++)
            {
                deltaWeights[i][j] = k * sigma[j] * previousLayer[i];
                weights[i][j] += deltaWeights[i][j];
            }
            delete[] deltaWeights[i];
        }
    }

    void clear()    //Dynamic arrays are need to be deleted.
    {
        delete[] layer;
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
        return 1 / (1 + exp(-x));
    }

    void matrixMultiplication(size_t M1_str, double** M1, size_t same, double** M2, size_t M2_col, double** result) //I don't use it, but it's there... and it ceeps you going...
    {
        for (size_t i = 0; i < M1_str; i++)
        {
            for (size_t j = 0; j < M2_col; j++)
            {
                double sup = 0;
                for (size_t k = 0; k < same; k++)
                {
                    sup += M1[i][k] * M2[j][k];
                }
                result[i][j] = sup;
            }
        }
    }
};