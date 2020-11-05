#include <fstream>

using namespace std;

void getInfo(int *trainSet, int *input_col, int *output_col)
{
    ifstream file("XOR_info.txt");
    file >> *trainSet;
    file >> *input_col;
    file >> *output_col;
    file.close();
}

void getInput(int trainSet, int input_col, double** input)
{
    ifstream file("XOR_input.txt");
    for (int i = 0; i < trainSet; i++)
    {
        for (int j = 0; j < input_col; j++)
        {
            file >> input[i][j];
        }
    }
    file.close();
}

void getOutput(int trainSet, int output_col, double** output)
{
    ifstream file("XOR_output.txt");
    for (int i = 0; i < trainSet; i++)
    {
        for (int j = 0; j < output_col; j++)
        {
            file >> output[i][j];
        }
    }
    file.close();
}