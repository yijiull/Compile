#include <string>
#include <fstream>
#include "symtab.h"
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::pair<int, std::vector<int>>> symTable;


void st_insert(std::string name, int lineno, int loc){
    if(symTable.count(name)){
        auto &p = symTable[name];
        p.second.push_back(lineno);

    }else{
        auto &p = symTable[name];
        p.first = loc;
        p.second.push_back(lineno);
    }
}

int st_lookup(std::string name){
    if(symTable.count(name)){
        return symTable[name].first;
    }else{
        return -1;
    }
}

void printSymTable(std::fstream &symtablefile){
    symtablefile << "Variable Name    Location    Line Numbers\n";
    symtablefile << "-------------    --------    ------------\n";
    symtablefile.setf(std::ios::left);
    for(auto p : symTable){
        symtablefile.width(17);
        symtablefile << p.first;
        symtablefile.width(12);
        symtablefile << p.second.first;
        symtablefile.width();
        for(auto i : p.second.second){
            symtablefile << std::to_string(i) + ", ";
        }
        symtablefile << "\n";
    }
}