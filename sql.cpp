#include "sql.h"

SQL::SQL()
{
    T = Map<string, Table>();
    qury_num = 0;
}

void SQL::run()
{
    char my_string[300] = "";
    cout << "> ";
    cin.getline(my_string, 300);
    cout << ":" << my_string << ":" << endl;

    while(strcmp(my_string, "Exit") != 0)
    {
        run_command(my_string);
        cout << "> ";
        cin.getline(my_string, 300);
    }
}
void SQL::run_command(char*  command)
{
    if(command[0] == '\0')
    {
        cout << endl;
    }
    else if (command[0] == '/')
    {
        cout << command << endl;
    }
    else
    {
        Parser_Class p(command);

//        cout << "Table name: " << T[table_name].get_table_name() << ", records:" << T[table_name].get_record_num() << endl;

        MMap<string, string> ptree = p.parse_tree();

//        cout << ptree<< endl;

        string _command = to_upper(ptree["command"].front());
        if(_command == "SELECT")
        {
            cout << "[" << qury_num << "]" << command << endl;
            qury_num++;
            table_name = ptree["table"].front();
            field = ptree["field"];
            //there is condition
            if(!ptree["condition"].empty())
            {

//                cout << "QQQQQQQQQQQQ" << ptree["field"][0] << endl;
                if(ptree["field"].front() == "*")
                {
                    cout << T[table_name].select_simple_condition(ptree["condition"]) << endl;
//                    cout << "eng1 " << endl;
                }
                else
                {
                    cout << T[table_name].select(field, ptree["condition"]) << endl;
                }
            }
            else
            {
                if(ptree["field"].front() == "*")
                {
                    cout << T[table_name]._select_all() << endl;
                }
                else
                {
                    cout << T[table_name].select(field, ptree["field"]) << endl;
                }

            }
        }
        else if(_command == "BATCH")
        {
            string st = ptree["filename"].front().c_str();
            char ch[st.size() + 1];
            strcpy(ch, st.c_str());
            Batch(ch);
        }
        else if (_command == " MAKE TABLE" || _command == " CREATE TABLE")
        {
            cout << "[" << qury_num << "]" << command << endl;
            qury_num++;
            table_name = ptree["table"].front();
            field = ptree["field"];
            T.insert(table_name,Table(table_name, field));
            cout << T[table_name]._select_all() << endl;
        }
        else if (_command == "INSERT INTO")
        {
            cout << "[" << qury_num << "]" << command << endl;
            qury_num++;
            table_name = ptree["table"].front();
            field = ptree["field"];
            T[table_name].insert_into(field);
        }
        else if (_command == "DROP TABLE")
        {
            cout << "[" << qury_num << "]" << command << endl;
            qury_num++;
            table_name = ptree["table"].front();
            field = ptree["field"];
//            Table T(table_name);
            T[table_name].drop_table();
        }
        else
        {
            cout << "ERROR COMMAND" << endl;
        }

        cout << endl << "SQL::DONE" << endl;
    }
}

string SQL::to_upper(string& st)
{
    for(unsigned int i=0;i<st.length();i++)
    {
        st[i] = toupper(st[i]);
    }
    return st;
}

void SQL::Batch(char* file)
{
     ifstream i;
     i.open(file);
     if(i.fail())
     {
         cout << "Fail to open file" << endl;
     }

     string comm = "";
     while (!i.eof())
     {
         getline(i, comm);
         int size = comm.size() + 1;
         char ch[size];
         strcpy(ch, comm.c_str());
         run_command(ch);
     }
}

