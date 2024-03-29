﻿#include <iostream>
#include <fstream>
#include <ctime>
#include "Neuron.h"

using namespace std;

void setTrainInOut(size_t trainSet, double** input, double** output);
void neural_learning(size_t trainSet, size_t* neuronNum, size_t hiddenLayersAmount, double** input, double** output);

void getInput(double* input, char* filename);
void neuralNetwork(size_t* neuronNum, size_t hiddenLayersAmount, double* input, double* result);
void getWeights(size_t size, Neuron* obj, size_t* neuronNum);

void outNum(size_t size, double* num);  //Draws num from png to console.

void sayHi();
bool mojemPovtorit();

int main() {
    sayHi();
    cout << "This is the neural network that makes digit recognition." << endl
         << "Used lodepng libraries for PNG decode" << endl;

    size_t trainSet = 1000;    //Number of train sets (for learning).
    size_t inputNum = 784, outputNum = 10; //Number of input and output values.
    size_t hiddenLayersAmount = 2;  //Number of hidden layers.
    size_t neuronNum[] = { inputNum, 200, 50, outputNum };    //Number of neurons in each layer.

    bool task = true;
    while (task) {
        ifstream file_w("weights.txt");
        if (!file_w.is_open()) {
            double** input = new double* [trainSet];
            double** output = new double* [trainSet];

            for (size_t count = 0; count < trainSet; count++) {
                input[count] = new double[inputNum];
                output[count] = new double[outputNum];
                for (size_t j = 0; j < outputNum; j++)
                {
                    output[count][j] = 0;
                }
            }

            setTrainInOut(trainSet, input, output);
            cout << "Got train values!" << endl;

            clock_t start = clock();    //For calculating the duration of learning process
            neural_learning(trainSet, neuronNum, hiddenLayersAmount, input, output);    //learning
            cout << "Time - " << ((double) clock() - start) / (double)CLOCKS_PER_SEC << " (sec)." << endl;  //Tells us how long it was.

            for (size_t count = 0; count < trainSet; count++) {
                delete[] input[count];
                delete[] output[count];
            }
        } else {
            file_w.close();
        }

        char filename[] = "try\\try0.png";
        for (size_t i = 0; i <= 9; i++) {
            double* in = new double[inputNum];
            getInput(in, filename);
            outNum(inputNum, in);

            double* result = new double[outputNum];
            neuralNetwork(neuronNum, hiddenLayersAmount, in, result);
            delete[] in;

            for (size_t j = 0; j < outputNum; j++) {
                //cout << result[j] << " ";
                if (result[j] > 0.8) {
                    cout << "Result is " << j << ".";
                }
            }
            cout << endl;
            delete[] result;

            filename[7]++;
        }
        task = mojemPovtorit();
    }
    return 0;
}

void outNum(size_t size, double* num) {
    for (size_t i = 0; i < size; i++) {
        if (num[i] == 1) {
            cout << '1' << " ";
        } else {
            cout << "  ";
        }

        if ((i + 1) % 28 == 0) {
            cout << endl;
        }
    }
}

void neuralNetwork(size_t* neuronNum, size_t hiddenLayersAmount, double* input, double* result) {
    Neuron* perceptron = new Neuron[hiddenLayersAmount + 1];
    getWeights(hiddenLayersAmount + 1, perceptron, neuronNum);

    perceptron[0].forwardPropagation(input);
    perceptron[0].clearWeights();
    for (size_t i = 1; i <= hiddenLayersAmount; i++) {
        perceptron[i].forwardPropagation(perceptron[i - 1].layer);
        perceptron[i].clearWeights();
    }

    for (size_t i = 0; i < perceptron[hiddenLayersAmount].columnsNum; i++) {
        result[i] = perceptron[hiddenLayersAmount].layer[i];
    }

    delete[] perceptron;
}