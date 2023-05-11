#include <iostream>
#include <fstream>
#include <string>
#include "symboltable.cpp"
#include <sstream>
using namespace std;

class vm
{
public:
    // symboltable vmst;
    int quad[100][4];
    int *ds = new int[100];
    symboltable *vmst;

public:
    vm()
    {
    }

    void machine_code(const char filename[])
    {
        string text;
        ifstream fil(filename);
        int i = 1;
        while (getline(fil, text))
        {
            // Output the text from the file
            // cout << text << "\n";
            if (i == 1)
                mce(text);
            i++;
        }

        // Close the file
        fil.close();
    }

    // int lookup(string x)
    // {

    // }

    void mce(string s)
    {
        ofstream fil;

        fil.open("mce.txt", std::ios_base::app);

        fil << s << "\n";

        fil.close();
    }

    int opcode(string s)
    {
        if (s == "+")
            return 10;
        else if (s == "-")
            return 20;
        else if (s == "/")
            return 30;
        else if (s == "*")
            return 40;
        else if (s == "=")
            return 100;
    }
};

// int quad[..][4];
// ...
// int* ds = new int[..];
// ...
// for (int pc = 0; pc < quadSize(); ++pc) {
// switch (quad[pc][0]) {
// case ‘+’: ...
// case ‘-’: ...
// case GOTO: ...
// case GE: ...
// case GT: ...
// case IN: ...
// case OUT: ...
// ...
// }
// }
// case ‘+’:
// int i = quad[pc][1];
// int j = quad[pc][2];
// int k = quad[pc][3];
// ds[k] = ds[i] + ds[j];
// break;
// // e.g. ‘+’ 10 14 18
// case GOTO:
// pc = quad[pc][1] - 1;
// break;
// // goto 100
// case GE:
// int i = quad[pc][1];
// int j = quad[pc][2];
// int k = quad[pc][3];
// if (ds[i] >= ds[j])
// pc = k - 1;
// break;
// // e.g. if x >= y goto 100
// // GE &x &y 100
// case IN:
// int i = quad[pc][1];
// cin >> ds[i];
// break;
// // in x