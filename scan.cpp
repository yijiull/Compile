#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>
#include "global.h"  //和下一行不能换？否则函数重定义？
#include "scan.h"
#include "util.h"

enum StateType{
    START, INASSINE, INCOMMENT, INNUM, INID, DONE, 
    INLESSEQUAL, INGREATEREUQAL, INQUOTE
};

std::string tokenString;
std::vector<Token*> tokens;

const int BUFLEN = 256;

namespace{
    std::string linebuf;
    int linepos = 0;
    int bufsize = 0;
    bool EOF_flag = false;
    std::unordered_map<std::string, TokenType> reversedWords = {
        {"if", TK_IF}, {"else", TK_ELSE}, {"then", TK_THEN}, 
        {"end", TK_END}, {"repeat", TK_REPEAT}, {"read", TK_READ},
        {"write", TK_WRITE}, {"until", TK_UNTIL},
        {"true", TK_TRUE}, {"false", TK_FALSE}, {"or", TK_OR}, 
        {"and", TK_AND}, {"not", TK_NOT}, {"int", TK_INT}, 
        {"bool", TK_BOOL}, {"string", TK_STRING}, {"while", TK_WHILE}, {"do", TK_DO}
    };

    int getNextChar(){
        if(linepos < bufsize){
            return linebuf[linepos++];
        }
        if(getline(source, linebuf)){
            lineno++;
            bufsize = linebuf.size();
            //std::cout<<linebuf<<std::endl;
            //std::cout<<int(linebuf[bufsize-1])<<std::endl;
            //std::cout<<bufsize<<std::endl;
            linepos = 0;
			listing << lineno << ": " << linebuf << std::endl;
            return linebuf[linepos++];
        }else{
            EOF_flag = true;
            return EOF;
        }
    }

    void ungetNextChar(){
        if(!EOF_flag){
            linepos--;
        }
    }

    TokenType reversedLookup(std::string s){
        if(reversedWords.count(s)){
            return reversedWords[s];
        }
        return TK_ID;
    }
    void insertToken(TokenType tokentype){
        Token *token = new Token();
        token->tokenType = TK_ID;
        token->tokenString = tokenString;        
        tokens.push_back(token);
    }

};

TokenType getToken(){
    tokenString.clear();
    TokenType curTK;
    StateType state = START;
    bool save;
    while(state != DONE){
        int c = getNextChar();
        //std::cout<<char(c)<<std::endl;
        save = true;
        switch(state){
            case START:
                if(isdigit(c)){
                    state = INNUM;
                }else if(isalpha(c)){
                    state = INID;
                }else if(c == ':'){
                    state = INASSINE;
                }else if(c == '<'){
                    state = INLESSEQUAL;
                }else if(c == '>'){
                    state = INGREATEREUQAL;
                }else if(c == ' ' || c == '\n' || c == '\t' || c == '\r'){   //回车符 '\r' 2h
                    save = false;
                }else if(c == '{'){
                    save = false;
                    state = INCOMMENT;
                }else if(c == '\''){
                    state = INQUOTE;
                }else{
                    state = DONE;
                    switch(c){
                        case EOF:
                            save = false;
                            curTK = TK_ENDFILE;
                            break;
                        case '=':
                            curTK = TK_EQ;
                            break;
                        case '+':
                            curTK = TK_PLUS;
                            break;
                        case '-':
                            curTK = TK_MINUS;
                            break;
                        case '*':
                            curTK = TK_TIMES;
                            break;
                        case '/':
                            curTK = TK_OVER;
                            break;
                        case '(':
                            curTK = TK_LPAREN;
                            break;
                        case ')':
                            curTK = TK_RPAREN;
                            break;
                        case ';':
                            curTK = TK_SEMI;
                            break;
                        case ',':
                            curTK = TK_COMMA;
                            break;
                        default:
                            curTK = TK_ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                save = false;
                if(c == EOF){
                    state = DONE;
                    curTK = TK_ENDFILE;
                }else if(c == '}'){
                    state = START;
                }
                break;
            case INASSINE:
                state = DONE;
                if(c == '='){
                    curTK = TK_ASSIGN;
                }else{
                    ungetNextChar();
                    save = false;
                    curTK = TK_ERROR;
                }
                break;
            case INNUM:
                if(!isdigit(c)){
                    save = false;
                    ungetNextChar();
                    state = DONE;
                    curTK = TK_NUM;
                }
                break;
            case INID:
                if(!isalnum(c)){
                    save = false;
                    ungetNextChar();
                    state = DONE;
                    curTK = TK_ID;
                }
                break; //!!
            case INLESSEQUAL:
                state = DONE;
                if(c == '='){
                    curTK = TK_LE;
                }else{
                    ungetNextChar();
                    save = false;
                    curTK = TK_LT;
                }
                break;
            case INGREATEREUQAL:
                state = DONE;
                if(c == '='){
                    curTK = TK_GE;
                }else{
                    ungetNextChar();
                    save = false;
                    curTK = TK_GT;
                }
                break;
            case INQUOTE:
                if(c == '\''){
                    curTK = TK_STR;
                    state = DONE;
                }else if(c == '\n'){
                    curTK = TK_ERROR;
                    save = false;
                    ungetNextChar();
                }
                break;
            case DONE:
            default:
                // never here
                std::cout<<"bug default at line 200" << std::endl;
                break;
        }
        if(save && tokenString.size() < MAXTOKENLEN){
            tokenString.push_back(char(c));
        }
        if(state == DONE){
            if(curTK == TK_ID){
                curTK = reversedLookup(tokenString);
            }
        }
    }
	listing << "\t" << lineno << ": " << std::flush;
    printToken(curTK, tokenString);
    insertToken(curTK);
    return curTK;
}
//int main(){
//    auto it = reversedWords.begin();
//    while(it != reversedWords.end()){
//        std::cout<<(*it).first<<"  "<<(*it).second<<std::endl;
//        it++;
//    }
//}
