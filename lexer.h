#ifndef _LEXER_H_
#define _LEXER_H_
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// all your tokens goes here
enum class TokenType
{
	END_OF_FILE = 0,
	EQUALS,
	NOT_EQUALS,
	LESS_THAN,
	GREATER_THAN,
	LESS_THAN_EQUAL_TO,
	GREATER_THAN_EQUAL_TO,
	PIPE,
	COLON,
	SEMICOLON,
	AT,
	BACKTICK,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	MODULUS,
	IDENTIFIER,
	NUMERIC_LITERAL,
	ASSIGN,
	COMMENT,
	INPUT,
	OUTPUT,
	KEYWD_MARKAZI,
	KEYWD_KAAM,
	KEYWD_ST_BLK_KARO,
	KEYWD_END_BLK_BAS_KARO,
	KEYWD_RAKHO,
	KEYWD_JAB,
	KEYWD_TAK,
	KEYWD_BAS,
	KEYWD_AGAR,
	KEYWD_TO,
	KEYWD_WARNA,
	KEYWD_PHIR,
	KEYWD_DEKHAO,
	KEYWD_LO,
	KEYWD_CHALAO,
	KEYWD_WAPAS,
	KEYWD_BHAIJO,
	KEYWD_ADAD,
	KEYWD_KHALI,
	KEYWD_KHATAM,
	STRING,
	CHARACTER,
	NEWLINE,
	ERROR

};
// structure of a token
struct token
{
	string lexeme;
	TokenType tokenType; // enum type
	// constructor
	token(string lexeme, TokenType tokenType);
	// constructor default
	token();
	void Print();
};
class lexer
{
	vector<char> stream;  // used for storing file sample_code.ol content
	vector<token> tokens; // vector to store all (tokens,lexeme) pairs
	void Tokenize();	  // populates tokens vector
	int index;

public:
	lexer();
	lexer(const char filename[]);
	void printRaw();				 // just print everything as it is present in file
	token getNextToken();			 // get next token
	void resetPointer();			 // reset pointer to start getting tokens from start
	int getCurrentPointer();		 // get where current pointer in tokens vector is
	void setCurrentPointer(int pos); // move current pointer to wherever
	token peek(int);				 // peek the next token
};

#endif // !_LEXER_H
