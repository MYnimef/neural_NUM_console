#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void random_weights(const int n, double w1[], double w2[], double w3[])
{
    srand(time(0));     //Настройка генерации чисел от времени
    for (int i = 0; i < n; i++)     //Цикл, присваивающий рандомные значения весам (диапазон от -0.5 до 0.5)
    {
        w1[i] = (5.0 - rand() % 10) * 0.1;     //Вес от первого входа до скрытого слоя
        w2[i] = (5.0 - rand() % 10) * 0.1;     //Вес от второго входа до скрытого слоя
        w3[i] = (5.0 - rand() % 10) * 0.1;     //Вес от скрытого слоя до выхода
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

void set_weights(const int n, double w1[], double w2[], double w3[])
{
    ofstream file_w("weights.txt");
    for (int i = 0; i < 3 * n; i++)
    {
        if (i < n)
        {
            file_w << fixed << w1[i] << endl;
        }
        else if (i < 2 * n)
        {
            file_w << fixed << w2[i - n] << endl;
        }
        else
        {
            file_w << fixed << w3[i - 2 * n] << endl;
        }
    }
    file_w.close();
}