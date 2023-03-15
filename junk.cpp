// #include "parser.h"

// void parser::syntax_error()
// {
//     cout << "SYNTAX ERROR\n";
//     exit(1);
// }
// token parser::expect(TokenType expected_type)
// {
//     token t = _lexer.getNextToken();
//     if (t.tokenType != expected_type)
//         syntax_error();
//     return t;
// }
// parser::parser(const char filename[])
// {
//     _lexer = lexer(filename);
// }
// void parser::readAndPrintAllInput() // read and print allinputs (provided)
// {
//     token t;
//     t = _lexer.getNextToken();
//     while (t.tokenType != TokenType::END_OF_FILE)
//     {
//         t.Print();
//         t = _lexer.getNextToken();
//     }
// }
// void parser::resetPointer()
// {
//     _lexer.resetPointer();
// }
// // this function is for sample purposes only
// /*
// bool parser::statements()
// {
//     //statements-- > COLON LPAREN start RPAREN
//     if (_lexer.peek(1).tokenType == TokenType::COLON)
//     {
//         expect(TokenType::COLON);
//         if (_lexer.peek(1).tokenType == TokenType::LPAREN)
//         {
//             expect(TokenType::LPAREN);
//             start();
//             if (_lexer.peek(1).tokenType == TokenType::RPAREN)
//             {
//                 expect(TokenType::RPAREN);
//                 return true;
//             }
//         }
//     }
//     return false;
// }*/

// void parser::start()
// {
//     if (_lexer.peek(1).tokenType == TokenType::COMMENT)
//     {
//         expect(TokenType::COMMENT);
//         start();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
//     {
//         if (_lexer.peek(2).tokenType == TokenType::KEYWD_MARKAZI)
//         {
//             _main();
//         }
//         else if (_lexer.peek(2).tokenType == TokenType::IDENTIFIER)
//         {
//             func();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::_main()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
//     {
//         expect(TokenType::KEYWD_KAAM);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_MARKAZI)
//         {
//             expect(TokenType::KEYWD_MARKAZI);
//             functype();
//             if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//             {
//                 expect(TokenType::OPEN_PARENTHESIS);
//                 if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                 {
//                     expect(TokenType::CLOSE_PARENTHESIS);
//                 }
//             }
//             blks();
//             statements();
//             fblke();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::func()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
//     {
//         expect(TokenType::KEYWD_KAAM);
//         if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//         {
//             expect(TokenType::IDENTIFIER);
//             functype();
//             if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//             {
//                 expect(TokenType::OPEN_PARENTHESIS);
//                 params();
//                 if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                 {
//                     expect(TokenType::CLOSE_PARENTHESIS);
//                 }
//             }
//             blks();
//             statements();
//             fblke();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::blks()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_ST_BLK_KARO)
//     {
//         expect(TokenType::KEYWD_ST_BLK_KARO);
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::fblke()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_KAAM)
//     {
//         expect(TokenType::KEYWD_KAAM);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_KHATAM)
//         {
//             expect(TokenType::KEYWD_KHATAM);
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::blke()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_END_BLK_BAS_KARO)
//     {
//         expect(TokenType::KEYWD_END_BLK_BAS_KARO);
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::functype()
// {
//     if (_lexer.peek(1).tokenType == TokenType::AT)
//     {
//         expect(TokenType::AT);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
//         {
//             expect(TokenType::KEYWD_ADAD);
//         }
//         else if (_lexer.peek(1).tokenType == TokenType::KEYWD_KHALI)
//         {
//             expect(TokenType::KEYWD_KHALI);
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::params()
// {
//     if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//     {
//         expect(TokenType::IDENTIFIER);
//         vartype();
//         sep();
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::sep()
// {
//     if (_lexer.peek(1).tokenType == TokenType::PIPE)
//     {
//         expect(TokenType::PIPE);
//         params();
//     }
//     else
//     {
//     }
// }

// void parser::statements()
// {
//     if (_lexer.peek(1).tokenType == TokenType::COMMENT)
//     {
//         expect(TokenType::COMMENT);
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_RAKHO)
//     {
//         declare();
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
//     {
//         input();
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_DEKHAO)
//     {
//         output();
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_JAB)
//     {
//         loop();
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
//     {
//         _if();
//         statements();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::KEYWD_WAPAS)
//     {
//         ret();
//         statements();
//     }
//     else
//     {
//     }
// }

// void parser::vartype()
// {
//     if (_lexer.peek(1).tokenType == TokenType::AT)
//     {
//         expect(TokenType::AT);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_ADAD)
//         {
//             expect(TokenType::KEYWD_ADAD);
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::declare()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_RAKHO)
//     {
//         expect(TokenType::KEYWD_RAKHO);
//         if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//         {
//             expect(TokenType::IDENTIFIER);
//             vartype();
//             declare_();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::declare_()
// {
//     if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//     {
//         expect(TokenType::SEMICOLON);
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
//     {
//         expect(TokenType::ASSIGN);
//         if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
//         {
//             expect(TokenType::NUMERIC_LITERAL);
//             if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//             {
//                 expect(TokenType::SEMICOLON);
//             }
//         }
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
//     {
//         expect(TokenType::ASSIGN);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
//         {
//             expect(TokenType::KEYWD_CHALAO);
//             if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//             {
//                 expect(TokenType::IDENTIFIER);
//                 if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//                 {
//                     expect(TokenType::OPEN_PARENTHESIS);
//                     params();
//                     if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                     {
//                         expect(TokenType::CLOSE_PARENTHESIS);
//                         if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//                         {
//                             expect(TokenType::SEMICOLON);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::ASSIGN)
//     {
//         expect(TokenType::ASSIGN);
//         exp();
//         if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//         {
//             expect(TokenType::SEMICOLON);
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

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

