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

        // int i = 0;
        // int oper = 0;
        // string arr[4] = {"","","",""};

        // for (i = 0; s[i] != '\0'; i++)
        // {
        //     if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) // string's character is identifier
        //     {
        //         string s;
        //         stringstream ss;
        //         ss << s[i];
        //         ss >> s;
        //         if (oper == 0)
        //         {
        //             arr[3] = vmst->find_addr(s);
        //             oper++;
        //         }
        //         else if (oper == 1)
        //         {
        //             arr[1] = vmst->find_addr(s);
        //             oper++;
        //         }
        //         else
        //             arr[2] = vmst->find_addr(s);
        //     }
        //     else if ((s[i] >= 60 && s[i] <= 62) || s[i] == 45 || s[i] == 43 || s[i] == 47 || s[i] == 42)
        //     {
        //         string s;
        //         stringstream ss;
        //         ss << s[i];
        //         ss >> s;
        //         arr[0] = to_string(opcode(s));
        //     }
        // }
        // for (size_t i = 0; i < 4; i++)
        // {
        //     cout << arr[i] << " ";
        // }

        // if (fil)
        // {
        //     fil<<"already\n";
        // }
        // else
        // {
        //     fil.open("mce.txt");
        //     fil << "     ---SYMBOL TABLE---\n\n";
        // }

        // fil << "name: " << table[i][0] << "    datatype: " << table[i][1] << "   addr: " << table[i][2] << "   initValue: " << table[i][3] << "  type -> isFunction? " << table[i][4] << "\n";

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