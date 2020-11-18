#include <iostream>
#include "Neuron.h"

using namespace std;

void setWeights(size_t size, Neuron* obj);

void neural_learning(size_t trainSet, size_t* neuronNum, size_t hiddenLayersAmount, double** input, double** output)
{
    double k = 0.3;  //�������� ��������
    Neuron* perceptron = new Neuron[hiddenLayersAmount + 1];
    for (size_t i = 0; i <= hiddenLayersAmount; i++)
    {
        perceptron[i].setRandomWeights(neuronNum[i], neuronNum[i + 1]);
    }

    size_t maxEpoch = 100000; //���-�� ����
    size_t delta_load = maxEpoch / 10, loading = delta_load;   //���������� ��� ���������� "��������"
    for (size_t epoch = 0; epoch < maxEpoch; epoch++)   //������ ������ ����� ��������� 
    {
        if ((epoch + 1) == loading) //���������� ���� ��������, 10 ��������� � ������� - ����� ��������
        {
            cout << '*';
            loading += delta_load;
        }

        for (size_t train = 0; train < trainSet; train++)
        {
            //Forward propagation
            perceptron[0].forwardPropagation(input[train]);
            for (size_t i = 1; i <= hiddenLayersAmount; i++)
            {
                perceptron[i].forwardPropagation(perceptron[i - 1].layer);
            }

            //Backward propagation
            perceptron[hiddenLayersAmount].mistake(output[train]);
            for (size_t i = hiddenLayersAmount; i > 0; i--)
            {
                perceptron[i - 1].backwardPropagation(perceptron[i].columnsNum, perceptron[i].weights, perceptron[i].sigma);
            }

            //������������� �����
            perceptron[0].changeWeights(k, input[train]);
            for (size_t i = 1; i <= hiddenLayersAmount; i++)
            {
                perceptron[i].changeWeights(k, perceptron[i - 1].layer);
            }

            for (size_t i = 0; i <= hiddenLayersAmount; i++)
            {
                perceptron[i].clear();
            }
        }
    }
    cout << endl;

    setWeights(hiddenLayersAmount + 1, perceptron);
    delete[] perceptron;
}