#include "global.h"
#include "main.h"
#include "util.h"
#include "parse.h"
#include "scan.h"
#include "analyze.h"
#include "cgen.h"
int lineno = 0;
int linepos = 0;

std::fstream source;
std::fstream tokenfile;
std::fstream symtablefile;
std::fstream codefile;
std::fstream treefile;
std::fstream logfile;
std::string file;
namespace{
    std::string out;
    std::string sym;
    std::string tree;
    std::string logf;
    std::string code;
}

bool Error = false;


// read size char from file
/*
string file = "/home/yijiull/code/by/temp.txt";
fstream source;
source.open(file, std::ios::in|std::ios::ate);
if(!source.is_open()){
    std::cout<<"not open\n";
    return 0;
}
int size = source.tellg();
source.seekg(0, std::ios::beg);
std::cout<<"size: "<<size<<std::endl;
int sz = size / 10;
c = new char[size];
while(source.read(c, sz)){
    std::cout<<c<<std::flush;
}
delete[] c;
*/

//设置源文件
void setSourceCode(std::string fileName){
    file = fileName; 
    out = file + ".token";
    sym = file + ".symbal";
    tree = file + ".tree";
    logf = file + ".log";
    code = file + ".code";
}
//只提取token并打印错误到log
void getAllToken(){
    source.open(file, std::ios::in);
    tokenfile.open(out, std::ios::out);
    logfile.open(logf, std::ios::out);
    while(getToken()){};
    std::cout<<"tokens:\n";
    for(auto i : tokens){
        std::cout<<"\t"<<i->tokenString<<std::endl;
    }
    if(Error){
        std::cout << std::string("something is wrong, please check the ") + logf << std::endl;
    }else{
        std::cout << "Success! please check the file:\n\t" + out << std::endl;  
    }
    source.close();
    tokenfile.close();
    logfile.close();
}
//产生token、中间代码、语法树、符号表、错误日志
void generateResult(){
    source.open(file, std::ios::in);
    tokenfile.open(out, std::ios::out);
    symtablefile.open(sym, std::ios::out);
    treefile.open(tree, std::ios::out);
    logfile.open(logf, std::ios::out);
    codefile.open(code, std::ios::out);
    TreeNode *t = parse();
    printTree(t);
    buildSymTable(t);
    typeCheck(t);
    codeGenerate(t);
    if(Error){
        std::cout << std::string("something is wrong, please check the ") + logf << std::endl;
    }else{
        std::cout << "Success! please check the files:\n\t" + sym + "\n\t" + tree + "\n\t" + code << std::endl;  
    }
    source.close();
    tokenfile.close();
    symtablefile.close();
    logfile.close();
    codefile.close();
    treefile.close();
}
//从文件中读取内容
std::string getContent(std::string name){
    std::fstream source;
    source.open(name, std::ios::in|std::ios::ate);
    if(!source.is_open()){
        std::cout<<"cant not open " + name << std::endl;
        return 0;
    }
    int size = source.tellg();
    source.seekg(0, std::ios::beg);
    std::cout<<"size: "<<size<<std::endl;
    int sz = size;
    char *c = new char[size];
    source.read(c, sz);
    std::string res = std::string(c);
    delete[] c;
    return res;
}

int main(int argc, char* argv[]){
    if(argc == 3){
        setSourceCode(argv[2]);
        getAllToken();
    }else{
        setSourceCode(argv[1]);
        generateResult();
    }
}
