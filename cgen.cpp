#include "global.h"
#include "cgen.h"
#include "symtab.h"
#include "util.h"
std::vector<Code*> codes;

namespace{
    int id = 0; //临时变量计数
    std::string newTemp(){
        return "_t" + std::to_string(id++);
    }

    void pt(std::string s){
        codefile << s << std::endl;
    }

    void backpatch(int a, int b){
        auto p = codes[a];
        while(p != nullptr){
            p->jump = b;
            p = p->nxt;
        }

    }
    int merge(int a, int b){
        auto p1 = codes[a], p2 = codes[b];
        auto p = p2;
        while(p2->nxt != nullptr) p2 = p2->nxt;
        p2->nxt = p1;
        return p->pos;
    }

    void opGoto(TreeNode *t, std::string s, const std::string &t1, const std::string &t2){
        t->T = codes.size();
        t->B = t->T;
        t->F = t->T + 1;
        Code *code1 = newCode();
        code1->stmt = "if " + t1 + " " + s + " " + t2 + " goto ";
        //std::cout<<code1->stmt<<std::endl;
        codes.push_back(code1);
        Code *code2 = newCode();
        code2->stmt = "goto ";
        codes.push_back(code2);
    }

    std::string cgen(TreeNode *t){
        if(t == nullptr){
            return "";
        }
        //std::cout<<t->lineno<<std::endl;
        //std::cout<<t->nodetype<<std::endl;
        std::string name;
        switch(t->nodetype){
            case IF_STMT:{
                t->child[0]->B = codes.size();
                cgen(t->child[0]);
                int then_b = codes.size();
                cgen(t->child[1]);

                Code *code = newCode();
                code->stmt = "goto ";
                codes.push_back(code);         //

                int else_b = codes.size();
                cgen(t->child[2]);
                code->jump = codes.size();     // !!
                backpatch(t->child[0]->F, else_b);
                backpatch(t->child[0]->T, then_b);
                break;
            }
            case READ_STMT:{
                Code *code = newCode();
                code->stmt = "read " + t->child[0]->tk->tokenString;
                codes.push_back(code);
                break;
            }
            case WRITE_STMT:{
                Code *code = newCode();
                code->stmt = "write " + t->child[0]->tk->tokenString;
                codes.push_back(code);
                break;
            }
            case REPEAT_STMT:{
                int repeat_b = codes.size();
                cgen(t->child[0]);
                t->child[1]->B = codes.size();
                cgen(t->child[1]);
                backpatch(t->child[1]->T, repeat_b);
                backpatch(t->child[1]->F, codes.size());
                break;
            }
            case WHILE_STMT:{
                t->child[0]->B = codes.size();
                cgen(t->child[0]);
                int while_t = codes.size();
                cgen(t->child[1]);
                backpatch(t->child[0]->T, while_t);
                backpatch(t->child[0]->F, codes.size());
                break;
            }
            case STMT_SEQUENCE:{
                cgen(t->child[0]);
                cgen(t->child[1]);
                break;
            }
            case ASSIGN_STMT:{
                Code *code = newCode();
                name = cgen(t->child[1]);
                code->stmt = t->child[0]->tk->tokenString + " := " + name;
                codes.push_back(code);
                break;
            }
            case GT_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                opGoto(t, ">", t1, t2);
                break;
            }
            case GE_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                opGoto(t, ">=", t1, t2);
                break;
            }
            case LT_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                opGoto(t, "<", t1, t2);
                break;
            }
            case LE_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                opGoto(t, "<=", t1, t2);
                break;
            }
            case EQ_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                opGoto(t, "=", t1, t2);
                break;
            }
            case AND_EXP:{
                cgen(t->child[0]);
                cgen(t->child[1]);
                backpatch(t->child[0]->T, t->child[1]->B);
                t->B = t->child[0]->B;
                t->T = t->child[1]->T;
                t->F = merge(t->child[0]->F, t->child[1]->F);
                break;
            }
            case OR_EXP:{
                cgen(t->child[0]);
                cgen(t->child[1]);
                backpatch(t->child[0]->F, t->child[1]->B);
                t->B = t->child[0]->B;
                t->T = merge(t->child[0]->T, t->child[1]->T);
                t->F = t->child[1]->F;
                break;
            }
            case NOT_EXP:{
                // 没有not的文法
                break;
            }
            case PLUS_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                name = newTemp();
                Code *code = newCode();
                code->stmt = name + " := " + t1 + " + " + t2;
                //std::cout<<code->stmt<<std::endl;
                codes.push_back(code);
                break;
            }
            case SUB_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                name = newTemp();
                Code *code = newCode();
                code->stmt = name + " := " + t1 + " - " + t2;
                codes.push_back(code);
                break;
            }
            case MUL_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                name = newTemp();
                Code *code = newCode();
                code->stmt = name + " := " + t1 + " * " + t2;
                codes.push_back(code);
                break;
            }
            case DIV_EXP:{
                auto t1 = cgen(t->child[0]);
                auto t2 = cgen(t->child[1]);
                name = newTemp();
                Code *code = newCode();
                code->stmt = name + " := " + t1 + " / " + t2;
                codes.push_back(code);
                break;
            }
            case FACTOR:{
                name = t->tk->tokenString;
                break;
            }
            default:
                break;
        }
        return name;
    }
}
void codeGenerate(TreeNode *t){
    Code *code = newCode();
    code->stmt = "start";
    codes.push_back(code);
    cgen(t);
    int i = 0;
    for(auto code : codes){
        if(code->jump != -1) code->stmt += std::to_string(code->jump);
        pt(std::to_string(i) + ") " + code->stmt);
        i++;
    }
    pt(std::to_string(i) + ") " + "end");
}
