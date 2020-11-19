#include <iostream>
#include <fstream>
#include <ctime>
#include "Neuron.h"

void getInput(size_t trainSet, size_t inputNum, double** input);
void getOutput(size_t trainSet, size_t outputNum, double** output);

void neural_learning(size_t trainSet, size_t* neuronNum, size_t hiddenLayersAmount, double** input, double** output);

using namespace std;

void neuralNetwork(size_t* neuronNum, size_t hiddenLayersAmount, double* input, double* result);
void getWeights(size_t size, Neuron* obj, size_t* neuronNum);

bool mojemPovtorit();

int main()
{
    size_t trainSet = 4;    //Number of train sets (for learning).
    size_t inputNum = 2, outputNum = 1; //Number of input and output values.
    size_t hiddenLayersAmount = 1;  //Number of hidden layers.
    size_t neuronNum[] = { inputNum, 5, outputNum };    //Number of neurons in each layer.

    cout << "This is the nerural network that makes digit recognition." << endl;
    bool task = true;
    while (task)
    {
        ifstream file_w("weights.txt");
        if (!file_w.is_open())  //If file is not opened.
        {
            double** input = new double* [trainSet];
            double** output = new double* [trainSet];
            for (size_t count = 0; count < trainSet; count++)
            {
                input[count] = new double[inputNum];
                output[count] = new double[outputNum];
            }

            getInput(trainSet, inputNum, input);
            getOutput(trainSet, outputNum, output);

            clock_t start = clock();    //For calculating time of learning process
            neural_learning(trainSet, neuronNum, hiddenLayersAmount, input, output);    //leraning
            cout << "Time - " << ((double) clock() - start) / (double)CLOCKS_PER_SEC << " (sec)." << endl;

            for (size_t count = 0; count < trainSet; count++)
            {
                delete[] input[count];
                delete[] output[count];
            }
        }
        else
        {
            file_w.close();
        }

        cout << "Enter " << inputNum << " values: ";
        double* in = new double[inputNum];
        for (size_t i = 0; i < inputNum; i++)
        {
            cin >> in[i];
        }

        double* result = new double[outputNum];
        neuralNetwork(neuronNum, hiddenLayersAmount, in, result);
        delete[] in;

        for (size_t i = 0; i < outputNum; i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
        delete[] result;

        task = mojemPovtorit();
    }
    return 0;
}

void neuralNetwork(size_t* neuronNum, size_t hiddenLayersAmount, double* input, double* result)
{
    Neuron* perceptron = new Neuron[hiddenLayersAmount + 1];
    getWeights(hiddenLayersAmount + 1, perceptron, neuronNum);

    perceptron[0].forwardPropagation(input);
    perceptron[0].clearWeights();
    for (size_t i = 1; i < hiddenLayersAmount + 1; i++)
    {
        perceptron[i].forwardPropagation(perceptron[i - 1].layer);
        perceptron[i].clearWeights();
    }
    for (size_t i = 0; i < perceptron[hiddenLayersAmount].columnsNum; i++)
    {
        result[i] = perceptron[hiddenLayersAmount].layer[i];
    }
    delete[] perceptron;
}