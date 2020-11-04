#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void random_weights(int n, int m, double** w)
{
    srand(time(0));     //Настройка генерации чисел от времени
    for (int i = 0; i < n; i++)     //Цикл, присваивающий рандомные значения весам (диапазон от -0.5 до 0.5)
    {
        for (int j = 0; j < m; j++)
        {
            w[i][j] = (5.0 - rand() % 10) * 0.1;
        }
    }
}

void get_weights(const int n, double w1[], double w2[], double w3[])
{
    ifstream file_w("weights.txt");  //
    for (int i = 0; i < 3 * n; i++)
    {
        string num;
        file_w >> num;
        if (i < n)
        {
            w1[i] = stof(num);
        }
        else if (i < 2 * n)
        {
            w2[i - n] = stof(num);
        }
        else
        {
            w3[i - 2 * n] = stof(num);
        }
    }
    file_w.close();
}

void set_weights(int n, int m, double** w)
{
    ofstream file_w("weights.txt", ios_base::app);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            file_w << fixed << w[i][j] << endl;
        }
    }
    file_w.close();
}