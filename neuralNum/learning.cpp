#include <iostream>

//#include <A:\\Coding\\Cpp\\Git\\neural_NUM_console\\neuralNum\\function.cpp> 
//#include <A:\\Coding\\Cpp\\Git\\neural_NUM_console\\neuralNum\\weights.cpp> 

void random_weights(const int n, double w1[], double w2[], double w3[]);
void set_weights(const int n, double w1[], double w2[], double w3[]);
double sigmoidFunction(double x);

using namespace std;

void neural_learning()
{
    const int in = 2;   //���-�� �������� �� �����
    const int trainSet = 4; //���-�� ������������� �����
    const int n = 5;    //���-�� �������� � ������� ����
    double k = 0.3;  //�����������

    int input[trainSet][in] =   //�������� �� �����
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

    double w_input[in][n], w_output[n]; //������� ������������ ����� ������ � ������� ����� � ����� ������� ����� � �������
    random_weights(n, w_input[0], w_input[1], w_output);    //�������� �� ��������� ��������

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

            double hiddenLayer[n], pre_result = 0;   //������ �������� �� �������� ����, � ������� ���� � ��, ��� �� ���� ������
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
            double result = sigmoidFunction(pre_result);   //�������� ���������
            //cout << result << endl;   //����� ��� ��������

            //Backward

            double sigma_out = (output[train] - result) * result * (1 - result);     //����������� ����� �� ������, ������������� ����������� ������� ��������������
            double delta_w_output[n], sigma_in[n];
            for (int i = 0; i < n; i++)
            {
                delta_w_output[i] = k * sigma_out * hiddenLayer[i];
                sigma_in[i] = delta_w_output[i] * w_output[i] * hiddenLayer[i] * (1 - hiddenLayer[i]);        //��� ��� ��� �������
                //sigma_in[i] = (output[train] - result) * w_output[i] * hiddenLayer[i] * (1 - hiddenLayer[i]);   //���������

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