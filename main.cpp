#include <iostream>
#include "parser.h"
#include "symboltable.cpp"
//#include "vm.cpp"
using namespace std;

int main(int argc, char *argv[])
{
	// asking for file name as command line arguments
	if (argc == 2)
	{
		// lexer _lexer(argv[1]);
		// token t;
		// t = _lexer.getNextToken();
		// int i = 1;
		// while (t.tokenType != TokenType::END_OF_FILE)
		// {
		// 	cout << i;
		// 	i++;
		// 	t.Print();
		// 	t = _lexer.getNextToken();
		// }
		// cout << "\n\n";
		
		cout << "---Parse Tree---\n\n";
		parser p(argv[1]);
		p.smt.print_table();
		
		// for (size_t i = 0; i < p.param_count; i++)
		// {
		// 	cout << p.formal_param[i] << " ";
		// }
		
		// vm v;
		// v.vmst = &p.smt;
		// v.machine_code("TAC.txt");
		//v.vmst->print_table();
		//v.vmst.print_table();
		//v.machine_code("TAC.txt");
		// string a = "z";
		// p.smt.find_addr(a);
		
		//cout << p.nl;
		//p.find_replace("goto");
		//p.separatetac("z = a + b");
	}
	else if (argc > 2)
	{ // argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else // if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
