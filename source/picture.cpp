#include <iostream>
#include <vector>
#include "lodepng.h"

using namespace std;

bool decodeOneStep(double* pic, const char* filename);
void count(size_t num, char* arr);

void setTrainInOut(size_t trainSet, double** input, double** output)
{
    char fileName[] = "train\\000000-num0.png";
    for (size_t i = 0; i < trainSet; i++)
    {
        size_t sup = 0;
        bool flag = true;
        while (flag) 
        {
            flag = decodeOneStep(input[i], fileName);
            fileName[19]++;
            sup++;
        }
        output[i][sup - 1] = 1;
        fileName[19] = '0';
        count(14, fileName);
    }
}

void count(size_t num, char* arr)
{
    arr[num]++;
    if (arr[num] == '9' + 1)
    {
        if (num >= 9)
        {
            count(num - 1, arr);
        }
        arr[num] = '0';
    }
}

void getInput(double* input, char* filename)
{
    bool flag = decodeOneStep(input, filename);
    if (flag)
    {
        cout << "Mistake! File is not opened so we set zero values." << endl;
        for (size_t i = 0; i < 784; i++)
        {
            input[i] = 0;
        }
    }
}

bool decodeOneStep(double* pic, const char* filename)   //Decode from disk to raw pixels with a single function call
{
    vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    
    unsigned error = lodepng::decode(image, width, height, filename);   //decode
    if (error)  //if there's an error, display it
    {
        return true;
    }
    else
    {
        size_t sup = 0;
        bool flag = false;
        for (size_t i = 0; i < image.size(); i++)
        {
            if ((i + 1) % 4 == 0)
            {
                pic[sup] = (flag ? 1 : 0);
                flag = false;
                sup++;
            }
            else if ((int)image[i] != 0)
            {
                flag = true;
            }
        }
        return false;
    }
}