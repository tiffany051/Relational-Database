#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <iostream>
#include <fstream>
#include "../CS008_Final_Project/!include/my_map.h"
#include "../CS008_Final_Project/!include/my_mmap.h"
#include "../CS008_Final_Project/!include/file_utility_functions.h"
#include "shunting_yard.h"
#include "rpn.h"
#include "record.h"

using namespace std;

class Table
{
public:
    Table();
    Table(const string& name);
    Table(const string& name, const vector<string>& fields);

    void insert_into(const vector<string>& field_values);

    Table _select_all();
    Table select(const vector<string>& fields);
    Table select_simple_condition(const vector<string>& condition);
    Table select(const vector<string>& fileds, const vector<string>& condition);

    vector<long> simple_conditon(const vector<string>& st);
    Table get_table(vector<long> rec_nos);

    Table select();
    void drop_table();
    void reindex();
    Table filter_col(const vector<string>& fields);
    long get_record_num();
    string get_table_name();
    friend ostream& operator <<(ostream& outs, const Table& T)
    {
        fstream f;
        string file_name = T._tabel_name + string(".bin");
        open_fileRW(f, file_name.c_str());
        Record r;
        long recno = 1;

        long num = 0;
        outs << setw(10) << "Record";

        for (int i = 0; i < T._fields_names.size(); i++)
        {
            outs << setw(15) << T._fields_names.at(i);
        }
        outs << endl;
        r.read(f, recno);
        while(!f.eof())
        {
            outs << setw(10) << num;
            for (int i = 0; i < r.get_record().size(); i++)
            {
                outs << setw(15) << r.get_record().at(i);
            }
            outs << endl;
            recno++;
            r.read(f, recno);
            num++;
        }

        f.close();
        return outs;
    }

private:
    string _tabel_name;
    string file_name;
    vector<MMap<string, long>> _indices;
    vector <string> _fields_names;
    bool empty();
    Map<string, long> _field_map;
    long _serial;
    int _last_record_num;
    void set_field(vector<string> field_name)
    {
        for (int i = 0; i < field_name.size(); i++)
        {
            _fields_names.push_back(field_name[i]);

        }
        //set up the indicies vecotor and update field map
        for (int i = 0;i < _fields_names.size(); i++)
        {
            _field_map.insert(_fields_names[i], i);
            _indices.push_back(MMap<string, long>());
        }
    }
};



#endif // TABLE_H
