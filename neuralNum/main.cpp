#include <iostream>
#include <fstream>
#include <ctime>
#include "Neuron.h"

using namespace std;

void setTrainInOut(size_t trainSet, double** input, double** output);
void neural_learning(size_t trainSet, size_t* neuronNum, size_t hiddenLayersAmount, double** input, double** output);

void getInput(double* input, char* filename);
void neuralNetwork(size_t* neuronNum, size_t hiddenLayersAmount, double* input, double* result);
void getWeights(size_t size, Neuron* obj, size_t* neuronNum);

bool mojemPovtorit();

int main()
{
    size_t trainSet = 1000;    //Number of train sets (for learning).
    size_t inputNum = 784, outputNum = 10; //Number of input and output values.
    size_t hiddenLayersAmount = 2;  //Number of hidden layers.
    size_t neuronNum[] = { inputNum, 200, 100, outputNum };    //Number of neurons in each layer.

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
                for (size_t j = 0; j < outputNum; j++)
                {
                    output[count][j] = 0;
                }
            }

            setTrainInOut(trainSet, input, output);
            cout << "Got train values!" << endl;

            clock_t start = clock();    //For calculating time of learning process
            neural_learning(trainSet, neuronNum, hiddenLayersAmount, input, output);    //learning
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

        double* in = new double[inputNum];
        char filename[] = "try5.png";
        getInput(in, filename);
        for (size_t i = 0; i < inputNum; i++)
        {
            if (in[i] == 1)
            {
                cout << '1' << " ";
            }
            else
            {
                cout << "  ";
            }
            if ((i + 1) % 28 == 0)
            {
                cout << endl;
            }
        }

        double* result = new double[outputNum];
        neuralNetwork(neuronNum, hiddenLayersAmount, in, result);
        delete[] in;

        for (size_t i = 0; i < outputNum; i++)
        {
            //cout << result[i] << " ";
            if (result[i] > 0.8)
            {
                cout << i;
            }
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
    for (size_t i = 1; i <= hiddenLayersAmount; i++)
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