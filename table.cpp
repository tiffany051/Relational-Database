#include "table.h"
Table::Table()
{

    _tabel_name = "";
    file_name = "";
    _serial = 0;
    _last_record_num = 0;
    _fields_names.push_back(" ");
}

Table::Table(const string& name)
{

    Record r(_fields_names);
    _serial = 0;
    _tabel_name = name;
    file_name = _tabel_name.c_str() + string(".bin");
    fstream f;
    open_fileRW(f, file_name.c_str());
    r.read(f,0);
    //set up the field names
    for (int i = 0;i < r.get_record().size(); i++)
    {
        _fields_names.push_back(r.get_record().at(i));
    }
    set_field(_fields_names);
    reindex();
    f.close();
}
Table::Table(const string& name, const vector<string>& fields)
{
    _serial = 0;
    set_field(fields);
    fstream f;
    _tabel_name = name;
    file_name = _tabel_name.c_str() + string(".bin");
    open_fileW(f, file_name.c_str());

    Record r(_fields_names);
    long recno = r.write(f);
    f.close();
}

void Table::insert_into(const vector<string>& field_values)
{
    fstream f;
    open_fileRW(f, file_name.c_str());
    Record r(field_values);
    long recno = r.write(f);

    //update
    for (int i = 0;i < field_values.size(); i++)
    {
        if(field_values[i] != "\0")
        {
            _indices[i][field_values[i]] += recno;
        }
    }

    f.close();
}

Table Table::_select_all()
{
    Record r;
    fstream f;
    open_fileRW(f, file_name.c_str());

    int new_num = _serial++;
    string temp_file_name = _tabel_name.c_str() + to_string(new_num);
    vector<string> temp_field_names = _fields_names;
    Table temp(temp_file_name, temp_field_names);

    long recno = 1;
    int count  = 0;
    r.read(f, recno);
    while(!f.eof())
    {
        Record temp_record = r;
        temp.insert_into(temp_record.get_record());
        recno++;
        count++;
        r.read(f, recno);
    }
    cout << "Table: " << (_tabel_name + to_string(_serial)) << " Record:" << count << endl;
    f.close();
    return temp;
}

long Table::get_record_num()
{
    return _last_record_num;
}
string Table::get_table_name()
{
    string t_n = _tabel_name + to_string(_serial);
    return t_n;
}
Table Table::filter_col(const vector<string>& fields)
{
    fstream f;
    open_fileRW(f, file_name.c_str());
    string temp_name = _tabel_name.c_str() + to_string(_serial++);

    vector<int> col_numbers;

    vector<string> temp_field_name;
    //this loop will get the match fields's column number
    //and plce into a vector
    for (int i = 0; i < _fields_names.size(); i++)
    {
        for (int j = 0; j < fields.size(); j++)
        {
            if(_fields_names[i] == fields[j])
            {
                col_numbers.push_back(i);
                temp_field_name.push_back(_fields_names[i]);
            }
        }
    }
    //create a new table
//    Table temp(temp_name, temp_field_name);
    Table temp(temp_name);
    temp.set_field(temp_field_name);
    Record r;
    long recno = 1;
    r.read(f, recno);
    while(!f.eof())
    {
        Record temp_record = r;
        vector<string> match_col;
        //get the sting of that column and place into the match_col vector
        //so we could insert into the temp table
        for (int i = 0;i < col_numbers.size(); i++)
        {
            string st = temp_record.get_record().at(col_numbers[i]);
            match_col.push_back(st);
        }
        temp.insert_into(match_col);
        recno++;
        r.read(f, recno);
    }
    f.close();
    return temp;
}
Table Table::select(const vector<string>& fields)
{
    return filter_col(fields);
}
Table Table::select_simple_condition(const vector<string>& condition)
{
//    return select_simple_condition(condition[0], condition[1], condition[2]);

    Queue<sy_Token*> infix;
    for (int i = 0;i < condition.size(); i++)
    {
        if(condition[i] == "or" || condition[i] == "Or" || condition[i] == "OR")
        {
            infix.push(new Logical_operator("OR"));
        }
        else if (condition[i] == "and" || condition[i] == "And" || condition[i] == "AND")
        {
            infix.push(new Logical_operator("AND"));
        }
        else if (condition[i] == "=" || condition[i] == "<" || condition[i] == ">" || condition[i] == "<="|| condition[i] == ">=")
        {
            infix.push(new Operator(condition[i]));
        }
        else if(condition[i] == "(")
        {
            infix.push(new Left_parenthesis(condition[i]));
        }
        else if(condition[i] == ")")
        {
            infix.push(new Right_Parenthesis(condition[i]));
        }
        else if(condition[i] != " ")
        {
            infix.push(new Alpha(condition[i]));
        }
    }
    shunting_yard sy(infix);
    Queue <sy_Token*> post_fix= sy.postfix();

    RPN rpn(post_fix, _indices, _field_map);
    vector<long> result = rpn();
    return get_table(result);
}

