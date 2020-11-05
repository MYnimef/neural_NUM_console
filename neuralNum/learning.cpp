#include <iostream>

void random_weights(int n, int m, double** w);
void set_weights(int n, int m, double** w);
double sigmoidFunction(double x);
void forwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* secondLayer);
void backwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* sigma_second, double* sigma_first);

using namespace std;

void neural_learning(int trainSet, int input_col, double** input, int output_col, double** output)
{
    int n = 5;    //Кол-во нейронов в скрытом слое
    int hiddenLayers_amount; //Кол-во скрытых слоев
    double k = 0.3;  //Скорость обучения

    double** w_input = new double* [input_col];
    for (int count = 0; count < input_col; count++)
    {
        w_input[count] = new double [n];
    }

    double** w_output = new double* [n];
    for (int count = 0; count < n; count++)
    {
        w_output[count] = new double[output_col];
    }

    random_weights(input_col, n, w_input);    //Придание им рандомных значений
    random_weights(n, output_col, w_output);

    int maxEpoch = 100000; //Кол-во Эпох
    int delta_load = maxEpoch / 10, loading = delta_load;   //Переменные для реализации "загрузки"
    for (int epoch = 0; epoch < maxEpoch; epoch++)   //Начало работы самой нейросети 
    {
        if ((epoch + 1) == loading) //Собственно сама загрузка, 10 звездочек в консоле - финал обучения
        {
            cout << '*';
            loading += delta_load;
        }

        for (int train = 0; train < trainSet; train++)
        {
            //Forward propagation

            double* hiddenLayer = new double[n];
            forwardPropagation(input_col, input[train], w_input, n, hiddenLayer);

            double* result = new double[output_col];
            forwardPropagation(n, hiddenLayer, w_output, output_col, result);

            //Backward propagation

            double* sigma_out = new double[output_col];
            sigma_out[0] = (output[train][0] - result[0]) * result[0] * (1 - result[0]);     //Погрешность суммы до выхода, использование производной функции преобразования
            delete[] result;

            double* sigma_in = new double[n];
            backwardPropagation(n, hiddenLayer, w_output, output_col, sigma_out, sigma_in);

            //Корректировка весов
            
            double* delta_w_output = new double[n];
            for (int i = 0; i < n; i++)
            {
                delta_w_output[i] = k * sigma_out[0] * hiddenLayer[i];
                w_output[i][0] += delta_w_output[i];
            }
            delete[] sigma_out;
            delete[] delta_w_output;
            delete[] hiddenLayer;

            double** delta_w = new double* [input_col];
            for (int count = 0; count < input_col; count++)
            {
                delta_w[count] = new double [n];
            }

            for (int i = 0; i < input_col; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    delta_w[i][j] = k * sigma_in[j] * input[train][i];
                    w_input[i][j] += delta_w[i][j];
                }
            }
            delete[] sigma_in;
            delete[] delta_w;
        }
    }
    cout << endl;
    set_weights(input_col, n, w_input);
    set_weights(n, 1, w_output);

    for (int count = 0; count < input_col; count++)
    {
        delete[] w_input[count];
    }
    for (int count = 0; count < n; count++)
    {
        delete[] w_output[count];
    }
}

void forwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* secondLayer)
{
    for (int i = 0; i < size_of_secondLayer; i++)
    {
        double sum = 0;
        for (int j = 0; j < size_of_firstLayer; j++)
        {
            sum += firstLayer[j] * weights[j][i];
        }
        secondLayer[i] = sigmoidFunction(sum);
    }
}

void backwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* sigma_second, double* sigma_first)
{
    for (int i = 0; i < size_of_firstLayer; i++)
    {
        double sigma_in = 0;
        for (int j = 0; j < size_of_secondLayer; j++)
        {
            sigma_in += sigma_second[j] * weights[i][j];
        }
        sigma_first[i] = sigma_in * firstLayer[i] * (1 - firstLayer[i]);
    }
}