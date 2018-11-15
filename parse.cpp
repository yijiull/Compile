#include "global.h"
#include "util.h"
#include "scan.h"
#include "parse.h"
#include "symtab.h"

namespace{
    TokenType token;

    int location = 0;

    TreeNode* parse();
    void declarations();
    TreeNode* program(); 
    TreeNode* stmt_sequence();
    TreeNode* statement();
    TreeNode* if_stmt();
    TreeNode* repeat_stmt();
    TreeNode* assign_stmt();
    TreeNode* read_stmt();
    TreeNode* write_stmt();
    TreeNode* while_stmt();

    TreeNode* or_exp();
    TreeNode* and_exp();

    void syntaxError(std::string m){
        tokenfile << "\n>>> ";
        tokenfile << "Syntax error at line " << lineno << ": " << m;
        Error = true;
    }

    void match(TokenType expected){
        if(token == expected){
            token = getToken();
        }else{
            syntaxError("unexpexted token ->");
            printToken(token, tokenString);
            tokenfile << "       ";
        }
    }

    TreeNode* program(){
        declarations();
        return stmt_sequence();
    }

    void declarations(){
        token = getToken();
        while(token == TK_INT || token == TK_BOOL || token == TK_STRING){
            do{
                token = getToken();
                std::string name = tokenString;
                match(TK_ID);
                //插入符号表
                std::cout<<name<<std::endl;
                if(st_lookup(name) == -1){
                    st_insert(name, lineno, location++);
                }else{
                    symtablefile << "Error at line " << lineno <<";\n";
                    symtablefile << name << "declared multies times:)\n";
                    st_insert(name, lineno, 0);
                }
            }while(token == TK_COMMA);
            match(TK_SEMI);
        }
        //打印符号表
        printSymTable(symtablefile);
    }


    TreeNode* stmt_sequence(){
        TreeNode *t = statement();
        return t;
    }

    TreeNode* statement(){
        TreeNode *t = nullptr;
        switch(token){
            case TK_IF:
                t = if_stmt();
                break;
            case TK_READ:
                t = read_stmt();
                break;
            case TK_REPEAT:
                t = repeat_stmt();
                break;
            case TK_WRITE:
                t = write_stmt();
                break;
            case TK_WHILE:
                t = while_stmt();
                break;
            case TK_ASSIGN:
                t = assign_stmt();
                break;
            default:
                std::cout<<"Error at line " << lineno << ", unknown tokens:)\n";
        }
        return t;
    }

    TreeNode* if_stmt(){
        TreeNode *t = newNode(IF_STMT);
        match(TK_IF);
        if(t != nullptr){
            t->child[0] = or_exp();
        }
        match(TK_THEN);
        if(t != nullptr){
            t->child[1] = stmt_sequence();
        }
        if(token == TK_ELSE){
            match(TK_ELSE);
            if(t != nullptr){
                t->child[2] = stmt_sequence();
            }
        }
        match(TK_END);
        return t;
    }

    TreeNode* repeat_stmt(){
        TreeNode *t = newNode(REPEAT_STMT);
        match(TK_REPEAT);
        if(t != nullptr){
            t->child[0] = stmt_sequence();
        }
        match(TK_UNTIL);
        if(t !=  nullptr){
            t->child[1] = or_exp();
        }
        return t;
    }


};

TreeNode* parse(){
    TreeNode *t = program();
    return t;
}