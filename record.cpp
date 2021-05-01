#include "record.h"

Record::Record()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        _record[i][0] = NULL;
    }
    _record_num = -1;
    _num_of_fields = 0;
}

Record::Record(const vector<string>& st)
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        _record[i][0] = NULL;
    }
    for (int i = 0; i < st.size(); i++)
    {
        strncpy(_record[i], st[i].c_str(),MAX_ROW);
    }
    _num_of_fields = st.size();
}

long Record::write(fstream& outs)
{
    //write to the end of the file.
    outs.seekg(0, outs.end);

    long pos = outs.tellp();    //retrieves the current position of the
    //      file pointer

    //outs.write(&record[0], sizeof(record));
    outs.write(&_record[0][0], sizeof(_record));

    return pos / sizeof(_record);  //record number
}
long Record::read(fstream& ins, long record_num)
{

    long pos= record_num * sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    ins.read(&_record[0][0], sizeof(_record));
    return ins.gcount();
}

vector<string> Record::get_record()
{
    vector<string> st;
    for (int i = 0; i < MAX_ROW; i++)
    {
        if(_record[i] == " " || _record[i] == ", ")
        {
            break;
        }
        else
        {
           st.push_back(string(_record[i]));
        }
    }
    return st;
}

string Record::operator[](const int row)
{
    return _record[row];
}

