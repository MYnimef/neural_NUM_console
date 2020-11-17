#include <iostream>
#include <fstream>
#include "Neuron.h"
#include "ohMy.cpp"

void getInfo(int* trainSet, int* input_col, int* output_col);
void getInput(int trainSet, int input_col, double** input);
void getOutput(int trainSet, int output_col, double** output);

void neural_learning(int trainSet, int input_col, double** input, int output_col, double** output);

using namespace std;

void neuralNetwork(double* input, double* result);
void getWeights(size_t size, Neuron* obj, size_t* neuronNum);

int main()
{
    cout << "This is the nerural network that makes digit recognition." << endl;
    bool task = true;
    while (task)
    {
        ifstream file_w("weights.txt");
        if (!file_w.is_open())  //Если файл не открыт
        {
            int trainSet, input_col, output_col;
            getInfo(&trainSet, &input_col, &output_col);

            double** input = new double* [trainSet];
            for (int count = 0; count < trainSet; count++)
            {
                input[count] = new double[input_col];
            }

            double** output = new double* [trainSet];
            for (int count = 0; count < trainSet; count++)
            {
                output[count] = new double[output_col];
            }

            getInput(trainSet, input_col, input);
            getOutput(trainSet, output_col, output);

            neural_learning(trainSet, input_col, input, output_col, output);

            for (int count = 0; count < trainSet; count++)
            {
                delete[] input[count];
                delete[] output[count];
            }
        }
        else
        {
            file_w.close();
        }

        cout << "Enter x1, x2: ";
        double x[2];
        cin >> x[0] >> x[1];

        double* result = new double[1];
        neuralNetwork(x, result);
        for (size_t i = 0; i < 1; i++)
        {
            cout << result[i] << " ";
        }
        cout << endl;
        delete[] result;

        task = mojemPovtorit();
    }
    return 0;
}

void neuralNetwork(double* input, double* result)
{
    size_t hiddenLayersAmount = 2;  //Кол-во скрытых слоев
    size_t neuronNum[] = { 2, 5, 5, 1 };    //Кол-во нейронов в каждом слое

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
