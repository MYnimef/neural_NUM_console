#include <iomanip>
#include <fstream>
#include <string>
#include "Neuron.h"

using namespace std;

void getWeights(size_t size, Neuron* obj, size_t* neuronNum)
{
    ifstream file_w("weights.txt");  //

    for (size_t s = 0; s < size; s++)
    {
        obj[s].linesNum = neuronNum[s];
        obj[s].columnsNum = neuronNum[s + 1];

        obj[s].weights = new double* [neuronNum[s]];
        for (size_t i = 0; i < neuronNum[s]; i++)
        {
            obj[s].weights[i] = new double[neuronNum[s + 1]];
            for (size_t j = 0; j < neuronNum[s + 1]; j++)
            {
                string num;
                file_w >> num;
                obj[s].weights[i][j] = stof(num);
            }
        }
    }

    file_w.close();
}

void setWeights(size_t linesNum, size_t columnsNum, double** weights)
{
    ofstream file_w("weights.txt", ios_base::app);
    for (size_t i = 0; i < linesNum; i++)
    {
        for (size_t j = 0; j < columnsNum; j++)
        {
            file_w << fixed << weights[i][j] << endl;
        }
    }
    file_w.close();
}