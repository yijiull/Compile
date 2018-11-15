#include <fstream>
#include <vector>
#include <string>
#include <iostream>
enum TokenType{
    TK_ENDFILE, TK_ERROR,
    TK_IF, TK_THEN, TK_ELSE, TK_END, TK_REPEAT, TK_UNTIL, TK_READ, TK_WRITE,
    TK_TRUE, TK_FALSE, TK_OR, TK_AND, TK_NOT, TK_INT, TK_BOOL, TK_STRING, TK_WHILE, TK_DO, //new
    TK_ID, TK_NUM, TK_STR,
    TK_ASSIGN, TK_EQ, TK_LT, TK_PLUS, TK_MINUS, TK_TIMES, TK_OVER, TK_LPAREN, TK_RPAREN, TK_SEMI,
    TK_GT, TK_LE, TK_GE, TK_COMMA, TK_QUOTE //new
};
const int MAXRESERVED = 18;

extern bool Error;
extern int lineno;
extern std::fstream source;
extern std::fstream listing;
extern std::fstream code;

struct Token{
    Token(){};
    TokenType tokenType;
    std::string tokenString;
};