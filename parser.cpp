#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR at line: " << no_of_lines << "\n";
    exit(1);
}
token parser::expect(TokenType expected_type)
{
    token t = _lexer.getNextToken();
    if (t.tokenType != expected_type)
        syntax_error();
    return t;
}
parser::parser(const char filename[])
{
    _lexer = lexer(filename);
    start();
}
void parser::readAndPrintAllInput() // read and print allinputs (provided)
{
    token t;
    t = _lexer.getNextToken();
    while (t.tokenType != TokenType::END_OF_FILE)
    {
        t.Print();
        t = _lexer.getNextToken();
    }
}
void parser::resetPointer()
{
    _lexer.resetPointer();
}
// this function is for sample purposes only
/*
bool parser::statements()
{
    //statements-- > COLON LPAREN start RPAREN
    if (_lexer.peek(1).tokenType == TokenType::COLON)
    {
        expect(TokenType::COLON);
        if (_lexer.peek(1).tokenType == TokenType::LPAREN)
        {
            expect(TokenType::LPAREN);
            start();
            if (_lexer.peek(1).tokenType == TokenType::RPAREN)
            {
                expect(TokenType::RPAREN);
                return true;
            }
        }
    }
    return false;
}*/

void parser::ptabs(string n)
{
    tabs++;
    for (size_t i = 0; i < tabs; i++)
    {
        cout << " ";
    }

    cout << n << "\n";
}

