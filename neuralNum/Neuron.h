#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

double sigmoidFunction(double x);

class Neuron
{
public:
    size_t layerSize;

    void setRandomWeights(size_t n, size_t m)
    {
        linesNum = n, layerSize = m;
        weights = new double* [linesNum];
        for (size_t i = 0; i < linesNum; i++)
        {
            weights[i] = new double[layerSize];
            for (size_t j = 0; j < layerSize; j++)
            {
                weights[i][j] = (5 - rand() % 10) * 0.01;
            }
        }
    }

    double* layer;

    void forwardPropagation(size_t previousLayerSize, double* previousLayer)
    {
        layer = new double[layerSize];
        for (size_t i = 0; i < layerSize; i++)
        {
            double sum = 0;
            for (size_t j = 0; j < previousLayerSize; j++)
            {
                sum += previousLayer[j] * weights[j][i];
            }
            layer[i] = sigmoidFunction(sum);
        }
    }

    double* sigma;

    void mistake(double* output)
    {
        sigma = new double[layerSize];
        for (size_t i = 0; i < layerSize; i++)
        {
           sigma[i] = (output[i] - layer[i]) * layer[i] * (1 - layer[i]);
        }
    }

    void backwardPropagation(size_t previousLayerSize, double** previousWeights, double* previousSigma)
    {
        sigma = new double[layerSize];
        for (size_t i = 0; i < layerSize; i++)
        {
            double sigma_in = 0;
            for (size_t j = 0; j < previousLayerSize; j++)
            {
                sigma_in += previousSigma[j] * previousWeights[i][j];
            }
            sigma[i] = sigma_in * layer[i] * (1 - layer[i]);
        }
    }

    double** deltaWeights;

    void changeWeights(double k, double* previousLayer)
    {
        deltaWeights = new double* [linesNum];
        for (size_t i = 0; i < linesNum; i++)
        {
            deltaWeights[i] = new double[layerSize];
            for (size_t j = 0; j < layerSize; j++)
            {
                deltaWeights[i][j] = k * sigma[j] * previousLayer[i];
                weights[i][j] += deltaWeights[i][j];
            }
        }
    }

    void setWeights()
    {
        ofstream file_w("weights.txt", ios_base::app);
        for (size_t i = 0; i < linesNum; i++)
        {
            for (size_t j = 0; j < layerSize; j++)
            {
                file_w << fixed << weights[i][j] << endl;
            }
        }
        file_w.close();
    }

    void clear()
    {
        delete[] layer;
        delete[] sigma;
    }

    void clearWeights()
    {
        for (size_t i = 0; i < linesNum; i++)
        {
            delete[] weights[i];
        }
    }

//private:
    size_t linesNum;
    double** weights;

    void matrixMultiplication(size_t M1_str, double** M1, size_t same, double** M2, size_t M2_col, double** result)
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