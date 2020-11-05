#include <iostream>

void random_weights(int n, int m, double** w);
void set_weights(int n, int m, double** w);
double sigmoidFunction(double x);
void forwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* secondLayer);
void backwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* sigma_second, double* sigma_first);

using namespace std;

void neural_learning()
{
    const int in = 2;   //���-�� �������� �� �����
    const int trainSet = 4; //���-�� ������������� �����
    const int n = 5;    //���-�� �������� � ������� ����
    double k = 0.3;  //�����������

    double input[trainSet][in] =   //�������� �� �����
    {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    int output[trainSet] =  //��������� ��������� ������ �� ������ ������� �� ����� (XOR)
    {
        0,
        1,
        1,
        0
    };

    double** w_input = new double* [in];
    for (int count = 0; count < in; count++)
    {
        w_input[count] = new double [n];
    }

    double** w_output = new double* [n];
    for (int count = 0; count < n; count++)
    {
        w_output[count] = new double[1];
    }

    random_weights(in, n, w_input);    //�������� �� ��������� ��������
    random_weights(n, 1, w_output);

    int maxEpoch = 100000; //���-�� ����
    int delta_load = maxEpoch / 10, loading = delta_load;   //���������� ��� ���������� "��������"
    for (int epoch = 0; epoch < maxEpoch; epoch++)   //������ ������ ����� ��������� 
    {
        if ((epoch + 1) == loading) //���������� ���� ��������, 10 ��������� � ������� - ����� ��������
        {
            cout << '*';
            loading += delta_load;
        }

        for (int train = 0; train < trainSet; train++)
        {
            //Forward
            double hiddenLayer[n];
            forwardPropagation(in, input[train], w_input, n, hiddenLayer);

            double result[1];
            forwardPropagation(n, hiddenLayer, w_output, 1, result);

            //Backward

            double sigma_out[1];
            sigma_out[0] = (output[train] - result[0]) * result[0] * (1 - result[0]);     //����������� ����� �� ������, ������������� ����������� ������� ��������������
            double sigma_in[n];
            backwardPropagation(n, hiddenLayer, w_output, 1, sigma_out, sigma_in);

            double delta_w_output[n];
            for (int i = 0; i < n; i++)
            {
                delta_w_output[i] = k * sigma_out[0] * hiddenLayer[i];
                w_output[i][0] += delta_w_output[i];
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

            /*

            double sigma_out = (output[train] - result[0]) * result[0] * (1 - result[0]);     //����������� ����� �� ������, ������������� ����������� ������� ��������������
            double delta_w_output[n], sigma_in[n];
            for (int i = 0; i < n; i++)
            {
                delta_w_output[i] = k * sigma_out * hiddenLayer[i];
                sigma_in[i] = delta_w_output[i] * w_output[i][0] * hiddenLayer[i] * (1 - hiddenLayer[i]);        //��� ��� ��� �������
                //sigma_in[i] = (output[train] - result) * w_output[i] * hiddenLayer[i] * (1 - hiddenLayer[i]);   //���������

                w_output[i][0] += delta_w_output[i];
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

            */
        }
    }
    cout << endl;
    set_weights(in, n, w_input);
    set_weights(n, 1, w_output);

    for (int count = 0; count < in; count++)
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