void parser::start()
{
    ptabs("start");
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        ptabs(";");
        tabs--;
        expect(TokenType::SEMICOLON);
        if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
        {
            newline();
        }
        else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
        {
            ptabs("cmt");
            tabs--;
            expect(TokenType::COMMENT);
            start();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
    {
        ptabs("cmt");
        tabs--;
        expect(TokenType::COMMENT);
        start();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
    {

        if (_lexer.peek(2).tokenType == TokenType::KEYWD_MARKAZI)
        {
            _main();
        }
        else if (_lexer.peek(2).tokenType == TokenType::IDENTIFIER)
        {
            func();
            start();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
    {
        newline();
        start();
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::_main()
{
    ptabs("main");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
    {
        ptabs("kaam");
        tabs--;
        expect(TokenType::KEYWD_KAAM);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_MARKAZI)
        {
            ptabs("markazi");
            tabs--;
            smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme, nl, "NULL", 1);
            expect(TokenType::KEYWD_MARKAZI);
            functype();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
            blks();
            statements();
            fblke();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::func()
{
    ptabs("func");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
    {
        ptabs("kaam");
        tabs--;
        expect(TokenType::KEYWD_KAAM);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            ptabs("id");
            tabs--;
            smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme, nl, "NULL", 1);
            expect(TokenType::IDENTIFIER);
            functype();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                params();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
            blks();
            statements();
            fblke();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::blks()
{
    ptabs("blks");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_ST_BLK_KARO)
    {
        ptabs("karo");
        tabs--;
        expect(TokenType::KEYWD_ST_BLK_KARO);
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
                newline();
            }
            else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
        }
        else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
        {
            newline();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::fblke()
{
    ptabs("fblke");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
    {
        ptabs("kaam khatam");
        tabs--;
        expect(TokenType::KEYWD_KAAM);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_KHATAM)
        {
            expect(TokenType::KEYWD_KHATAM);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                ptabs(";");
                tabs--;
                expect(TokenType::SEMICOLON);
                if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                {
                    ptabs("cmt");
                    tabs--;
                    expect(TokenType::COMMENT);
                    newline();
                }
                else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                {
                    newline();
                }
            }
            else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::blke()
{
    ptabs("blke");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_BAS)
    {
        ptabs("bas karo");
        tabs--;
        expect(TokenType::KEYWD_BAS);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_ST_BLK_KARO)
        {
            expect(TokenType::KEYWD_ST_BLK_KARO);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                ptabs(";");
                tabs--;
                expect(TokenType::SEMICOLON);
                if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                {
                    ptabs("cmt");
                    tabs--;
                    expect(TokenType::COMMENT);
                    newline();
                }
                else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                {
                    newline();
                }
            }
            else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::functype()
{
    ptabs("functype");
    if (_lexer.peek(1).tokenType == TokenType::AT)
    {
        ptabs("@");
        tabs--;
        expect(TokenType::AT);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
        {
            ptabs("adad");
            tabs--;
            expect(TokenType::KEYWD_ADAD);
        }
        else if (_lexer.peek(1).tokenType == TokenType::KEYWD_KHALI)
        {
            ptabs("khali");
            tabs--;
            expect(TokenType::KEYWD_KHALI);
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::params()
{
    ptabs("params");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme, -1, "NULL", 0);
        tabs--;
        expect(TokenType::IDENTIFIER);
        vartype();
        sep();
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::sep()
{
    ptabs("sep");
    if (_lexer.peek(1).tokenType == TokenType::PIPE)
    {
        ptabs("|");
        tabs--;
        expect(TokenType::PIPE);
        params();
    }
    else
    {
    }
    tabs--;
}

int parser::args()
{
    ptabs("args");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        entry = "param " + _lexer.peek(1).lexeme + "\n";
        update_tac(entry);
        nl++;
        expect(TokenType::IDENTIFIER);
        int s = args_() + 1;
        return s;
    }
    else if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        entry = "param " + _lexer.peek(1).lexeme + "\n";
        update_tac(entry);
        nl++;
        expect(TokenType::NUMERIC_LITERAL);
        int s = args_() + 1;
        return s;
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

int parser::args_()
{
    ptabs("args_");
    if (_lexer.peek(1).tokenType == TokenType::PIPE)
    {
        ptabs("|");
        tabs--;
        expect(TokenType::PIPE);
        int s = args();
        return s;
    }
    else
    {
        int s = 0;
        return s;
    }
    tabs--;
}

void parser::statements()
{
    ptabs("statements");
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        ptabs(";");
        tabs--;
        expect(TokenType::SEMICOLON);
        if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
        {
            newline();
        }
        else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
        {
            ptabs("cmt");
            tabs--;
            expect(TokenType::COMMENT);
            statements();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_RAKHO)
    {
        declare();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
    {
        input();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_DEKHAO)
    {
        output();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_JAB)
    {
        loop();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
    {
        _if();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_WAPAS)
    {
        ret();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
    {
        newline();
        statements();
    }
    else
    {
    }
    tabs--;
}

void parser::vartype()
{
    ptabs("vartype");
    if (_lexer.peek(1).tokenType == TokenType::AT)
    {
        ptabs("@");
        tabs--;
        expect(TokenType::AT);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
        {
            ptabs("adad");
            tabs--;
            expect(TokenType::KEYWD_ADAD);
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::declare()
{
    ptabs("declare");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_RAKHO)
    {
        ptabs("rakho");
        tabs--;
        expect(TokenType::KEYWD_RAKHO);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            ptabs("id");
            tabs--;
            string id = _lexer.peek(1).lexeme;
            if (_lexer.peek(5).tokenType == TokenType::NUMERIC_LITERAL)
            {
                smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme, -1, _lexer.peek(5).lexeme, 0);
            }
            else
            {
                smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme, -1, "NULL", 0);
            }
            expect(TokenType::IDENTIFIER);
            declare_(id);
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::declare_(string id)
{
    ptabs("declare_");
    if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
    {
        ptabs(":=");
        tabs--;
        expect(TokenType::ASSIGN);
        string v = val();
        string entry = id + " = " + v + "\n";
        string str_tac = separatetac(entry);
        update_tac(str_tac);
        nl++;

        // machine code
        // string id_a = smt.find_addr(id);
        // v = remove_spaces(v);
        // string val_a = smt.find_addr(v);
        // if (val_a != "0")
        //     parser::v.mce("500 " + val_a + " " + id_a);

        // find_replace(entry, sep_str);
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
            else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
                if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                {
                    newline();
                }
            }
        }
        else
        {
            syntax_error();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::AT)
    {
        vartype();
        declare__(id);
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::declare__(string id)
{
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        ptabs(";");
        tabs--;
        expect(TokenType::SEMICOLON);
        if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
        {
            newline();
        }
        else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
        {
            ptabs("cmt");
            tabs--;
            expect(TokenType::COMMENT);
            if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
    {
        ptabs(":=");
        tabs--;
        expect(TokenType::ASSIGN);
        string v = val();
        entry = id + " = " + v + "\n";

        // // if val() v is not in symbol table then create a temporary varible
        // string s = smt.find_addr(v);
        // if (s == "0") // address not found
        //     smt.insert_item("t" + to_string(++tmp_count), "temp", -1, v, false);

        string str_tac = separatetac(entry);
        update_tac(str_tac);
        nl++;
        // find_replace(entry, sep_str);
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
            else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
                newline();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
}

string parser::val()
{
    ptabs("val");
    if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        string v = _lexer.peek(1).lexeme;
        expect(TokenType::NUMERIC_LITERAL);
        return " " + v;
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
    {
        ptabs("chalao");
        tabs--;
        expect(TokenType::KEYWD_CHALAO);
        string var = newtmp();
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            // string var = newtmp();
            ptabs("id");
            tabs--;
            string id = _lexer.peek(1).lexeme;
            expect(TokenType::IDENTIFIER);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                int s = args();
                // string var = newtmp();
                update_tac("call " + id + " " + to_string(s) + ", " + var + "\n");
                nl++;
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
        return var;
    }
    else
    {
        string exp_str = exp();
        string str = " " + exp_str;
        return str;
    }
    tabs--;
}

void parser::input()
{
    ptabs("input");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
    {
        ptabs("lo");
        tabs--;
        expect(TokenType::KEYWD_LO);
        input_();
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::input_()
{
    ptabs("input_");
    if (_lexer.peek(1).tokenType == TokenType::INPUT)
    {
        ptabs(">>");
        tabs--;
        expect(TokenType::INPUT);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            ptabs("id");
            tabs--;
            entry = "in " + _lexer.peek(1).lexeme + "\n";
            update_tac(entry);
            nl++;

            // machine code
            string a = smt.find_addr(_lexer.peek(1).lexeme);
            v.mce("100 " + a);

            expect(TokenType::IDENTIFIER);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                ptabs(";");
                tabs--;
                expect(TokenType::SEMICOLON);
                if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                {
                    newline();
                }
                else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                {
                    ptabs("cmt");
                    tabs--;
                    expect(TokenType::COMMENT);
                    newline();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        ptabs("<<");
        tabs--;
        expect(TokenType::OUTPUT);
        if (_lexer.peek(1).tokenType == TokenType::STRING)
        {
            ptabs("str");
            tabs--;
            entry = "out " + _lexer.peek(1).lexeme + "\n";
            update_tac(entry);
            nl++;

            // machine code
            string a = smt.find_addr(_lexer.peek(1).lexeme);

            if (a == "0") // address not found
            {
                string t = "t" + to_string(++tmp_count);
                smt.insert_item(t, "temp", -1, _lexer.peek(1).lexeme, false);
                a = smt.find_addr(t);
            }

            v.mce("200 " + a);

            expect(TokenType::STRING);
            if (_lexer.peek(1).tokenType == TokenType::INPUT)
            {
                ptabs(">>");
                tabs--;
                expect(TokenType::INPUT);
                if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
                {
                    ptabs("id");
                    tabs--;
                    entry = "in " + _lexer.peek(1).lexeme + "\n";
                    update_tac(entry);
                    nl++;

                    // machine code
                    string a = smt.find_addr(_lexer.peek(1).lexeme);

                    if (a == "0") // address not found
                    {
                        string t = "t" + to_string(++tmp_count);
                        smt.insert_item(t, "temp", -1, _lexer.peek(1).lexeme, false);
                        a = smt.find_addr(t);
                    }

                    v.mce("100 " + a);

                    expect(TokenType::IDENTIFIER);
                    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
                    {
                        ptabs(";");
                        tabs--;
                        expect(TokenType::SEMICOLON);
                        if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                        {
                            newline();
                        }
                        else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                        {
                            ptabs("cmt");
                            tabs--;
                            expect(TokenType::COMMENT);
                            newline();
                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::output()
{
    ptabs("output");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_DEKHAO)
    {
        ptabs("dekhao");
        tabs--;
        expect(TokenType::KEYWD_DEKHAO);
        output_();
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
            else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
                newline();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::output_()
{
    ptabs("output_");
    if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        ptabs("<<");
        tabs--;
        expect(TokenType::OUTPUT);
        string n = out_();
        entry = "out " + n + "\n";
        update_tac(entry);
        nl++;

        string a = smt.find_addr(n);

        // if n is not in symbol table then create a temporary varible
        // string s = smt.find_addr(v);
        if (a == "0") // address not found
        {
            string t = "t" + to_string(++tmp_count);
            smt.insert_item(t, "temp", -1, n, false);
            a = smt.find_addr(t);
        }
        v.mce("200 " + a);

        output__();
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

string parser::separatetac(string exp)
{
    // origin contains start of expression which is lhs of expression
    string main_str = "", origin = "", origin_2 = "";
    int i = 0;

    while (1)
    {
        if (exp[i] != 32)
        {
            origin += exp[i];
            if (exp[i] != 61)
                origin_2 += exp[i];
        }
        if (exp[i] == 61)
            break;

        i++;
    }
    i++;

    string str = "";
    string op = "";

    // separate operands and operators in str and op respectively
    for (; exp[i] != '\0'; i++)
    {
        if ((exp[i] >= 37 && exp[i] <= 47) || (exp[i] >= 60 && exp[i] <= 62))
        {
            op.push_back(exp[i]);
        }
        else
        {
            if (exp[i] != 32)
                str.push_back(exp[i]);
        }
    }

    // v.mce("\n");
    //  generate tac code for expression
    while (1)
    {
        string operand1 = "", operand2 = "";
        operand1 += str.front();

        // if operand is a temporary variable
        if (str.front() == 't')
        {
            str.erase(0, 1);
            operand1 += str.front();
        }

        // remove in case of errors
        //  if operand is a numeric value
        //  while (str.front() >= 48 && str.front() <= 56)
        //  {
        //      str.erase(0, 1);
        //      operand1 += str.front();
        //  }

        str.erase(0, 1);

        if (str.length() != 0)
        {
            operand2 += str.front();
            str.erase(0, 1);
        }

        string _operator = "";
        _operator += op.front();

        if (op.length() != 0)
        {
            // print tac in file
            string var = newtmp();
            update_tac(var + " = " + operand1 + _operator + operand2 + "\n");
            nl++;

            // machine code
            string opcode = to_string(op_translator(_operator));
            string adr0 = smt.find_addr(var);

            string adr1 = smt.find_addr(operand1);
            if (adr1 == "0") // address not found
            {
                string t = "t" + to_string(++tmp_count);
                smt.insert_item(t, "temp", -1, operand1, false);
                adr1 = smt.find_addr(t);
            }

            string adr2 = smt.find_addr(operand2);
            if (adr2 == "0") // address not found
            {
                string t = "t" + to_string(++tmp_count);
                smt.insert_item(t, "temp", -1, operand2, false);
                adr2 = smt.find_addr(t);
            }

            v.mce(opcode + " " + adr1 + " " + adr2 + " " + adr0);

            str = var[1] + str;
            str = var[0] + str;
        }
        else
        {
            // machine code
            string adr0 = smt.find_addr(origin_2);
            string adr1 = smt.find_addr(operand1);

            // if adr1 is not in symbol table then create a temporary varible
            // string s = smt.find_addr(adr1);
            if (adr1 == "0") // address not found
            {
                string t = "t" + to_string(++tmp_count);
                smt.insert_item(t, "temp", -1, operand1, false);
                adr1 = smt.find_addr(t);
            }

            v.mce("500 " + adr1 + " " + adr0);

            // return final statement
            return origin + " " + operand1 + "\n";
        }
        op.erase(0, 1);
    }

    return main_str;
}

void ::parser::output__()
{
    ptabs("output__");
    if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        output_();
    }
    else
    {
    }
    tabs--;
}

string parser::out_()
{
    ptabs("out_");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        string n = _lexer.peek(1).lexeme;
        expect(TokenType::IDENTIFIER);
        return n;
    }
    else if (_lexer.peek(1).tokenType == TokenType::STRING)
    {
        ptabs("str");
        tabs--;
        string n = _lexer.peek(1).lexeme;
        expect(TokenType::STRING);
        return n;
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHARACTER)
    {
        ptabs("chr");
        tabs--;
        string n = _lexer.peek(1).lexeme;
        expect(TokenType::CHARACTER);
        return n;
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::loop()
{
    ptabs("loop");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_JAB)
    {
        ptabs("jab");
        tabs--;
        expect(TokenType::KEYWD_JAB);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_TAK)
        {
            ptabs("tak");
            tabs--;
            expect(TokenType::KEYWD_TAK);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                string exp_str = exp();
                int ret_loop = nl;
                entry = "if " + exp_str + " goto loopt\n";
                // entry = "if exp goto loopt\n";
                update_tac(entry);
                nl++;
                entry = "goto loopf\n";
                update_tac(entry);
                nl++;
                find_replace("loopt", to_string(nl));
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                    blks();
                    statements();
                    update_tac("goto " + to_string(ret_loop) + "\n");
                    nl++;
                    find_replace("loopf", to_string(nl));
                    blke();
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

string parser::exp()
{
    string str = "";
    ptabs("exp");
    string exp__str = exp_();
    str = str + " " + exp__str;
    string r_str = R();
    str = str + " " + r_str;
    // entry = "if exp goto _\n";
    // update_tac(entry);
    // nl++;
    // update_tac("goto _\n");
    // nl++;
    tabs--;
    return str;
}

string parser::exp_()
{
    ptabs("exp_");
    string str = "";
    string expval_str = expval();
    str = str + " " + expval_str;
    string rel_str = rel();
    str = str + " " + rel_str;
    string p_str = P();
    str = str + " " + p_str;
    tabs--;
    return str;
}

string parser::R()
{
    string str = "";
    ptabs("R");
    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        ptabs("+");
        tabs--;
        str = str + " " + "+";
        expect(TokenType::PLUS);
        string exp__str = exp_();
        str = str + " " + exp__str;
        string rel_str = rel();
        str = str + " " + rel_str;
        string r_str = R();
        str = str + " " + r_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::MINUS)
    {
        ptabs("-");
        tabs--;
        str = str + " " + "-";
        expect(TokenType::MINUS);
        string exp__str = exp_();
        str = str + " " + exp__str;
        string rel_str = rel();
        str = str + " " + rel_str;
        string r_str = R();
        str = str + " " + r_str;
    }
    else
    {
    }
    tabs--;
    return str;
}

string parser::P()
{
    ptabs("P");
    string str = "";
    if (_lexer.peek(1).tokenType == TokenType::MODULUS)
    {
        ptabs("%");
        tabs--;
        str = str + " " + "%";
        expect(TokenType::MODULUS);
        string expval_str = expval();
        str = str + " " + expval_str;
        string rel_str = rel();
        str = str + " " + rel_str;
        string p_str = P();
        str = str + " " + p_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::MULTIPLY)
    {
        ptabs("*");
        tabs--;
        str = str + " " + "*";
        expect(TokenType::MULTIPLY);
        string expval_str = expval();
        str = str + " " + expval_str;
        string rel_str = rel();
        str = str + " " + rel_str;
        string p_str = P();
        str = str + " " + p_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::DIVIDE)
    {
        ptabs("/");
        tabs--;
        str = str + " " + "/";
        expect(TokenType::DIVIDE);
        string expval_str = expval();
        str = str + " " + expval_str;
        string rel_str = rel();
        str = str + " " + rel_str;
        string p_str = P();
        str = str + " " + p_str;
    }
    else
    {
    }
    tabs--;
    return str;
}

string parser::expval()
{
    string str = "";
    ptabs("expval");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        str = str + " " + _lexer.peek(1).lexeme;
        expect(TokenType::IDENTIFIER);
    }
    else if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        str = str + " " + _lexer.peek(1).lexeme;
        expect(TokenType::NUMERIC_LITERAL);
    }
    else if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
    {
        ptabs("(");
        tabs--;
        str = str + " " + _lexer.peek(1).lexeme;
        expect(TokenType::OPEN_PARENTHESIS);

        string exp_str = exp();
        str = str + " " + exp_str;
        if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
        {
            ptabs(")");
            tabs--;
            str = str + " " + _lexer.peek(1).lexeme;
            expect(TokenType::CLOSE_PARENTHESIS);
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
    return str;
}

string parser::rel()
{
    ptabs("rel");
    string str = "";
    if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_EQUAL_TO)
    {
        ptabs(">=");
        tabs--;
        str = str + " " + ">=";
        expect(TokenType::GREATER_THAN_EQUAL_TO);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN)
    {
        ptabs(">");
        tabs--;
        str = str + " " + ">";
        expect(TokenType::GREATER_THAN);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_EQUAL_TO)
    {
        ptabs("<=");
        tabs--;
        str = str + " " + "<=";
        expect(TokenType::LESS_THAN_EQUAL_TO);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN)
    {
        ptabs("<");
        tabs--;
        str = str + " " + "<";
        expect(TokenType::LESS_THAN);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUALS)
    {
        ptabs("<>");
        tabs--;
        str = str + " " + "<>";
        expect(TokenType::NOT_EQUALS);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else if (_lexer.peek(1).tokenType == TokenType::EQUALS)
    {
        ptabs("=");
        tabs--;
        str = str + " " + "=";
        expect(TokenType::EQUALS);
        string exp_str = exp();
        str = str + " " + exp_str;
    }
    else
    {
    }
    tabs--;
    return str;
}

void parser::_if()
{
    ptabs("_if");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
    {
        ptabs("agar");
        tabs--;
        expect(TokenType::KEYWD_AGAR);
        if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
        {
            ptabs("(");
            tabs--;
            expect(TokenType::OPEN_PARENTHESIS);
            string exp_str = exp();
            entry = "if " + exp_str + "goto ift\n";
            update_tac(entry);

            // if condition
            string _expression = remove_spaces(exp_str);
            vm_conditionals(_expression, "ift"); // true condition

            // entry = "if exp goto t1\n";
            nl++;
            update_tac("goto iff\n");
            v.mce("800 iff");
            nl++;
            find_replace("ift", to_string(nl));
            if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
            {
                ptabs(")");
                tabs--;
                expect(TokenType::CLOSE_PARENTHESIS);
                if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
                {
                    ptabs("to");
                    tabs--;
                    expect(TokenType::KEYWD_TO);
                    if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
                    {
                        ptabs("phir");
                        tabs--;
                        expect(TokenType::KEYWD_PHIR);
                        blks();
                        statements();
                        update_tac("goto nn1\n");
                        nl++;
                        find_replace("iff", to_string(nl)); // false cond.
                        _elseif();
                        _else();
                        find_replace("nn1", to_string(nl));
                        blke();
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::_elseif()
{
    ptabs("_elseif");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_WARNA)
    {
        ptabs("warna");
        tabs--;
        expect(TokenType::KEYWD_WARNA);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
        {
            ptabs("agar");
            tabs--;
            expect(TokenType::KEYWD_AGAR);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                string exp_str = exp();
                entry = "if " + exp_str + "goto elseift\n";
                // entry = "if exp goto t2\n";
                update_tac(entry);
                nl++;
                update_tac("goto elseiff\n");
                nl++;
                find_replace("elseift", to_string(nl));
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                    if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
                    {
                        ptabs("to");
                        tabs--;
                        expect(TokenType::KEYWD_TO);
                        if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
                        {
                            ptabs("phir");
                            tabs--;
                            expect(TokenType::KEYWD_PHIR);
                            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
                            {
                                ptabs(";");
                                tabs--;
                                expect(TokenType::SEMICOLON);
                                if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                                {
                                    ptabs("cmt");
                                    tabs--;
                                    expect(TokenType::COMMENT);
                                    newline();
                                }
                                else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                                {
                                    newline();
                                }
                            }
                            else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                            {
                                newline();
                            }
                            statements();
                            update_tac("goto nn2\n");
                            nl++;
                            find_replace("elseiff", to_string(nl)); // false cond.
                            _else();
                            find_replace("nn2", to_string(nl));
                        }
                        else
                        {
                            syntax_error();
                        }
                    }
                    else
                    {
                        syntax_error();
                    }
                }
                else
                {
                    syntax_error();
                }
            }
            else
            {
                syntax_error();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
    }
    tabs--;
}

void parser::_else()
{
    ptabs("_else");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_WARNA)
    {
        ptabs("wrna");
        tabs--;
        expect(TokenType::KEYWD_WARNA);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
        {
            ptabs("phir");
            tabs--;
            expect(TokenType::KEYWD_PHIR);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                ptabs(";");
                tabs--;
                expect(TokenType::SEMICOLON);
                if (_lexer.peek(1).tokenType == TokenType::COMMENT)
                {
                    ptabs("cmt");
                    tabs--;
                    expect(TokenType::COMMENT);
                    newline();
                }
                else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
                {
                    newline();
                }
            }
            else if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
            statements();
            // find_replace("_", nl);
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
    }
    tabs--;
}

void parser::ret()
{
    ptabs("ret");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_WAPAS)
    {
        ptabs("wapis");
        tabs--;
        expect(TokenType::KEYWD_WAPAS);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_BHAIJO)
        {
            ptabs("bhaijo");
            tabs--;
            expect(TokenType::KEYWD_BHAIJO);
            ret_();
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::ret_()
{
    ptabs("ret_");
    if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        entry = "ret " + _lexer.peek(1).lexeme + "\n";

        // machine code
        string a = smt.find_addr(_lexer.peek(1).lexeme);

        if (a == "0") // address not found
        {
            string t = "t" + to_string(++tmp_count);
            smt.insert_item(t, "temp", -1, _lexer.peek(1).lexeme, false);
            a = smt.find_addr(t);
        }

        v.mce("900 " + a);

        expect(TokenType::NUMERIC_LITERAL);
        update_tac(entry);
        nl++;
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
            if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
            {
                newline();
            }
            else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
                newline();
            }
        }
        else
        {
            syntax_error();
        }
    }
    else
    {
        v.mce("900");
        update_tac("ret\n");
        nl++;
    }
    tabs--;
}

void parser::newline()
{
    if (_lexer.peek(1).tokenType == TokenType::NEWLINE)
    {

        expect(TokenType::NEWLINE);
        no_of_lines++;
    }
    else
    {
        syntax_error();
    }
}

void parser::update_tac(string data)
{
    ofstream fil;

    fil.open("TAC.txt", ios::app);

    if (!fil)
    {
        fil.close();
        fil.open("TAC.txt");
        fil << data;
        fil.close();
    }
    else
    {
        fil << data;
        fil.close();
    }
}

void parser::find_replace(string text, string nl)
{
    fstream fin;
    fin.open("TAC.txt", ios::in);

    string data, newdata;

    newdata = "";
    bool found = true;

    while (fin)
    {
        getline(fin, data);
        int a = (int)data.find(text, 0);
        if (a != string::npos && found)
        {
            data.replace(a, text.length(), nl);
            found = false;
        }
        newdata = newdata + data + "\n";
    }
    fin.close();

    newdata.pop_back();

    fin.open("TAC.txt", ios::out);

    fin << newdata;

    fin.close();
}

string parser::newtmp()
{
    tmp_count++;
    smt.insert_item("t" + to_string(tmp_count), "adad", -1, "NULL", 0);
    return "t" + to_string(tmp_count);
}

string parser::remove_spaces(string s)
{
    string a = "";
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != 32)
            a = a + s[i];
    }
    return a;
}

int parser::op_translator(string op)
{
    if (op == "+")
        return 10;
    else if (op == "-")
        return 20;
    else if (op == "*")
        return 30;
    else if (op == "/")
        return 40;
    else if (op == "%")
        return 50;
    else if (op == "<")
        return 1000;
    else if (op == "<=")
        return 1010;
    else if (op == ">")
        return 2000;
    else if (op == ">=")
        return 2010;
    else if (op == "=")
        return 3000;
    else if (op == "<>")
        return 4000;
}

void parser::vm_conditionals(string exp, string cond)
{
    int i = 0;
    string operand1, op, operand2;
    stringstream ss;

    operand1 += exp[i];
    i++;
    if (exp[i - 1] == 't') // if first expression is a temporary variable
    {
        operand1 = operand1 + exp[i];
        i++;
    }
    string adr1 = smt.find_addr(operand1);

    //check later
    // if (adr1 == "0") // address not found, make temporary variable
    // {
    //     string t = "t" + to_string(++tmp_count);
    //     smt.insert_item(t, "temp", -1, operand1, false);
    //     adr1 = smt.find_addr(t);
    // }

    op += exp[i];
    i++;
    if (exp[i] == '=' || exp[i] == '>') // if
    {
        op = op + exp[i];
        i++;
    }
    string _opcode = to_string(op_translator(op));

    operand2 += exp[i];

    i++;
    if (exp[i - 1] == 't') // if first expression is a temporary variable
    {
        operand2 = operand2 + exp[i];
        i++;
    }
    string adr2 = smt.find_addr(operand2);
    if (adr2 == "0") // address not found, make temporary variable
    {
        string t = "t" + to_string(++tmp_count);
        smt.insert_item(t, "temp", -1, operand2, false);
        adr2 = smt.find_addr(t);
    }

    v.mce(_opcode + " " + adr1 + " " + adr2 + " " + cond);
}