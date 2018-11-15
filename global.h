#include <fstream>
#include <string>
#include <iostream>
enum TokenType{
    TK_ENDFILE, TK_ERROR,
    TK_IF, TK_THEN, TK_ELSE, TK_END, TK_REPEAT, TK_UNTIL, TK_READ, TK_WRITE,
    TK_TRUE, TK_FALSE, TK_OR, TK_AND, TK_NOT, TK_INT, TK_BOOL, TK_STRING, TK_WHILE, TK_DO, //new
    TK_ID, TK_NUM, TK_CHARS,
    TK_ASSIGN, TK_EQ, TK_LT, TK_PLUS, TK_MINUS, TK_TIMES, TK_OVER, TK_LPAREN, TK_RPAREN, TK_SEMI,
    TK_GT, TK_LE, TK_GE, TK_COMMA, TK_QUOTE //new
};
const int MAXRESERVED = 18;

extern bool Error;
extern int lineno;
extern std::fstream source;
extern std::fstream listing;
extern std::fstream code;


enum NodeKind{
    StmtK, ExpK
};
enum StmtKind{
    IfK, RepeatK, AssignK, ReadK, WriteK,
    WhileK
};
enum ExpKind{
    OpK, ConstK, IdK,
    StringK, TrueK, FalseK
};

enum ExpType{
    Void, Integer, Boolean,
    Chars, True, False
};

const int MAXCHILDREN = 3;

struct TreeNode{
    TreeNode();
    TreeNode *child[MAXCHILDREN];
    TreeNode *silbing;
    int lineno;
    NodeKind nodekind;
    union{
        StmtKind stmt;
        ExpKind exp;
    }kind;
    union{
        TokenType op;
        int val;
        std::string name;
    }attr;
    ExpType type;
};