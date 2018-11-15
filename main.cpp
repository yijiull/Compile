#include "global.h"
#include "util.h"
int lineno = 0;

std::fstream source;
std::fstream tokenfile;
std::fstream symtablefile;
std::fstream codefile;
std::fstream treefile;
std::fstream checkfile;

char *c;

bool Error;

#define NO_PARSE false

#if NO_PARSE
    #include "scan.h"
#else
    #include "parse.h"
#endif

#include "analyze.h"

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

int main(int argc, char* argv[]){
    std::string file = std::string(argv[1]);
    std::string out = file + ".back";
    std::string sym = file + ".symbal";
    std::string tree = file + ".tree";
    std::string checklog = file + ".checklog";
    source.open(file, std::ios::in);
#if NO_PARSE
    tokenfile.open(out, std::ios::out);
    while(getToken()){};
    for(auto i : tokens){
        std::cout<<i->tokenString<<std::endl;
    }
#else
    symtablefile.open(sym, std::ios::out);
    TreeNode *t = parse();
    treefile.open(tree, std::ios::out);
    checkfile.open(checklog, std::ios::out);
    printTree(t);
    buildSymTable(t);

#endif
}
