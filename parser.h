#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
//for future assignments leave it as it is
class parser
{
    lexer _lexer;
    token l;
    int tabs = 0;
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
	//all your parser function goes here
    void start();
    void _main();
    void func();
    void functype();
    void params();
    void sep();
    void statements();
    void blks();
    void fblke();
    void blke();
    void vartype();
    void declare();
    void declare_();
    //void val();
    void input();
    void input_();
    void output();
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
