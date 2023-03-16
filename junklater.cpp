        // ptabs(":=");
        // tabs--;
        // expect(TokenType::ASSIGN);
        // if (_lexer.peek(1).tokenType == TokenType::NUMERIC_LITERAL)
        // {
        //     ptabs("num");
        //     tabs--;
        //     expect(TokenType::NUMERIC_LITERAL);
        //     if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        //     {
        //         ptabs(";");
        //         tabs--;
        //         expect(TokenType::SEMICOLON);
        //     }
        // }
        // else if (_lexer.peek(1).tokenType == TokenType::KEYWD_CHALAO)
        // {
        //     ptabs("chalao");
        //     tabs--;
        //     expect(TokenType::KEYWD_CHALAO);
        //     if (_lexer.peek(1).tokenType == TokenType::IDENTIFIER)
        //     {
        //         ptabs("id");
        //         tabs--;
        //         expect(TokenType::IDENTIFIER);
        //         if (_lexer.peek(1).tokenType == TokenType::OPEN_PARENTHESIS)
        //         {
        //             ptabs("(");
        //             tabs--;
        //             expect(TokenType::OPEN_PARENTHESIS);
        //             args();
        //             if (_lexer.peek(1).tokenType == TokenType::CLOSE_PARENTHESIS)
        //             {
        //                 ptabs(")");
        //                 tabs--;
        //                 expect(TokenType::CLOSE_PARENTHESIS);
        //                 if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        //                 {
        //                     ptabs(";");
        //                     tabs--;
        //                     expect(TokenType::SEMICOLON);
        //                 }
        //             }
        //         }
        //     }
        // }
        // else
        // {
        //     exp();
        //     if (_lexer.peek(1).tokenType == TokenType::SEMICOLON)
        //     {
        //         ptabs(";");
        //         tabs--;
        //         expect(TokenType::SEMICOLON);
        //     }
        // }