// void parser::input()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_LO)
//     {
//         expect(TokenType::KEYWD_LO);
//         input_();
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::input_()
// {
//     if (_lexer.peek(1).tokenType == TokenType::INPUT)
//     {
//         expect(TokenType::INPUT);
//         if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//         {
//             expect(TokenType::IDENTIFIER);
//             if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//             {
//                 expect(TokenType::SEMICOLON);
//             }
//         }
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
//     {
//         expect(TokenType::OUTPUT);
//         if (_lexer.peek(1).tokenType == TokenType::STRING)
//         {
//             expect(TokenType::STRING);
//             if (_lexer.peek(1).tokenType == TokenType::INPUT)
//             {
//                 expect(TokenType::INPUT);
//                 if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//                 {
//                     expect(TokenType::IDENTIFIER);
//                     if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//                     {
//                         expect(TokenType::SEMICOLON);
//                     }
//                 }
//             }
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::output()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_DEKHAO)
//     {
//         expect(TokenType::KEYWD_DEKHAO);
//         if (_lexer.peek(1).tokenType == TokenType::OUTPUT)
//         {
//             expect(TokenType::OUTPUT);
//             out_();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::out_()
// {
//     if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
//     {
//         expect(TokenType::IDENTIFIER);
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::STRING)
//     {
//         expect(TokenType::STRING);
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::loop()
// {
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_JAB)
//     {
//         expect(TokenType::KEYWD_JAB);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_TAK)
//         {
//             expect(TokenType::KEYWD_TAK);
//             if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//             {
//                 expect(TokenType::OPEN_PARENTHESIS);
//                 exp();
//                 if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                 {
//                     expect(TokenType::CLOSE_PARENTHESIS);
//                     blks();
//                     statements();
//                     blke();
//                 }
//             }
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::exp()
// {
// }

// void parser::exp_()
// {
// }

// void parser::expval()
// {
// }

// void parser::rel()
// {
//     // <= exp | < exp | >= exp | > exp | <> exp | = exp | null

//     if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN_EQUAL_TO)
//     {
//         expect(TokenType::GREATER_THAN_EQUAL_TO);
//         exp();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::GREATER_THAN)
//     {
//         expect(TokenType::GREATER_THAN);
//         exp();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN_EQUAL_TO)
//     {
//         expect(TokenType::LESS_THAN_EQUAL_TO);
//         exp();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::LESS_THAN)
//     {
//         expect(TokenType::LESS_THAN);
//         exp();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::NOT_EQUALS)
//     {
//         expect(TokenType::NOT_EQUALS);
//         exp();
//     }
//     else if (_lexer.peek(1).tokenType == TokenType::EQUALS)
//     {
//         expect(TokenType::EQUALS);
//         exp();
//     }
//     else
//     {
//     }
// }

// void parser::_if()
// {
//     // agar (exp) to phir blks statements elseif else blke

//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
//     {
//         expect(TokenType::KEYWD_AGAR);
//         if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//         {
//             expect(TokenType::OPEN_PARENTHESIS);
//             exp();
//             if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//             {
//                 expect(TokenType::CLOSE_PARENTHESIS);
//                 if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
//                 {
//                     expect(TokenType::KEYWD_TO);
//                     if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
//                     {
//                         expect(TokenType::KEYWD_PHIR);
//                         blks();
//                         statements();
//                         _elseif();
//                         _else();
//                         blke();
//                     }
//                 }
//             }
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::_elseif()
// {
//     // warna agar (exp) to phir statements else | null
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_WARNA)
//     {
//         expect(TokenType::KEYWD_WARNA);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_AGAR)
//         {
//             expect(TokenType::KEYWD_AGAR);
//             if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
//             {
//                 expect(TokenType::OPEN_PARENTHESIS);
//                 exp();
//                 if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
//                 {
//                     expect(TokenType::CLOSE_PARENTHESIS);
//                     if (_lexer.peek(1).tokenType == TokenType::KEYWD_TO)
//                     {
//                         expect(TokenType::KEYWD_TO);
//                         if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
//                         {
//                             expect(TokenType::KEYWD_PHIR);
//                             statements();
//                             _else();
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     else
//     {
//     }
// }

// void parser::_else()
// {
//     // warna phir statements | null
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_WARNA)
//     {
//         expect(TokenType::KEYWD_WARNA);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_PHIR)
//         {
//             expect(TokenType::KEYWD_PHIR);
//             statements();
//         }
//     }
//     else
//     {
//     }
// }

// void parser::ret()
// {
//     // wapis bhejo returnstatement_;
//     if (_lexer.peek(1).tokenType == TokenType::KEYWD_WAPAS)
//     {
//         expect(TokenType::KEYWD_WAPAS);
//         if (_lexer.peek(1).tokenType == TokenType::KEYWD_BHAIJO)
//         {
//             expect(TokenType::KEYWD_BHAIJO);
//             ret_();
//         }
//     }
//     else
//     {
//         syntax_error();
//     }
// }

// void parser::ret_()
// {
//     // num; | null
//     if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
//     {
//         expect(TokenType::NUMERIC_LITERAL);
//         if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
//         {
//             expect(TokenType::SEMICOLON);
//         }
//     }
//     else
//     {
//     }
// }