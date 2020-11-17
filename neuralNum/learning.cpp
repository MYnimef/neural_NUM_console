#include <iostream>
#include "Neuron.h"

using namespace std;

void setWeights(size_t linesNum, size_t columnsNum, double** weights);

void neural_learning(int trainSet, int input_col, double** input, int output_col, double** output)
{
    size_t hiddenLayersAmount = 2;  //Кол-во скрытых слоев
    size_t neuronNum[] = {input_col, 5, 5, output_col};    //Кол-во нейронов в каждом слое
    double k = 0.3;  //Скорость обучения

    Neuron* perceptron = new Neuron[hiddenLayersAmount + 1];
    for (size_t i = 0; i < hiddenLayersAmount + 1; i++)
    {
        perceptron[i].setRandomWeights(neuronNum[i], neuronNum[i + 1]);
    }

    size_t maxEpoch = 100000; //Кол-во Эпох
    size_t delta_load = maxEpoch / 10, loading = delta_load;   //Переменные для реализации "загрузки"
    for (size_t epoch = 0; epoch < maxEpoch; epoch++)   //Начало работы самой нейросети 
    {
        if ((epoch + 1) == loading) //Собственно сама загрузка, 10 звездочек в консоле - финал обучения
        {
            cout << '*';
            loading += delta_load;
        }

        for (size_t train = 0; train < trainSet; train++)
        {
            //Forward propagation
            perceptron[0].forwardPropagation(input[train]);
            for (size_t i = 1; i < hiddenLayersAmount + 1; i++)
            {
                perceptron[i].forwardPropagation(perceptron[i - 1].layer);
            }

            //Backward propagation
            perceptron[hiddenLayersAmount].mistake(output[train]);
            for (size_t i = hiddenLayersAmount; i > 0; i--)
            {
                perceptron[i - 1].backwardPropagation(perceptron[i].columnsNum, perceptron[i].weights, perceptron[i].sigma);
            }

            //Корректировка весов
            perceptron[0].changeWeights(k, input[train]);
            for (size_t i = 1; i < hiddenLayersAmount + 1; i++)
            {
                perceptron[i].changeWeights(k, perceptron[i - 1].layer);
            }

            for (size_t i = 0; i < hiddenLayersAmount + 1; i++)
            {
                perceptron[i].clear();
            }
        }
    }
    cout << endl;

    for (size_t i = 0; i < hiddenLayersAmount + 1; i++)
    {
        setWeights(perceptron[i].linesNum, perceptron[i].columnsNum, perceptron[i].weights);
        perceptron[i].clearWeights();
    }

    delete[] perceptron;
}