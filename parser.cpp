#include "parser.h"

void parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
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
        if (_lexer.peek(1).tokenType == TokenType::COMMENT)
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
            smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme);
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
            }
            blks();
            statements();
            fblke();
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
            smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme);
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
            }
            blks();
            statements();
            fblke();
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

void parser::args()
{
    ptabs("args");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        expect(TokenType::IDENTIFIER);
        args_();
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::args_()
{
    ptabs("args_");
    if (_lexer.peek(1).tokenType == TokenType::PIPE)
    {
        ptabs("|");
        tabs--;
        expect(TokenType::PIPE);
        args();
    }
    else
    {
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
        if (_lexer.peek(1).tokenType == TokenType::COMMENT)
        {
            ptabs("cmt");
            tabs--;
            expect(TokenType::COMMENT);
            statements();
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::COMMENT)
    {
        ptabs("cmt");
        tabs--;
        expect(TokenType::COMMENT);
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_RAKHO)
    {
        // ptabs("rakho");
        // tabs--;
        declare();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
    {
        // ptabs("lo");
        // tabs--;
        input();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_DEKHAO)
    {
        // ptabs("dekhao");
        // tabs--;
        output();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_JAB)
    {
        // ptabs("jab");
        // tabs--;
        loop();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
    {
        // ptabs("agar");
        // tabs--;
        _if();
        statements();
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_WAPAS)
    {
        // ptabs("wapis");
        // tabs--;
        ret();
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
            smt.insert_item(_lexer.peek(1).lexeme, _lexer.peek(3).lexeme);
            expect(TokenType::IDENTIFIER);
            declare_();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::declare_()
{
    ptabs("declare_");
    if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
    {
        ptabs(":=");
        tabs--;
        expect(TokenType::ASSIGN);
        val();
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
            }
        }
    }
    else
    {
        vartype();
        declare__();
    }
    tabs--;
}

void parser::declare__()
{
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
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
    {
        ptabs(":=");
        tabs--;
        expect(TokenType::ASSIGN);
        val();
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
            }
        }
    }
    else
    {
        syntax_error();
    }
}

void parser::val()
{
    ptabs("val");
    if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        expect(TokenType::NUMERIC_LITERAL);
    }
    else if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
    {
        ptabs("chalao");
        tabs--;
        expect(TokenType::KEYWD_CHALAO);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            ptabs("id");
            tabs--;
            expect(TokenType::IDENTIFIER);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                ptabs("(");
                tabs--;
                expect(TokenType::OPEN_PARENTHESIS);
                args();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                }
            }
        }
    }
    else
    {
        exp();
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
            expect(TokenType::IDENTIFIER);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                ptabs(";");
                tabs--;
                expect(TokenType::SEMICOLON);
            }
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
                    expect(TokenType::IDENTIFIER);
                    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
                    {
                        ptabs(";");
                        tabs--;
                        expect(TokenType::SEMICOLON);
                    }
                }
            }
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
            if (_lexer.peek(1).tokenType == TokenType::COMMENT)
            {
                ptabs("cmt");
                tabs--;
                expect(TokenType::COMMENT);
            }
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
        out_();
        output_();
    }
    else
    {
    }
    tabs--;
}

void parser::out_()
{
    ptabs("out_");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        expect(TokenType::IDENTIFIER);
    }
    else if (_lexer.peek(1).tokenType == TokenType::STRING)
    {
        ptabs("str");
        tabs--;
        expect(TokenType::STRING);
    }
    else if (_lexer.peek(1).tokenType == TokenType::CHARACTER)
    {
        ptabs("chr");
        tabs--;
        expect(TokenType::CHARACTER);
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
                exp();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    ptabs(")");
                    tabs--;
                    expect(TokenType::CLOSE_PARENTHESIS);
                    blks();
                    statements();
                    blke();
                }
            }
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::exp()
{
    ptabs("exp");
    exp_();
    rel();
    R();
    tabs--;
}

void parser::exp_()
{
    ptabs("exp_");
    expval();
    rel();
    P();
    tabs--;
}

void parser::R()
{
    ptabs("R");
    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        ptabs("+");
        tabs--;
        expect(TokenType::PLUS);
        exp_();
        rel();
        R();
    }
    else if (_lexer.peek(1).tokenType == TokenType::MINUS)
    {
        ptabs("-");
        tabs--;
        expect(TokenType::MINUS);
        exp_();
        rel();
        R();
    }
    else
    {
    }
    tabs--;
}

void parser::P()
{
    ptabs("P");
    if (_lexer.peek(1).tokenType == TokenType::MODULUS)
    {
        ptabs("%");
        tabs--;
        expect(TokenType::MODULUS);
        expval();
        rel();
        P();
    }
    else if (_lexer.peek(1).tokenType == TokenType::MULTIPLY)
    {
        ptabs("*");
        tabs--;
        expect(TokenType::MULTIPLY);
        expval();
        rel();
        P();
    }
    else if (_lexer.peek(1).tokenType == TokenType::DIVIDE)
    {
        ptabs("/");
        tabs--;
        expect(TokenType::DIVIDE);
        expval();
        rel();
        P();
    }
    else
    {
    }
    tabs--;
}

void parser::expval()
{
    ptabs("expval");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        ptabs("id");
        tabs--;
        expect(TokenType::IDENTIFIER);
    }
    else if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        expect(TokenType::NUMERIC_LITERAL);
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::rel()
{
    // <= exp | < exp | >= exp | > exp | <> exp | = exp | null

    ptabs("rel");
    if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_EQUAL_TO)
    {
        ptabs(">=");
        tabs--;
        expect(TokenType::GREATER_THAN_EQUAL_TO);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN)
    {
        ptabs(">");
        tabs--;
        expect(TokenType::GREATER_THAN);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_EQUAL_TO)
    {
        ptabs("<=");
        tabs--;
        expect(TokenType::LESS_THAN_EQUAL_TO);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN)
    {
        ptabs("<");
        tabs--;
        expect(TokenType::LESS_THAN);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUALS)
    {
        ptabs("<>");
        tabs--;
        expect(TokenType::NOT_EQUALS);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::EQUALS)
    {
        ptabs("=");
        tabs--;
        expect(TokenType::EQUALS);
        exp();
    }
    else
    {
    }
    tabs--;
}

void parser::_if()
{
    // agar (exp) to phir blks statements elseif else blke

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
            exp();
            if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS) /////
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
                        _elseif();
                        _else();
                        blke();
                    }
                }
            }
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
    // warna agar (exp) to phir statements else | null

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
                exp();
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
                            statements();
                            _else();
                        }
                    }
                }
            }
        }
    }
    else
    {
    }
    tabs--;
}

void parser::_else()
{
    // warna phir statements | null

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
            statements();
        }
    }
    else
    {
    }
    tabs--;
}

void parser::ret()
{
    // wapis bhejo returnstatement_;

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
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::ret_()
{
    // num; | null

    ptabs("ret_");
    if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
        ptabs("num");
        tabs--;
        expect(TokenType::NUMERIC_LITERAL);
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            ptabs(";");
            tabs--;
            expect(TokenType::SEMICOLON);
        }
    }
    else
    {
    }
    tabs--;
}