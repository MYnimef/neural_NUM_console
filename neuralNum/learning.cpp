#include <iostream>

//#include <A:\\Coding\\Cpp\\Git\\neural_NUM_console\\neuralNum\\function.cpp> 
//#include <A:\\Coding\\Cpp\\Git\\neural_NUM_console\\neuralNum\\weights.cpp> 

void random_weights(const int n, double w1[], double w2[], double w3[]);
void set_weights(const int n, double w1[], double w2[], double w3[]);
double sigmoidFunction(double x);

using namespace std;

void neural_learning()
{
    const int in = 2;   //Кол-во нейронов на входе
    const int trainSet = 4; //Кол-во тренировочных сетов
    const int n = 5;    //Кол-во нейронов в скрытом слое
    double k = 0.3;  //Коэффициент

    int input[trainSet][in] =   //Значения на входе
    {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    int output[trainSet] =  //Ожидаемый результат работы на данных наборах на входе (XOR)
    {
        0,
        1,
        1,
        0
    };

    double w_input[in][n], w_output[n]; //Весовые коэффициенты между входом и скрытым слоем и между скрытым слоем и выходом
    random_weights(n, w_input[0], w_input[1], w_output);    //Придание им рандомных значений

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
            //Forward

            double hiddenLayer[n], pre_result = 0;   //Расчет значений до скрытого слоя, в скрытом слое и то, что из него выйдет
            for (int i = 0; i < n; i++)
            {
                double pre_hiddenLayer = 0;
                for (int j = 0; j < in; j++)
                {
                    pre_hiddenLayer += input[train][j] * w_input[j][i];
                }
                hiddenLayer[i] = sigmoidFunction(pre_hiddenLayer);
                pre_result += hiddenLayer[i] * w_output[i];
            }
            double result = sigmoidFunction(pre_result);   //Конечный результат
            //cout << result << endl;   //Чисто для проверки

            //Backward

            double sigma_out = (output[train] - result) * result * (1 - result);     //Погрешность суммы до выхода, использование производной функции преобразования
            double delta_w_output[n], sigma_in[n];
            for (int i = 0; i < n; i++)
            {
                delta_w_output[i] = k * sigma_out * hiddenLayer[i];
                sigma_in[i] = delta_w_output[i] * w_output[i] * hiddenLayer[i] * (1 - hiddenLayer[i]);        //Тут все еще ведутся
                //sigma_in[i] = (output[train] - result) * w_output[i] * hiddenLayer[i] * (1 - hiddenLayer[i]);   //дискуссии

                w_output[i] += delta_w_output[i];
            }

            double delta_w[in][n];
            for (int i = 0; i < in; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    delta_w[i][j] = k * sigma_in[j] * input[train][i];
                    w_input[i][j] += delta_w[i][j];
                }
            }
        }
    }
    cout << endl;
    set_weights(n, w_input[0], w_input[1], w_output);
}

void forwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double secondLayer[])
{

}

void backwardPropagation()
{

}