Table Table::select(const vector<string>& fileds, const vector<string>& condition)
{
    Table t;
    if(condition.size() == 0)
    {
        t = filter_col(fileds);
    }
    else
    {
        Table temp = filter_col(fileds);
        t = temp.select_simple_condition(condition);
    }
    return t;
}

vector<long> Table::simple_conditon(const vector<string>& st)
{
   Queue<sy_Token*> infix;
   for (int i = 0;i < st.size(); i++)
   {
       if(st[i] == "or" || st[i] == "and")
       {
           infix.push(new Logical_operator(st[i]));
       }
       else if (st[i] == "=" || st[i] == "<" || st[i] == ">" || st[i] == "<="|| st[i] == ">=")
       {
            infix.push(new Operator(st[i]));
       }
       else if(st[i] == "(")
       {
           infix.push(new Left_parenthesis(st[i]));
       }
       else if(st[i] == "}")
       {
           infix.push(new Right_Parenthesis(st[i]));
       }
       else if(st[i] != " ")
       {
           infix.push(new Alpha(st[i]));
       }
   }
   shunting_yard sy(infix);
   Queue <sy_Token*> post_fix= sy.postfix();
//   post_fix.pop()->print();

   RPN rpn(post_fix, _indices, _field_map);
   vector<long> result = rpn();
   return result;
}

Table Table::get_table(vector<long> rec_nos)
{
    vector <long> get_reco;

//    cout << "record number bfore: " << rec_nos << "size: " << rec_nos.size() << endl;
    for (int i = 0; i < rec_nos.size();i++)
    {
        get_reco.push_back(rec_nos[i]);
    }
//    cout << "get recorn in table:" << get_reco << endl;
    Record r;
    fstream f;
    open_fileRW(f, file_name.c_str());

    cout << "Table: " << (_tabel_name + to_string(_serial));
    string temp_file_name = _tabel_name.c_str() + to_string(_serial++);
    vector<string> temp_field_names = _fields_names;
    Table temp(temp_file_name, temp_field_names);

    int count = 0;
    for (int i = 0; i < rec_nos.size(); i++)
    {
        r.read(f, rec_nos[i]);
        temp.insert_into(r.get_record());
        count++;
    }
    _last_record_num = count;
    int num = _serial - 2;
//    cout << "Table: " << (_tabel_name + to_string(num)) << " Record:" << count << endl;
    cout << " Record:" << count << endl;
    f.close();
    return temp;
}


void Table::reindex()
{
    fstream f;
    open_fileRW(f, file_name.c_str());
    _fields_names.clear();
    MMap<string, long> mmap;
    int record_num = 0;
    Record r;
    r.read(f, record_num);
    while(!f.eof())
    {
        if(record_num == 0)//the field names
        {
            vector<string> field_name = r.get_record();
            for (int i = 0;i < field_name.size();i++)
            {
                if(field_name[i] != "")
                {
                    _fields_names.push_back(field_name[i]);
                }
            }
            for (int i = 0; i < _fields_names.size();i++)
            {//place the field names in the indices
                _field_map.insert(_fields_names[i], i);
                MMap<string, long> mmap = MMap<string, long>();
                _indices.push_back(mmap);
            }
        }
        else//place the rest of the field
        {
            long temp_record_num = record_num - 1;
            for (int i = 0;i < _fields_names.size();i++)
            {
                vector<string> values = r.get_record();
                for (int i = 0; i < _fields_names.size();i++)
                {//place the field names in the indices
                    _indices[i].insert(values[i], temp_record_num);
                }
            }
            _last_record_num++;
        }
        record_num++;
        r.read(f, record_num);
    }
    f.close();
}
void Table::drop_table()
{
    remove(file_name.c_str());
}



