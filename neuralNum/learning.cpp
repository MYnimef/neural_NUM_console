#include <iostream>

void random_weights(const int n, double w1[], double w2[], double w3[]);
void set_weights(const int n, double w1[], double w2[], double w3[]);
double sigmoidFunction(double x);
void forwardPropagation(int size_of_firstLayer, double firstLayer[], double** weights, int size_of_secondLayer, double* secondLayer);

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

    random_weights(n, w_input[0], w_input[1], w_output[0]);    //�������� �� ��������� ��������

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
            double hiddenLayer[n] = {};
            forwardPropagation(in, input[train], w_input, n, hiddenLayer);

            double result[1] = {};
            forwardPropagation(n, hiddenLayer, w_output, 1, result);

            //Backward

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
        }
    }
    cout << endl;
    set_weights(n, w_input[0], w_input[1], w_output[0]);

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

void backwardPropagation()
{

}