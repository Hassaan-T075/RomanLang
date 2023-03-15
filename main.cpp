#include <iostream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	//asking for file name as command line arguments
	if (argc == 2)
	{
		// lexer _lexer(argv[1]);
		// token t;
		// t = _lexer.getNextToken();
		// int i = 1;
		// while (t.tokenType != TokenType::END_OF_FILE)
		// {
		// 	cout<< i;
		// 	i++;
		// 	t.Print();
		// 	t = _lexer.getNextToken();
		// }

		parser p(argv[1]);
	}
	else if (argc > 2)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
