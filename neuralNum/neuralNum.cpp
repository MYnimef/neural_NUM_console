#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ohMy.cpp"

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
            int trainSet = 4;
            int input_col = 2;
            int output_col = 1;

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

            input[0][0] = 0; input[0][1] = 0;
            input[1][0] = 0; input[1][1] = 1;
            input[2][0] = 1; input[2][1] = 0;
            input[3][0] = 1; input[3][1] = 1;

            output[0][0] = 0;
            output[1][0] = 1;
            output[2][0] = 1;
            output[3][0] = 0;

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
