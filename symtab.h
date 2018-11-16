void st_insert(std::string name, ValType type, int lineno, int loc);

int st_lookup(std::string name);

ValType st_getType(std::string name);

void printSymTable(std::fstream&);