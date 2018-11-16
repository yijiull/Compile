#include <string>
#include <fstream>
#include "global.h"
#include "symtab.h"
#include <unordered_map>
#include <vector>

struct Symbol{
    int location;
    std::vector<int> lines;
    ValType valType;
};

std::unordered_map<std::string, Symbol> symTable;


void st_insert(std::string name, ValType type, int lineno, int loc){
    if(symTable.count(name)){
        auto &p = symTable[name];
        p.lines.push_back(lineno);
    }else{
        auto &p = symTable[name];
        p.location = loc;
        p.valType = type;
        p.lines.push_back(lineno);
    }
}

int st_lookup(std::string name){
    if(symTable.count(name)){
        return symTable[name].location;
    }else{
        return -1;
    }
}
ValType st_getType(std::string name){
    //首先要确认符号表里有这个符号
    return symTable[name].valType;
}

void printSymTable(std::fstream &symtablefile){
    symtablefile << "Variable Name    ValType    Location    Line Numbers\n";
    symtablefile << "-------------    -------    --------    ------------\n";
    symtablefile.setf(std::ios::left);
    for(auto p : symTable){
        symtablefile.width(17);
        symtablefile << p.first;
        symtablefile.width(11);
        switch(p.second.valType){
            case VT_INT:
                symtablefile << "int";
                break;
            case VT_BOOL:
                symtablefile << "bool";
                break;
            case VT_STRING:
                symtablefile << "string";
                break;
            default:
                break;
        }
        symtablefile.width(12);
        symtablefile << p.second.location;
        symtablefile.width();
        for(auto i : p.second.lines){
            symtablefile << std::to_string(i) + ", ";
        }
        symtablefile << "\n";
    }
}