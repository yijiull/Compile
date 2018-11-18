#include "global.h"
#include "util.h"
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

    void unDeclaredError(TreeNode *t, std::string s){
        logfile << "unDeclared variable name at line " << t->lineno << s << std::endl;
        Error = true;
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
                        unDeclaredError(t, t->tk->tokenString);
                        //st_insert(t->tk->tokenString, t->tk->lineno, location++);
                    }else{
                        st_insert(t->tk->tokenString,t->valType, t->lineno, 0);
                    }
                }
                break;
            default: 
                break;
        }

    }

    void typeError(TreeNode *t, std::string s){
        logfile << "Type error at line " << t->lineno << ": " << s << std::endl;
        Error = true;
    }
    void checkNode(TreeNode *t){
        switch(t->nodetype){
            case LT_EXP:
            case LE_EXP:
            case GT_EXP:
            case GE_EXP:
                if(t->child[0]->valType != VT_INT || t->child[1]->valType != VT_INT){
                    log("比较运算符的操作数不是int类型", t->lineno);
                }else{
                    t->valType = VT_BOOL;
                }
                break;
            case EQ_EXP:
                if(t->child[0]->valType != t->child[1]->valType){
                    log("相等运算类型不一致", t->lineno);
                }else{
                    t->valType = VT_BOOL;
                }
                break;
            case OR_EXP:
            case AND_EXP:
            case NOT_EXP:
                if(t->child[0]->valType != VT_BOOL || t->child[1]->valType != VT_BOOL){
                    log("逻辑运算符的操作数不是bool类型", t->lineno);
                }else{
                    t->valType = VT_BOOL;
                }
                break;
            case PLUS_EXP:
            case SUB_EXP:
            case MUL_EXP:
            case DIV_EXP:
                if(t->child[0]->valType != VT_INT || t->child[1]->valType != VT_INT){
                    log("算术运算符的操作数不是int类型", t->lineno);
                }else{
                    t->valType = VT_INT;
                }
                break;
            case IF_STMT:
            case WHILE_STMT:
                if(t->child[0]->valType != VT_BOOL){
                    log("IF/WHILE语句的判别式不是bool类型", t->lineno);
                }else{
                    t->valType = VT_BOOL;
                }
                break;
            case ASSIGN_STMT:
                if(t->child[0]->valType != t->child[1]->valType){
                    log("赋值运算类型不一致", t->lineno);
                }else{
                    t->valType = t->child[0]->valType;
                }
                break;
            default:
                break;
        }
    }

    void nullProc(TreeNode *t){
        return ;
    }
}

void buildSymTable(TreeNode *t){
    //traverse(t, insertNode, nullProc); //在建立语法树的时候在parse.cpp中已经同时建立了符号表
    //打印符号表
    printSymTable(symtablefile);
}

void typeCheck(TreeNode *t){
    traverse(t, nullProc, checkNode);

}