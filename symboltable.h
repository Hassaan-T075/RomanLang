#include <iostream>
#include <fstream>
using namespace std;

class symboltable
{
public:
    string **table;
    int index = 0;
    int max_size = 2;

    symboltable()
    {

        table = new string *[max_size];

        for (int i = 0; i < max_size; i++)
        {
            table[i] = new string[2];
        }

        for (int i = 0; i < max_size; i++)
        {
            table[i][0] = " ";
            table[i][1] = " ";
        }
    }

    void insert_item(string name, string type)
    {
        for (int i = 0; i < index; i++)
        {
            if (table[i][0] == name)
                return;
        }
        if (index < max_size)
        {
            table[index][0] = name;
            table[index][1] = type;
            index++;
        }
        else
        {
            int new_size = max_size * 2;
            string **new_table;
            new_table = new string *[new_size];
            for (int i = 0; i < new_size; i++)
            {

                new_table[i] = new string[2];
            }

            for (int i = 0; i < new_size; i++)
            {
                new_table[i][0] = " ";
                new_table[i][1] = " ";
            }
            for (int i = 0; i < max_size; i++)
            {
                new_table[i][0] = table[i][0];
                new_table[i][1] = table[i][1];
            }

            for (int i = 0; i < max_size; i++)
            {
                delete[] table[i];
            }
            delete[] table;
            table = new_table;
            max_size = new_size;

            table[index][0] = name;
            table[index][1] = type;
            index++;
        }
    }

    void print_table()
    {
        // write to output file
        ofstream fil;
        fil.open("symbol_table.txt");

        fil << "     ---SYMBOL TABLE---\n\n";

        for (int i = 0; i < index; i++)
        {
            fil << "name: " << table[i][0] << "    type: " << table[i][1] << "\n";
        }

        fil.close();
    }

    ~symboltable()
    {
        for (int i = 0; i < max_size; i++)
        {
            delete[] table[i];
        }
        delete[] table;
    }
};
