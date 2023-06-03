#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
#include <fstream>
#include <string.h>
#include "symboltable.cpp"
#include "vm.cpp"
#include <vector>
#include <sstream>
// for future assignments leave it as it is

class parser
{
public:
    lexer _lexer;
    int tabs = 0;
    symboltable smt; // parser's symboltable data member
    int no_of_lines = 1;
    string entry;
    int nl = 1;
    int tmp_count = 0;
    int tmp_count_1 = 0;
    vm v;
    string formal_param[10];
    int param_count = 0;
    int actual_count = 0; 

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
    string tacsolver(string exp);
    void sep();
    int args();
    int args_();
    void statements();
    void shararat();
    void blks();
    void fblke();
    void blke();
    void vartype();
    void declare();
    void declare_(string id);
    void declare__(string id);
    string separatetac(string exp);
    string val();
    void input();
    void input_();
    void output();
    void output_();
    void output__();
    string out_();
    void loop();
    string exp();
    string exp_();
    string R();
    string P();
    string expval();
    string rel();
    void _if();
    void _elseif();
    void _else();
    void ret();
    void ret_();

    // helper functions
    void ptabs(string n);
    void newline();
    void update_tac(string data); // updates tac file
    void find_replace(string text, string nl);
    void find_replace_machine_code(string text, string nl);
    string newtmp();
    string remove_spaces(string s);
    int op_translator(string op);
    void vm_conditionals(string exp, string cond);
    int count_lines();
};
#endif
