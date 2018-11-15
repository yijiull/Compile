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
            listing << "reserved words: " << tokenString << std::endl;
            break;
        case TK_ASSIGN:
            listing << ":=\n";
            break;
        case TK_LT:
            listing << "<\n";
            break;
        case TK_LE:
            listing << "<=\n";
            break;
        case TK_GT:
            listing << ">\n";
            break;
        case TK_GE:
            listing << ">=\n";
            break;
        case TK_EQ:
            listing << "=\n";
            break;
        case TK_LPAREN:
            listing << "(\n";
            break;
        case TK_RPAREN:
            listing << ")\n";
            break;
        case TK_SEMI:
            listing << ";\n";
            break;
        case TK_PLUS:
            listing << "+\n";
            break;
        case TK_MINUS:
            listing << "-\n";
            break;
        case TK_TIMES:
            listing << "*\n";
            break;
        case TK_OVER:
            listing << "/\n";
            break;
        case TK_COMMA:
            listing << ",\n";
            break;
        case TK_ENDFILE:
            listing << "EOF\n";
            break;
        case TK_STR:  
            listing << "TK_STR, val = " << tokenString << std::endl;
            break;
        case TK_NUM:
            listing << "TK_NUM, val = " << tokenString << std::endl;
            break;
        case TK_ID:
            listing << "TK_ID, name = " << tokenString << std::endl;
            break;
        case TK_ERROR:
            listing << "TK_ERROR, name = " << tokenString << std::endl;
            break;
        default:
            listing << "unknown token !! \n";
            break;
    }
}
