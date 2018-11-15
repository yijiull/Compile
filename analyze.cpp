#include "global.h"
#include "symtab.h"
#include "analyze.h"
namespace{
    void traverse(TreeNode *t, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *)){
        if(t == nullptr){
            return;
        }
        preProc(t);
        for(int i = 0; i < MAXCHILDREN; i++){
            traverse(t->child[i], preProc, postProc);
        }
        postProc(t);
    }

    void insertNode(TreeNode *t){
        switch(t->nodetype){
            //case ASSIGN_STMT:
            //case READ_STMT:
            //    if(st_lookup(t->child[0]->tk->tokenString) == -1){
            //        st_insert(t->child[0]->tk->tokenString, t->child[0]->tk->lineno, location++);
            //    }else{
            //        st_insert(t->child[0]->tk->tokenString, t->child[0]->tk->lineno, 0);
            //    }
            //    break;
            case FACTOR:
                if(t->tk->tokenType == TK_ID){
                    if(st_lookup(t->tk->tokenString) == -1){
                        st_insert(t->tk->tokenString, t->tk->lineno, location++);
                    }else{
                        st_insert(t->tk->tokenString, t->tk->lineno, 0);
                    }
                }
                break;
            default: 
                break;
        }

    }

    void typeError(TreeNode *t, std::string s){
        checkfile << "Type error at line " << t->tk->lineno << s << std::endl;
        Error = true;
    }
    void checkNode(TreeNode *t){
        switch(t->nodetype){
            case LT_EXP:
            case LE_EXP:
            case GT_EXP:
            case GE_EXP:
            case EQ_EXP:
                if(t->child[0]->tk->tokenType != TK_NUM || t->child[1]->tk->tokenType != TK_NUM){
                    typeError(t, "比较运算符的运算数不是整数");
                }
                break;
            case FACTOR:
                if(t->tk->tokenType == TK_NUM){}
            
        }
    }

    void nullProc(TreeNode *t){
        return ;
    }
}

void buildSymTable(TreeNode *t){
    traverse(t, insertNode, nullProc);
    //打印符号表
    printSymTable(symtablefile);
}

void typeCheck(TreeNode *t){
    traverse(t, nullProc, checkNode);

}