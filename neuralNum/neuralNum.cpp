#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ohMy.cpp"

void getInfo(int* trainSet, int* input_col, int* output_col);
void getInput(int trainSet, int input_col, double** input);
void getOutput(int trainSet, int output_col, double** output);

void neural_learning(int trainSet, int input_col, double** input, int output_col, double** output);
double sigmoidFunction(double x);
void get_weights(const int n, double w1[], double w2[], double w3[]);

using namespace std;

double neuralNetwork(int input[]);

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
            }
            for (int count = 0; count < trainSet; count++)
            {
                delete[] output[count];
            }
        }
        else
        {
            file_w.close();
        }

        cout << "Enter x1, x2: ";
        int x[2];
        cin >> x[0] >> x[1];

        cout << neuralNetwork(x) << endl;
        task = mojemPovtorit();
    }
    return 0;
}

double neuralNetwork(int input[])
{
    const int n = 5;    //Кол-во скрытых слоев
    const int in = 2;
    double w_input[in][n], w_output[n];
    get_weights(n, w_input[0], w_input[1], w_output);

    double hiddenLayer[n], pre_result = 0;
    for (int i = 0; i < n; i++)
    {
        double pre_hiddenLayer = 0;
        for (int j = 0; j < in; j++)
        {
            pre_hiddenLayer += input[j] * w_input[j][i];
        }
        hiddenLayer[i] = sigmoidFunction(pre_hiddenLayer);
        pre_result += hiddenLayer[i] * w_output[i];
    }
    return sigmoidFunction(pre_result);
}
