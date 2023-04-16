#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    fstream fin;
    fin.open("tac.txt", ios::in);

    string data, newdata;
    // while(fin)
    // {
    //     getline(fin, data);
    //     cout<<data<<"\n";
    // }
    fin.close();

    fin.open("tac.txt", ios::in);
    newdata = "";
    bool found = true;

    while (fin)
    {
        getline(fin, data);
        int a = (int) data.find("goto", 0);
        if (a != string::npos && found)
        {
            data.replace(a, strlen("goto"), "vectored");
            found = false;
        }
        newdata = newdata + data + "\n";
    }
    fin.close();

    fin.open("tac.txt", ios::out);

    fin << newdata;

    fin.close();
}