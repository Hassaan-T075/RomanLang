#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <fstream>
// for future assignments leave it as it is

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

class parser
{
public:
    lexer _lexer;
    int tabs = 0;
    symboltable smt; //parser's symboltable data member
    int no_of_lines = 1;

public:
    void syntax_error();
    token expect(TokenType expected_type);
    parser(const char filename[]);
    void readAndPrintAllInput();
    void resetPointer();
    /*Terminal functions goes here use peek and expect*/
    /*use TokenType:: for token names for example
        expect(TokenType::ASSIGN);   //example function call
      */
    // all your parser function goes here
    void start();
    void _main();
    void func();
    void functype();
    void params();
    void sep();
    void args();
    void args_();
    void statements();
    void blks();
    void fblke();
    void blke();
    void vartype();
    void declare();
    void declare_();
    void declare__();
    void val();
    void input();
    void input_();
    void output();
    void output_();
    void output__();
    void out_();
    void loop();
    void exp();
    void exp_();
    void R();
    void P();
    void expval();
    void rel();
    void _if();
    void _elseif();
    void _else();
    void ret();
    void ret_();

    //helper functions
    void ptabs(string n);
    void newline();
};
#endif
