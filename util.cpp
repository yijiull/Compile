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
        case TK_SUB:
            tokenfile << "-\n";
            break;
        case TK_MUL:
            tokenfile << "*\n";
            break;
        case TK_DIV:
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


TreeNode* newNode(NodeType nodetype, int lineno){
    TreeNode *t = new TreeNode();
    for(int i = 0; i < MAXCHILDREN; i++){
        t->child[i] = nullptr;
    }
    //t->silbing = nullptr;
    t->nodetype = nodetype;
    t->tk = nullptr;
    t->lineno = lineno;
    return t;
}

namespace{
    int indent;
    void printSpace(){
        for(int i = 0; i < indent; i++){
            treefile<<" ";
        }
    }
    void pt(std::string s){
        treefile<<s<<std::endl;
    }
}
#define INDENT indent+=4
#define UNINDENT indent-=4

void printTree(TreeNode *t){
    INDENT;
    if(t != nullptr){
        printSpace();
        switch(t->nodetype){
            case STMT_SEQUENCE:
                pt("stmt_sequence");
                break;
            case PROGRAM:
                pt("program");
                break;
            case IF_STMT:
                pt("if");
                break;
            case REPEAT_STMT:
                pt("repeat");
                break;
            case ASSIGN_STMT:
                pt("assign");
                break;
            case READ_STMT:
                pt("read");
                break;
            case WRITE_STMT:
                pt("write");
                break;
            case WHILE_STMT:
                pt("while");
                break;
            case GE_EXP:
                pt(">=");
                break;
            case GT_EXP:
                pt(">");
                break;
            case LT_EXP:
                pt("<");
                break;
            case LE_EXP:
                pt("<=");
                break;
            case EQ_EXP:
                pt("=");
                break;
            case SUB_EXP:
                pt("sub");
                break;
            case PLUS_EXP:
                pt("plus");
                break;
            case MUL_EXP:
                pt("mul");
                break;
            case DIV_EXP:
                pt("div");
                break;
            case OR_EXP:
                pt("or");
                break;
            case AND_EXP:
                pt("and");
                break;
            case NOT_EXP:
                pt("not");
                break;
            case FACTOR:
                pt(std::string("factor:val=") + t->tk->tokenString);
                break;
            //case LPAREN_EXP:
            //    pt("(");
            //    break;
            //case RPAREN_EXP:
            //    pt(")");
            //    break;
            default:
                pt("---unknown NodeType  " + t->tk->tokenString);
                break;
        }
        for(int i = 0; i < MAXCHILDREN; i++){
            printTree(t->child[i]);
        }
    }
    UNINDENT;
}