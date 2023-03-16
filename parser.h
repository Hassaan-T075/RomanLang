#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
// for future assignments leave it as it is

class symboltable
{

public:
    string table[100][2];
    int index = 0;

    symboltable()
    {

        for (int i = 0; i < 100; i++)
        {
            table[i][0] = " ";
            table[i][1] = " ";
        }
    }

    void insert_item(string name, string type)
    {
        for (int i = 0; i <= index; i++)
        {
            if (table[i][0] == name)
                return;
        }
        table[index][0] = name;
        table[index][1] = type;
        index++;
    }

    void print_table()
    {

        for (int i = 0; i < index; i++)
        {
            cout << "name: " << table[i][0] << "    type: " << table[i][1] << endl;
        }
    }
};

class parser
{
public:
    lexer _lexer;
    token l;
    int tabs = 0;
    symboltable smt;

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
    void ptabs(string n);
};
#endif
