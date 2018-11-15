#include <fstream>
#include <vector>
#include <string>
#include <iostream>
enum TokenType{
    TK_ENDFILE, TK_ERROR,
    TK_IF, TK_THEN, TK_ELSE, TK_END, TK_REPEAT, TK_UNTIL, TK_READ, TK_WRITE,
    TK_TRUE, TK_FALSE, TK_OR, TK_AND, TK_NOT, TK_INT, TK_BOOL, TK_STRING, TK_WHILE, TK_DO, //new
    TK_ID, TK_NUM, TK_STR,
    TK_ASSIGN, TK_EQ, TK_LT, TK_PLUS, TK_SUB, TK_MUL, TK_DIV, TK_LPAREN, TK_RPAREN, TK_SEMI,
    TK_GT, TK_LE, TK_GE, TK_COMMA, TK_QUOTE //new
};

enum NodeType{
    PROGRAM, STMT_SEQUENCE, IF_STMT, REPEAT_STMT, ASSIGN_STMT,
    READ_STMT, WRITE_STMT, WHILE_STMT,
    GT_EXP, GE_EXP, LT_EXP, LE_EXP, EQ_EXP, OR_EXP, AND_EXP, NOT_EXP,
    PLUS_EXP, SUB_EXP, MUL_EXP, DIV_EXP,
    FACTOR,
    Void,
    LPAREN_EXP, RPAREN_EXP

};

enum ValType{
    VT_INT, VT_BOOL, VT_STRING
};

const int MAXRESERVED = 18;
const int MAXCHILDREN = 3;


extern bool Error;
extern int lineno;
extern std::fstream source;
extern std::fstream tokenfile;
extern std::fstream symtablefile;
extern std::fstream codefile;
extern std::fstream treefile;
extern std::fstream checkfile;

extern int location;

struct Token{
    Token(){};
    TokenType tokenType;
    std::string tokenString;
    int lineno;
};

struct TreeNode{
    NodeType nodetype;
    //TreeNode *silbing;
    TreeNode *child[MAXCHILDREN];

    Token *tk;
};