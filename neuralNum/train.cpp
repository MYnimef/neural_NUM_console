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

void getInput(size_t trainSet, size_t inputNum, double** input)
{
    ifstream file("XOR_input.txt");
    for (size_t i = 0; i < trainSet; i++)
    {
        for (size_t j = 0; j < inputNum; j++)
        {
            file >> input[i][j];
        }
    }
    file.close();
}

void getOutput(size_t trainSet, size_t outputNum, double** output)
{
    ifstream file("XOR_output.txt");
    for (size_t i = 0; i < trainSet; i++)
    {
        for (size_t j = 0; j < outputNum; j++)
        {
            file >> output[i][j];
        }
    }
    file.close();
}