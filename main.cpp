#include "global.h"
#include "scan.h"

int lineno = 0;

std::fstream source;
std::fstream listing;
std::fstream code;

char *c;

bool Error;

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
    source.open(file, std::ios::in);
    listing.open(out, std::ios::out);
    while(getToken()){};
}
