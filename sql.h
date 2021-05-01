#ifndef SQL_H
#define SQL_H
#include <iostream>
#include "parser_class.h"
#include "table.h"

using namespace std;

class SQL
{
public:
    SQL();
    void run();
    void run_command(char*  command);
    void Batch(char* file);

private:
    string short_command;
    vector<string> field;
    vector<string> condition;
    string table_name;
    string to_upper(string& st);
    Map<string, Table> T;
    long qury_num;
};

#endif // SQL_H
