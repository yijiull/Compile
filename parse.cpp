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
    TreeNode* comparison_exp();
    TreeNode* add_exp();
    TreeNode* mul_exp();
    TreeNode* lessthan_exp();
    TreeNode* greaterthan_exp();
    TreeNode* lessequal_exp();
    TreeNode* greaterequal_exp();
    TreeNode* equal_exp();
    TreeNode* factor();

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
        std::cout<<"log:  "<< std::endl;
        //打印符号表
        printSymTable(symtablefile);
    }


    /*tiny用链表写的，节约了内存，不过不太好理解,下面先用树实现，后面看情况再用链表
    TreeNode* stmt_sequence(){
        TreeNode *t = statement();
        TreeNode *p = t;
        while(token != TK_ENDFILE && token != TK_END && token != TK_ELSE && token != TK_UNTIL){
            TreeNode *q;
            match(TK_SEMI);
            q = statement();
            if(q != nullptr){
                if(t == nullptr){
                    t = p = q;
                }else{
                    p->silbing = q;
                    p = q;
                }
            }
        }
        return t;
    }
    */

    TreeNode* stmt_sequence(){
        TreeNode *t = newNode(STMT_SEQUENCE);
        if(t != nullptr){
            t->child[0] = statement();
        }
        if(token == TK_SEMI){
            match(TK_SEMI);
            if(t != nullptr){
                t->child[1] = stmt_sequence();
            }
       }else{
           t = t->child[0];
       }
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
            case TK_ID:
                t = assign_stmt();
                break;
            case EOF:
                break;

            default:
                std::cout<<"Error at line " << lineno << ", unknown tokens:) "<< tokenString << std::endl;;
                printToken(token, tokenString);
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

    TreeNode* assign_stmt(){
        TreeNode *t = newNode(ASSIGN_STMT);
        if(t != nullptr && token == TK_ID){
            t->child[0] = factor();
            //t->child[0]->tk->tokenType = TK_ID;
            //t->child[0]->tk->tokenString = tokenString;
        }
        match(TK_ASSIGN);
        if(t != nullptr){
            t->child[1] = or_exp();
        }
        return t;
    }

    TreeNode* read_stmt(){
        TreeNode *t = newNode(READ_STMT);
        match(TK_READ);
        if(t != nullptr && token == TK_ID){
            t->child[0] = factor();
        }
        return t;
    }
    TreeNode* write_stmt(){
        TreeNode *t = newNode(WRITE_STMT);
        match(TK_WRITE);
        if(t != nullptr){
            t->child[0] = or_exp();
        }
        return t;
    }
    TreeNode* while_stmt(){
        TreeNode *t = newNode(WHILE_STMT);
        match(TK_WHILE);
        if(t != nullptr){
            t->child[0] = or_exp();
        }
        match(TK_DO);
        if(t != nullptr){
            t->child[1] = stmt_sequence();
        }
        match(TK_END);
        return t;
    }

    TreeNode* or_exp(){
        TreeNode *t = newNode(OR_EXP);
        if(t != nullptr){
            t->child[0] = and_exp();
        }
        if(token == TK_OR){
            match(TK_OR);
            if(t != nullptr){
                t->child[1] = or_exp();
            }
        }else{
            t = t->child[0];
        }
        return t;
    }

    TreeNode* and_exp(){
        TreeNode *t = newNode(AND_EXP);
        if(t != nullptr){
            t->child[0] = comparison_exp();
        }
        if(token == TK_AND){
            match(TK_AND);
            if(t != nullptr){
                t->child[1] = and_exp();
            }
        }else{
            t = t->child[0];
        }
        return t;
    }

    TreeNode* comparison_exp(){
        TreeNode *t = newNode(Void);
        if(t != nullptr){
            t->child[0] = add_exp();
        }
        switch(token){
            case TK_LT:
                match(TK_LT);
                t->nodetype = LT_EXP;
                t->child[1] = comparison_exp();
                break;
            case TK_LE:
                match(TK_LE);
                t->nodetype = LE_EXP;
                t->child[1] = comparison_exp();
                break;
            case TK_GT:
                match(TK_GT);
                t->nodetype = GT_EXP;
                t->child[1] = comparison_exp();
                break;
            case TK_GE:
                match(TK_GE);
                t->nodetype = GE_EXP;
                t->child[1] = comparison_exp();
                break;
            case TK_EQ:
                match(TK_EQ);
                t->nodetype = EQ_EXP;
                t->child[1] = comparison_exp();
                break;
            default:
                t = t->child[0];
                break;
        }
        return t;
    }

    TreeNode* add_exp(){
        TreeNode *t = newNode(Void);
        if(t != nullptr){
            t->child[0] = mul_exp();
        }
        switch(token){
            case TK_PLUS:
                match(TK_PLUS);
                t->nodetype = PLUS_EXP;
                t->child[1] = add_exp();
                break;
            case TK_SUB:
                match(TK_SUB);
                t->nodetype = SUB_EXP;
                t->child[1] = add_exp();
                break;
            default:
                t = t->child[0];
                break;
        }
        return t;
    }

    TreeNode* mul_exp(){
        TreeNode *t = newNode(Void);
        if(t != nullptr){
            t->child[0] = factor();
        }
        switch(token){
            case TK_MUL:
                match(TK_MUL);
                t->nodetype = MUL_EXP;
                t->child[1] = mul_exp();
                break;
            case TK_DIV:
                match(TK_DIV);
                t->nodetype = DIV_EXP;
                t->child[1] = mul_exp();
                break;
            default:
                t = t->child[0];
                break;
        }
        return t;
    }

    TreeNode* factor(){
        TreeNode *t = newNode(FACTOR);
        switch(token){
            case TK_ID:
                t->tk = new Token();
                t->tk->tokenType = TK_ID;
                t->tk->tokenString = tokenString;
                match(TK_ID);
                break;
            case TK_NUM:
                t->tk = new Token();
                t->tk->tokenType = TK_NUM;
                t->tk->tokenString = tokenString;
                match(TK_NUM);
                break;

            case TK_STR:
                t->tk = new Token();
                t->tk->tokenType = TK_STR;
                t->tk->tokenString = tokenString;
                match(TK_STR);
                break;
            case TK_TRUE:
                t->tk = new Token();
                t->tk->tokenType = TK_TRUE;
                t->tk->tokenString = tokenString;
                match(TK_TRUE);
                break;
            case TK_FALSE:
                t->tk = new Token();
                t->tk->tokenType = TK_FALSE;
                t->tk->tokenString = tokenString;
                match(TK_FALSE);
                break;
            case TK_LPAREN:
                t->nodetype = LPAREN_EXP;
                t->child[0] = newNode(FACTOR);
                t->child[0]->tk = new Token();
                t->child[0]->tk->tokenString = tokenString;
                t->child[0]->tk->tokenType = TK_LPAREN;
                match(TK_LPAREN);
                
                t->child[1] = or_exp();

                t->child[2] = newNode(FACTOR);
                t->child[2]->tk = new Token();
                t->child[2]->tk->tokenString = tokenString;
                t->child[2]->tk->tokenType = TK_RPAREN;
                match(TK_RPAREN);
                break;
        }
        return t;
    }


};

TreeNode* parse(){
    TreeNode *t = program();
    return t;
}