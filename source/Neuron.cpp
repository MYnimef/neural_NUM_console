#include "Neuron.h"

void Neuron::setRandomWeights(size_t n, size_t m) {
    linesNum = n, columnsNum = m;
    weights = new double* [linesNum];
    srand(time(0));

    for (size_t i = 0; i < linesNum; i++) {
        weights[i] = new double[columnsNum];

        for (size_t j = 0; j < columnsNum; j++) {
            weights[i][j] = (5.0 - rand() % 10) * 0.1;
        }
    }
}

void Neuron::forwardPropagation(double* previousLayer) {
    layer = new double[columnsNum];

    for (size_t i = 0; i < columnsNum; i++) {
        double sum = 0;

        for (size_t j = 0; j < linesNum; j++) {
            sum += previousLayer[j] * weights[j][i];
        }

        layer[i] = sigmoidFunction(sum);
    }
}

void Neuron::mistake(double* output) {
    sigma = new double[columnsNum];

    for (size_t i = 0; i < columnsNum; i++) {
        sigma[i] = (output[i] - layer[i]) * layer[i] * (1 - layer[i]);
    }
    delete[] layer;
}

void Neuron::backwardPropagation(size_t previousLayerSize, double** previousWeights, double* previousSigma, double k) {
    sigma = new double[columnsNum];
    for (size_t i = 0; i < columnsNum; i++) {
        double sigma_in = 0;

        for (size_t j = 0; j < previousLayerSize; j++) {
            sigma_in += previousSigma[j] * previousWeights[i][j];
            previousWeights[i][j] += k * previousSigma[j] * layer[i];
        }
        sigma[i] = sigma_in * layer[i] * (1 - layer[i]);
    }
    delete[] layer;
    delete[] previousSigma;
}

void Neuron::changeWeights(double k, double* previousLayer) {
    for (size_t i = 0; i < linesNum; i++) {
        for (size_t j = 0; j < columnsNum; j++) {
            weights[i][j] += k * sigma[j] * previousLayer[i];
        }
    }
    delete[] sigma;
}

void Neuron::clearWeights() {
    for (size_t i = 0; i < linesNum; i++) {
        delete[] weights[i];
    }
}

double Neuron::sigmoidFunction(double x) {
    return (1 / (1 + exp(-x)));
}