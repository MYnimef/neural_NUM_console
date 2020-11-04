#include <iostream>

using namespace std;

bool mojemPovtorit()
{
    bool task = true;
    char hm;
    cout << "Wanna do that again? (Y/N): ";
    cin >> hm;
    if (hm == 'N' || hm == 'n')
    {
        task = false;
    }
    else if (hm != 'Y' && hm != 'y')
    {
        cout << "Alright, Joker, I'll do that again coz I want you to spend your time." << endl;
    }
    return task;
}