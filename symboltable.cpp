#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class symboltable
{
public:
    string **table;
    int index = 0;
    int max_size = 2;
    int addr_counter = 0;

    symboltable()
    {

        table = new string *[max_size];

        for (int i = 0; i < max_size; i++)
        {
            table[i] = new string[5];
        }

        for (int i = 0; i < max_size; i++)
        {
            table[i][0] = " ";
            table[i][1] = " ";
            table[i][2] = " ";
            table[i][3] = " ";
            table[i][4] = " ";
        }
    }

    void insert_item(string name, string type, int line = -1, string initialValue = "0", bool isFunc = 0)
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
            if (line == -1) // store memory addr
            {
                table[index][2] = to_string(addr_counter);
                if (type == "adad")
                {
                    addr_counter += 4;
                }
            }
            else
            { // store line

                table[index][2] = to_string(line);
            }
            table[index][3] = initialValue;
            table[index][4] = to_string(isFunc);
            index++;
        }
        else
        {
            int new_size = max_size * 2;
            string **new_table;
            new_table = new string *[new_size];
            for (int i = 0; i < new_size; i++)
            {

                new_table[i] = new string[5];
            }

            for (int i = 0; i < new_size; i++)
            {
                new_table[i][0] = " ";
                new_table[i][1] = " ";
                new_table[i][2] = " ";
                new_table[i][3] = " ";
                new_table[i][4] = " ";
            }
            for (int i = 0; i < max_size; i++)
            {
                new_table[i][0] = table[i][0];
                new_table[i][1] = table[i][1];
                new_table[i][2] = table[i][2];
                new_table[i][3] = table[i][3];
                new_table[i][4] = table[i][4];
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
            if (line == -1) // store memory addr
            {
                table[index][2] = to_string(addr_counter);
                if (type == "adad")
                {
                    addr_counter += 4;
                }
            }
            else
            { // store line

                table[index][2] = to_string(line);
            }
            table[index][3] = initialValue;
            table[index][4] = to_string(isFunc);
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
            fil << "name: " << table[i][0] << "    datatype: " << table[i][1] << "   addr: " << table[i][2] << "   initValue: " << table[i][3] << "  type -> isFunction? " << table[i][4] << "\n";
        }

        fil.close();
    }

    string find_addr(string addr)
    {
        for (int i = 0; i < index; i++)
        {
            // const char* tt = table[index][0].c_str();
            // const char* adr = addr.c_str();
            if(table[i][0] == addr)
                return table[i][2];
        }
        return "0";
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
#endif