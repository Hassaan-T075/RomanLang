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
    if (_lexer.peek(1).tokenType == TokenType::COMMENT)
    {
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
        expect(TokenType::KEYWD_KAAM);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_MARKAZI)
        {
            expect(TokenType::KEYWD_MARKAZI);
            functype();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                expect(TokenType::OPEN_PARENTHESIS);
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
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
        expect(TokenType::KEYWD_KAAM);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            expect(TokenType::IDENTIFIER);
            functype();
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                expect(TokenType::OPEN_PARENTHESIS);
                params();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
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
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_END_BLK_BAS_KARO)
    {
        expect(TokenType::KEYWD_END_BLK_BAS_KARO);
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
        expect(TokenType::AT);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
        {
            expect(TokenType::KEYWD_ADAD);
        }
        else if (_lexer.peek(1).tokenType == TokenType::KEYWD_KHALI)
        {
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
        expect(TokenType::PIPE);
        params();
    }
    else
    {
    }
    tabs--;
}

void parser::statements()
{
    ptabs("statements");
    if (_lexer.peek(1).tokenType == TokenType::COMMENT)
    {
        expect(TokenType::COMMENT);
        statements();
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
        expect(TokenType::AT);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
        {
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
        expect(TokenType::KEYWD_RAKHO);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            expect(TokenType::IDENTIFIER);
            vartype();
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
    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
    {
        expect(TokenType::SEMICOLON);
    }
    else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
    {
        expect(TokenType::ASSIGN);
        if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
        {
            expect(TokenType::NUMERIC_LITERAL);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                expect(TokenType::SEMICOLON);
            }
        }
        else if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
        {
            expect(TokenType::KEYWD_CHALAO);
            if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
            {
                expect(TokenType::IDENTIFIER);
                if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
                {
                    expect(TokenType::OPEN_PARENTHESIS);
                    params();
                    if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                    {
                        expect(TokenType::CLOSE_PARENTHESIS);
                        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
                        {
                            expect(TokenType::SEMICOLON);
                        }
                    }
                }
            }
        }
        else
        {
            exp();
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                expect(TokenType::SEMICOLON);
            }
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

// void parser::val()
// {
//     if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
//     {
//         expect(TokenType::NUMERIC_LITERAL);
//         if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//         {
//             expect(TokenType::SEMICOLON);
//         }
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
//     {
//         expect(TokenType::KEYWD_CHALAO);
//         if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//         {
//             expect(TokenType::IDENTIFIER);
//             if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//             {
//                 expect(TokenType::OPEN_PARENTHESIS);
//                 params();
//                 if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                 {
//                     expect(TokenType::CLOSE_PARENTHESIS);
//                     if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//                     {
//                         expect(TokenType::SEMICOLON);
//                     }
//                 }
//             }
//         }
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
//     {
//         // do something
//     }
//     else
//     {
//         syntax_error();
//     }
// }

void parser::input()
{
    ptabs("input");
    if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
    {
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
        expect(TokenType::INPUT);
        if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        {
            expect(TokenType::IDENTIFIER);
            if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
            {
                expect(TokenType::SEMICOLON);
            }
        }
    }
    else if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
    {
        expect(TokenType::OUTPUT);
        if (_lexer.peek(1).tokenType == TokenType::STRING)
        {
            expect(TokenType::STRING);
            if (_lexer.peek(1).tokenType == TokenType::INPUT)
            {
                expect(TokenType::INPUT);
                if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
                {
                    expect(TokenType::IDENTIFIER);
                    if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
                    {
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
        expect(TokenType::KEYWD_DEKHAO);
        if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
        {
            expect(TokenType::OUTPUT);
            out_();
        }
    }
    else
    {
        syntax_error();
    }
    tabs--;
}

void parser::out_()
{
    ptabs("out_");
    if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
    {
        expect(TokenType::IDENTIFIER);
    }
    else if (_lexer.peek(1).tokenType == TokenType::STRING)
    {
        expect(TokenType::STRING);
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
        expect(TokenType::KEYWD_JAB);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_TAK)
        {
            expect(TokenType::KEYWD_TAK);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                expect(TokenType::OPEN_PARENTHESIS);
                exp();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
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
    R();
    tabs--;
}

void parser::exp_()
{
    ptabs("exp_");
    expval();
    P();
    tabs--;
}

void parser::R()
{
    ptabs("R");
    if (_lexer.peek(1).tokenType == TokenType::PLUS)
    {
        expect(TokenType::PLUS);
        exp_();
        rel();
        R();
    }
    else if (_lexer.peek(1).tokenType == TokenType::MINUS)
    {
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
        expect(TokenType::MODULUS);
        expval();
        rel();
        P();
    }
    else if (_lexer.peek(1).tokenType == TokenType::MULTIPLY)
    {
        expect(TokenType::MULTIPLY);
        expval();
        rel();
        P();
    }
    else if (_lexer.peek(1).tokenType == TokenType::DIVIDE)
    {
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
        expect(TokenType::IDENTIFIER);
    }
    else if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
    {
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
        expect(TokenType::GREATER_THAN_EQUAL_TO);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN)
    {
        expect(TokenType::GREATER_THAN);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_EQUAL_TO)
    {
        expect(TokenType::LESS_THAN_EQUAL_TO);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN)
    {
        expect(TokenType::LESS_THAN);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUALS)
    {
        expect(TokenType::NOT_EQUALS);
        exp();
    }
    else if (_lexer.peek(1).tokenType == TokenType::EQUALS)
    {
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
        expect(TokenType::KEYWD_AGAR);
        if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
        {
            expect(TokenType::OPEN_PARENTHESIS);
            exp();
            if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
            {
                expect(TokenType::CLOSE_PARENTHESIS);
                if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
                {
                    expect(TokenType::KEYWD_TO);
                    if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
                    {
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
        expect(TokenType::KEYWD_WARNA);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
        {
            expect(TokenType::KEYWD_AGAR);
            if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
            {
                expect(TokenType::OPEN_PARENTHESIS);
                exp();
                if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
                {
                    expect(TokenType::CLOSE_PARENTHESIS);
                    if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
                    {
                        expect(TokenType::KEYWD_TO);
                        if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
                        {
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
        expect(TokenType::KEYWD_WARNA);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
        {
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
        expect(TokenType::KEYWD_WAPAS);
        if (_lexer.peek(1).tokenType == TokenType::KEYWD_BHAIJO)
        {
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
        expect(TokenType::NUMERIC_LITERAL);
        if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        {
            expect(TokenType::SEMICOLON);
        }
    }
    else
    {
    }
    tabs--;
}