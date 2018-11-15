#include "global.h"
#include "util.h"

void printToken(TokenType token, std::string tokenString){
    switch(token){
        case TK_IF:
        case TK_THEN:
        case TK_ELSE:
        case TK_END:
        case TK_REPEAT:
        case TK_UNTIL:
        case TK_READ:
        case TK_WRITE:
        case TK_TRUE:
        case TK_FALSE:
        case TK_OR:
        case TK_AND:
        case TK_NOT:
        case TK_INT:
        case TK_BOOL:
        case TK_STRING:
        case TK_WHILE:
        case TK_DO:
            tokenfile << "reserved words: " << tokenString << std::endl;
            break;
        case TK_ASSIGN:
            tokenfile << ":=\n";
            break;
        case TK_LT:
            tokenfile << "<\n";
            break;
        case TK_LE:
            tokenfile << "<=\n";
            break;
        case TK_GT:
            tokenfile << ">\n";
            break;
        case TK_GE:
            tokenfile << ">=\n";
            break;
        case TK_EQ:
            tokenfile << "=\n";
            break;
        case TK_LPAREN:
            tokenfile << "(\n";
            break;
        case TK_RPAREN:
            tokenfile << ")\n";
            break;
        case TK_SEMI:
            tokenfile << ";\n";
            break;
        case TK_PLUS:
            tokenfile << "+\n";
            break;
        case TK_MINUS:
            tokenfile << "-\n";
            break;
        case TK_TIMES:
            tokenfile << "*\n";
            break;
        case TK_OVER:
            tokenfile << "/\n";
            break;
        case TK_COMMA:
            tokenfile << ",\n";
            break;
        case TK_ENDFILE:
            tokenfile << "EOF\n";
            break;
        case TK_STR:  
            tokenfile << "TK_STR, val = " << tokenString << std::endl;
            break;
        case TK_NUM:
            tokenfile << "TK_NUM, val = " << tokenString << std::endl;
            break;
        case TK_ID:
            tokenfile << "TK_ID, name = " << tokenString << std::endl;
            break;
        case TK_ERROR:
            tokenfile << "TK_ERROR, name = " << tokenString << std::endl;
            break;
        default:
            tokenfile << "unknown token !! \n";
            break;
    }
}


TreeNode* newNode(NodeType nodetype){
    TreeNode *t = new TreeNode();
    for(int i = 0; i < MAXCHILDREN; i++){
        t->child[i] = nullptr;
    }
    t->silbing = nullptr;
    t->nodetype = nodetype;
    return t;
}