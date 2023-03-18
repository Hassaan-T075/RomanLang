#include "lexer.h"
using namespace std;
// for printing tokens names, Same as the enum defined in lexer.h
string reserved[] = {
    "END_OF_FILE",
    "EQUALS",
    "NOT_EQUALS",
    "LESS_THAN",
    "GREATER_THAN",
    "LESS_THAN_EQUAL_TO",
    "GREATER_THAN_EQUAL_TO",
    "PIPE",
    "COLON",
    "SEMICOLON",
    "AT",
    "BACKTICK",
    "OPEN_PARENTHESIS",
    "CLOSE_PARENTHESIS",
    "PLUS",
    "MINUS",
    "MULTIPLY",
    "DIVIDE",
    "MODULUS",
    "IDENTIFIER",
    "NUMERIC_LITERAL",
    "ASSIGN",
    "COMMENT",
    "INPUT",
    "OUTPUT",
    "KEYWD_MARKAZI",
    "KEYWD_KAAM",
    "KEYWD_ST_BLK_KARO",
    "KEYWD_END_BLK_BAS_KARO",
    "KEYWD_RAKHO",
    "KEYWD_JAB",
    "KEYWD_TAK",
    "KEYWD_BAS",
    "KEYWD_AGAR",
    "KEYWD_TO",
    "KEYWD_WARNA",
    "KEYWD_PHIR",
    "KEYWD_DEKHAO",
    "KEYWD_LO",
    "KEYWD_CHALAO",
    "KEYWD_WAPAS",
    "KEYWD_BHAIJO",
    "KEYWD_ADAD",
    "KEYWD_KHALI",
    "KEYWD_KHATAM",
    "STRING",
    "CHARACTER",
    "NEWLINE",
    "ERROR"};
