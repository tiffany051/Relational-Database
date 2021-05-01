#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include<iostream>
#include<fstream>
#include <iomanip>
#include<string.h>

using namespace std;

class Record{
public:
    Record();
    Record(const vector<string>& st);

    long write(fstream& outs);
    long read(fstream& ins, long record_num);
    vector<string> get_record();
    string operator[](const int row);
//    vector<>

    friend ostream& operator <<(ostream& outs, const Record& r)
    {
        for (int i = 0; i < r.MAX_ROW; i++)
        {
            outs << string(r._record[i]);
        }
        return outs;
    }

private:
    static const int MAX_ROW = 20;
    static const int MAX_COL = 50;
    int _record_num;
    int _num_of_fields;
    char _record[MAX_ROW][MAX_COL];
};

#endif // RECORD_H