token::token()
{
    this->lexeme = "";
    this->tokenType = TokenType::ERROR;
}
token::token(string lexeme, TokenType tokenType)
{
    this->lexeme = lexeme;
    this->tokenType = tokenType;
}
void token::Print()
{
    cout << "{" << lexeme << " , "
         << reserved[(int)tokenType] << "}\n";
}
int lexer::getCurrentPointer()
{
    return index;
}
void lexer::setCurrentPointer(int pos)
{
    if (pos >= 0 && pos < tokens.size())
        index = pos;
    else
        index = 0;
}
void lexer::Tokenize() // function that tokenizes your input stream
{
    vector<char>::iterator str_itr = stream.begin();
    // your implementation goes here

    int state = 1; // dfa state

    for (str_itr = stream.begin(); str_itr != stream.end(); str_itr++)
    {

        switch (state)
        {
        // Keywords

        // markazi
        case 1:
            if ((*str_itr == 'm') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'r') && (*(str_itr + 3) == 'k') && (*(str_itr + 4) == 'a') && (*(str_itr + 5) == 'z') && (*(str_itr + 6) == 'i'))
            {
                if (*(str_itr + 7) == ' ' || *(str_itr + 7) == '\n' || !isalnum(*(str_itr + 7)))
                {
                    tokens.push_back(token(string("markazi"), TokenType::KEYWD_MARKAZI));
                    if (*(str_itr + 7) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 6;

                    break;
                }
            }
        // kaam
        case 2:
            if ((*str_itr == 'k') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'm'))
            {
                if (*(str_itr + 4) == ' ' || *(str_itr + 4) == '\n' || !isalnum(*(str_itr + 4)))
                {
                    tokens.push_back(token(string("kaam"), TokenType::KEYWD_KAAM));
                    if (*(str_itr + 4) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 3;
                    break;
                }
            }
        // karo -> start block
        case 3:
            if ((*str_itr == 'k') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'r') && (*(str_itr + 3) == 'o'))
            {
                if (*(str_itr + 4) == ' ' || *(str_itr + 4) == '\n' || !isalnum(*(str_itr + 4)))
                {
                    tokens.push_back(token(string("karo"), TokenType::KEYWD_ST_BLK_KARO));
                    if (*(str_itr + 4) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 3;
                    break;
                }
            }
        // rakho
        case 4:
            if ((*str_itr == 'r') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'k') && (*(str_itr + 3) == 'h') && (*(str_itr + 4) == 'o'))
            {
                if (*(str_itr + 5) == ' ' || *(str_itr + 5) == '\n' || !isalnum(*(str_itr + 5)))
                {
                    tokens.push_back(token(string("rakho"), TokenType::KEYWD_RAKHO));
                    if (*(str_itr + 5) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 4;
                    break;
                }
            }
        // jab
        case 5:
            if ((*str_itr == 'j') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'b'))
            {
                if (*(str_itr + 3) == ' ' || *(str_itr + 3) == '\n' || !isalnum(*(str_itr + 3)))
                {
                    tokens.push_back(token(string("jab"), TokenType::KEYWD_JAB));
                    if (*(str_itr + 3) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 2;
                    break;
                }
            }
        // tak
        case 6:
            if ((*str_itr == 't') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'k'))
            {
                if (*(str_itr + 3) == ' ' || *(str_itr + 3) == '\n' || !isalnum(*(str_itr + 3)))
                {
                    tokens.push_back(token(string("tak"), TokenType::KEYWD_TAK));
                    if (*(str_itr + 3) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 2;
                    break;
                }
            }
        // bas
        case 7:
            if ((*str_itr == 'b') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 's'))
            {
                if (*(str_itr + 3) == ' ' || *(str_itr + 3) == '\n' || !isalnum(*(str_itr + 3)))
                {
                    tokens.push_back(token(string("bas"), TokenType::KEYWD_BAS));
                    if (*(str_itr + 3) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 2;
                    break;
                }
            }
        // agar
        case 8:
            if ((*str_itr == 'a') && (*(str_itr + 1) == 'g') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'r'))
            {
                if (*(str_itr + 4) == ' ' || *(str_itr + 4) == '\n' || !isalnum(*(str_itr + 4)))
                {
                    tokens.push_back(token(string("agar"), TokenType::KEYWD_AGAR));
                    if (*(str_itr + 4) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 3;
                    break;
                }
            }
        // to
        case 9:
            if ((*str_itr == 't') && (*(str_itr + 1) == 'o'))
            {
                if (*(str_itr + 2) == ' ' || *(str_itr + 2) == '\n' || !isalnum(*(str_itr + 2)))
                {
                    tokens.push_back(token(string("to"), TokenType::KEYWD_TO));
                    if (*(str_itr + 2) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 1;
                    break;
                }
            }
        // warna
        case 10:
            if ((*str_itr == 'w') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'r') && (*(str_itr + 3) == 'n') && (*(str_itr + 4) == 'a'))
            {
                if (*(str_itr + 5) == ' ' || *(str_itr + 5) == '\n' || !isalnum(*(str_itr + 5)))
                {
                    tokens.push_back(token(string("warna"), TokenType::KEYWD_WARNA));
                    if (*(str_itr + 5) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 4;
                    break;
                }
            }
        // phir
        case 11:
            if ((*str_itr == 'p') && (*(str_itr + 1) == 'h') && (*(str_itr + 2) == 'i') && (*(str_itr + 3) == 'r'))
            {
                if (*(str_itr + 4) == ' ' || *(str_itr + 4) == '\n' || !isalnum(*(str_itr + 4)))
                {
                    tokens.push_back(token(string("phir"), TokenType::KEYWD_PHIR));
                    if (*(str_itr + 4) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 3;
                    break;
                }
            }
        // dekhao
        case 12:
            if ((*str_itr == 'd') && (*(str_itr + 1) == 'e') && (*(str_itr + 2) == 'k') && (*(str_itr + 3) == 'h') && (*(str_itr + 4) == 'a') && (*(str_itr + 5) == 'o'))
            {
                if (*(str_itr + 6) == ' ' || *(str_itr + 6) == '\n' || !isalnum(*(str_itr + 6)))
                {
                    tokens.push_back(token(string("dekhao"), TokenType::KEYWD_DEKHAO));
                    if (*(str_itr + 6) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 5;
                    break;
                }
            }
        // lo
        case 13:
            if ((*str_itr == 'l') && (*(str_itr + 1) == 'o'))
            {
                if (*(str_itr + 2) == ' ' || *(str_itr + 2) == '\n' || !isalnum(*(str_itr + 2)))
                {
                    tokens.push_back(token(string("lo"), TokenType::KEYWD_LO));
                    if (*(str_itr + 2) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 1;
                    break;
                }
            }
        // chalao
        case 14:
            if ((*str_itr == 'c') && (*(str_itr + 1) == 'h') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'l') && (*(str_itr + 4) == 'a') && (*(str_itr + 5) == 'o'))
            {
                if (*(str_itr + 6) == ' ' || *(str_itr + 6) == '\n' || !isalnum(*(str_itr + 6)))
                {
                    tokens.push_back(token(string("chalao"), TokenType::KEYWD_CHALAO));
                    if (*(str_itr + 6) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 5;
                    break;
                }
            }
        // wapas
        case 15:
            if ((*str_itr == 'w') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 'p') && (*(str_itr + 3) == 'a') && (*(str_itr + 4) == 's'))
            {
                if (*(str_itr + 5) == ' ' || *(str_itr + 5) == '\n' || !isalnum(*(str_itr + 5)))
                {
                    tokens.push_back(token(string("wapas"), TokenType::KEYWD_WAPAS));
                    if (*(str_itr + 5) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 4;
                    break;
                }
            }
        // bhaijo
        case 16:
            if ((*str_itr == 'b') && (*(str_itr + 1) == 'h') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'i') && (*(str_itr + 4) == 'j') && (*(str_itr + 5) == 'o'))
            {
                if (*(str_itr + 6) == ' ' || *(str_itr + 6) == '\n' || !isalnum(*(str_itr + 6)))
                {
                    tokens.push_back(token(string("bhaijo"), TokenType::KEYWD_BHAIJO));
                    if (*(str_itr + 6) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 5;
                    break;
                }
            }
        // adad
        case 17:
            if ((*str_itr == 'a') && (*(str_itr + 1) == 'd') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'd'))
            {
                if (*(str_itr + 4) == ' ' || *(str_itr + 4) == '\n' || !isalnum(*(str_itr + 4)))
                {
                    tokens.push_back(token(string("adad"), TokenType::KEYWD_ADAD));
                    if (*(str_itr + 4) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 3;
                    break;
                }
            }
        // khali
        case 18:
            if ((*str_itr == 'k') && (*(str_itr + 1) == 'h') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 'l') && (*(str_itr + 4) == 'i'))
            {
                if (*(str_itr + 5) == ' ' || *(str_itr + 5) == '\n' || !isalnum(*(str_itr + 5)))
                {
                    tokens.push_back(token(string("khali"), TokenType::KEYWD_KHALI));
                    if (*(str_itr + 5) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 4;
                    break;
                }
            }
        // khatam
        case 19:
            if ((*str_itr == 'k') && (*(str_itr + 1) == 'h') && (*(str_itr + 2) == 'a') && (*(str_itr + 3) == 't') && (*(str_itr + 4) == 'a') && (*(str_itr + 5) == 'm'))
            {
                if (*(str_itr + 6) == ' ' || *(str_itr + 6) == '\n' || !isalnum(*(str_itr + 6)))
                {
                    tokens.push_back(token(string("khatam"), TokenType::KEYWD_KHATAM));
                    if (*(str_itr + 6) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 5;
                    break;
                }
            }
        // bas karo -> end block
        case 20:
            if ((*str_itr == 'b') && (*(str_itr + 1) == 'a') && (*(str_itr + 2) == 's') && (*(str_itr + 3) == ' ') && (*(str_itr + 4) == 'k') && (*(str_itr + 5) == 'a') && (*(str_itr + 6) == 'r') && (*(str_itr + 7) == 'o'))
            {
                if (*(str_itr + 8) == ' ' || *(str_itr + 8) == '\n' || !isalnum(*(str_itr + 8)))
                {
                    tokens.push_back(token(string("bas karo"), TokenType::KEYWD_END_BLK_BAS_KARO));
                    if (*(str_itr + 8) == '\n')
                    {
                        tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                        str_itr = str_itr + 1;
                    }
                    str_itr = str_itr + 7;
                    break;
                }
            }
            // Comment
        case 21:
            if (*str_itr == ';')
            {
                string temp = "";
                if (*(str_itr + 1) != '\n')
                {
                    // semicolon special comment case
                    tokens.push_back(token(string("semi colon"), TokenType::SEMICOLON));
                    str_itr++;

                    for (str_itr; *(str_itr) != '\n'; str_itr++)
                    {
                        temp = temp + *str_itr;
                    }
                    tokens.push_back(token(string(temp), TokenType::COMMENT));
                    tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                    break;
                }
            }
            // character
        case 22:
            if (*str_itr == '`' && *(str_itr + 2) == '`')
            {
                string temp = "";
                temp = temp + *str_itr;
                str_itr = str_itr + 1;
                temp = temp + *str_itr;
                str_itr = str_itr + 1;
                temp = temp + *str_itr;
                str_itr = str_itr + 1;
                tokens.push_back(token(string(temp), TokenType::CHARACTER));
                str_itr--;
                break;
            }
            // String

        case 23:
            if (*str_itr == '`')
            {
                string temp = "";
                temp = temp + "`";
                str_itr++;
                for (str_itr; *(str_itr) != '`'; str_itr++)
                {
                    temp = temp + *str_itr;
                }
                temp = temp + "`";
                tokens.push_back(token(string(temp), TokenType::STRING));
                break;
            }

            // Assignment
        case 24:
            if (*str_itr == ':' && *(str_itr + 1) == '=')
            {
                tokens.push_back(token(string("assign"), TokenType::ASSIGN));
                str_itr++;
                break;
            }
            // Input
        case 25:
            if (*str_itr == '>' && *(str_itr + 1) == '>')
            {
                tokens.push_back(token(string("input"), TokenType::INPUT));
                str_itr++;
                break;
            }
            // Output
        case 26:
            if (*str_itr == '<' && *(str_itr + 1) == '<')
            {
                tokens.push_back(token(string("output"), TokenType::OUTPUT));
                str_itr++;
                break;
            }
            // Relational Operator
        case 27:
            if (*str_itr == '>' && *(str_itr + 1) == '=')
            {
                tokens.push_back(token(string("greater than equal to"), TokenType::GREATER_THAN_EQUAL_TO));
                str_itr = str_itr + 1;
                break;
            }

        case 28:
            if (*str_itr == '<' && *(str_itr + 1) == '=')
            {
                tokens.push_back(token(string("less than equal to"), TokenType::LESS_THAN_EQUAL_TO));
                str_itr = str_itr + 1;
                break;
            }

        case 29:
            if (*str_itr == '<' && *(str_itr + 1) == '>')
            {
                tokens.push_back(token(string("not equal to"), TokenType::NOT_EQUALS));
                str_itr = str_itr + 1;
                break;
            }
        case 30:
            if (*str_itr == '=')
            {
                tokens.push_back(token(string("equals"), TokenType::EQUALS));
                break;
            }
        case 31:
            if (*str_itr == '>')
            {
                tokens.push_back(token(string("greater than"), TokenType::GREATER_THAN));
                break;
            }
        case 32:
            if (*str_itr == '<')
            {
                tokens.push_back(token(string("less than"), TokenType::LESS_THAN));
                break;
            }
            // Special Characters
        case 33:
            if (*str_itr == '|')
            {
                tokens.push_back(token(string("pipe"), TokenType::PIPE));
                break;
            }
        case 34:
            if (*str_itr == ':')
            {
                tokens.push_back(token(string("colon"), TokenType::COLON));
                break;
            }
        case 35:
            if (*str_itr == ';')
            {
                tokens.push_back(token(string("semi colon"), TokenType::SEMICOLON));
                break;
            }
        case 36:
            if (*str_itr == '@')
            {
                tokens.push_back(token(string("at"), TokenType::AT));
                break;
            }
        // individual backtick ?????
        //  case 37:
        //      if (*str_itr == '`')
        //      {
        //          tokens.push_back(token(string("backtick"), TokenType::BACKTICK));
        //          break;
        //      }
        case 38:
            if (*str_itr == '(')
            {
                tokens.push_back(token(string("open parenthesis"), TokenType::OPEN_PARENTHESIS));
                break;
            }
        case 39:
            if (*str_itr == ')')
            {
                tokens.push_back(token(string("close parenthesis"), TokenType::CLOSE_PARENTHESIS));
                break;
            }
            // Arithmetic Operators
        case 40:
            if (*str_itr == '+')
            {
                tokens.push_back(token(string("plus"), TokenType::PLUS));
                break;
            }
        case 41:
            if (*str_itr == '-')
            {
                tokens.push_back(token(string("minus"), TokenType::MINUS));
                break;
            }
        case 42:
            if (*str_itr == '*')
            {
                tokens.push_back(token(string("multiply"), TokenType::MULTIPLY));
                break;
            }
        case 43:
            if (*str_itr == '/')
            {
                tokens.push_back(token(string("divide"), TokenType::DIVIDE));
                break;
            }
        case 44:
            if (*str_itr == '%')
            {
                tokens.push_back(token(string("modulus"), TokenType::MODULUS));
                break;
            }
        case 45:
            if (*str_itr == ')')
            {
                tokens.push_back(token(string("close parenthesis"), TokenType::CLOSE_PARENTHESIS));
                break;
            }
            // Other Constructs
            // Idetifier
        case 46:
            if (isalpha(*str_itr) || (*str_itr == '_'))
            {

                string temp = "";
                for (str_itr; isalnum(*str_itr) || *str_itr == '_'; str_itr++)
                {
                    // if (isalpha(*str_itr))
                    //{
                    temp = temp + *str_itr;
                    //}
                }
                tokens.push_back(token(string(temp), TokenType::IDENTIFIER));
                str_itr--; //*str_itr--;
                break;
            }
            // Numeric literals
        case 47:

            if (isdigit((int)*str_itr))
            {

                string temp = "";
                for (str_itr; isdigit(*str_itr); str_itr++)
                {
                    if (isdigit((int)*str_itr))
                    {
                        temp = temp + *str_itr;
                    }
                }
                tokens.push_back(token(string(temp), TokenType::NUMERIC_LITERAL));
                str_itr--;
                break;
            }
        //keep track of lines
        case 48:
            if (*str_itr == '\n')
            {
                tokens.push_back(token(string("newline"), TokenType::NEWLINE));
                break;
            }
        }
    }

    // push_back EOF token at end to identify End of File
    tokens.push_back(token(string(""), TokenType::END_OF_FILE));
}
lexer::lexer(const char filename[])
{
    // constructors: takes file name as an argument and store all
    // the contents of file into the class varible stream
    ifstream fin(filename);
    if (!fin) // if file not found
    {
        cout << "file not found" << endl;
    }
    else
    {
        char byte = 0;
        while (fin.get(byte))
        { // store file contents into stream
            if (byte != '\r')
                stream.push_back(byte);
        }
        stream.push_back(' '); // dummy spaces appended at the end
        stream.push_back(' ');
        // Tokenize function to get all the (token,lexeme) pairs
        Tokenize();
        // int k = 0;
        // for (token i: this->tokens)
        //{
        // cout<< k;
        // k++;
        // i.Print();
        // cout<<endl;
        //}
        // assigning tokens to iterator::pointer
        index = 0;
    }
}
lexer::lexer()
{
    index = -1;
}
void lexer::printRaw()
{
    // helper function to print the content of file
    vector<char>::iterator it = stream.begin();
    for (it = stream.begin(); it != stream.end(); it++)
    {
        cout << *it;
    }
    cout << endl;
}
token lexer::getNextToken()
{
    // this function will return single (token,lexeme) pair on each call
    // this is an iterator which is pointing to the beginning of vector of tokens
    token _token;
    if (index == tokens.size())
    {                       // return end of file if
        _token.lexeme = ""; // index is too large
        _token.tokenType = TokenType::END_OF_FILE;
    }
    else
    {
        _token = tokens[index];
        index = index + 1;
    }
    return _token;
}
void lexer::resetPointer()
{
    index = 0;
}
token lexer::peek(int howFar)
{
    if (howFar <= 0)
    { // peeking backward or in place is not allowed
        cout << "LexicalAnalyzer:peek:Error: non positive argument\n";
        exit(-1);
    }

    int peekIndex = index + howFar - 1;
    if (peekIndex > (tokens.size() - 1))
    {                                             // if peeking too far
        return token("", TokenType::END_OF_FILE); // return END_OF_FILE
    }
    else
        return tokens[peekIndex];
}