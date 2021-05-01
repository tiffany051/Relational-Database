#include "parser_class.h"

Parser_Class::Parser_Class(char* s)
{
    strcpy(_buffer, s);//copy s to internal buffer
    make_table(adjacenct_table);//initialize adjacency table
    build_key_word_list(_buffer);//build keyword list
    set_string(_buffer);//set string
}

void Parser_Class::set_string(char str[])
{
    STokenizer st(str);
    Token t;
    st >> t;

    while(!st.done())
    {
        if(t.token_str() != " ")
        {
            inputq.push_back(t.token_str());
        }
        st >> t;
    }
    if(t.token_str() != " ")
    {
        inputq.push_back(t.token_str());
    }
//    inputq.push_back(t.token_str());
    //calls get_parse_tree
    get_parser_tree();
}

bool Parser_Class::get_parser_tree()
{
    int state = 0;
    int column_no = 0;
    string token = "";

    vector<string> v_condition;
    string condition = "";
    string drop = "";
    string create = "";
    string insert = "";
    string my_t = "";
    string fil_name = "";
    int quo = 0;

    for (int i = 0; i < inputq.size(); i++)
    {
        token = inputq[i];
        if(token == " " && inputq.size() < i)
        {
            i++;
            token = inputq[i];
        }
        column_no = build_key_word_list(token);//this will return which column it is
        state = adjacenct_table[state][column_no];//next state
        switch(state)
        {
        case 1://token that brought you here was "Select"
            if(token != ",")
            {
                ptree["command"] += token;
            }
            break;

        case 2://the token is the field name
            ptree["field"] += token;
            break;

        case 3://from: we don't care about this token
            break;

        case 4://our token was the table name
            ptree["table"] += token;
            break;

        case 5:// where or and
            if(inputq.size() == i + 1)
            {
                condition += " " + token;
                ptree["condition"] += " " + condition;
            }
            else if(token != "where")// and/ or
            {
                v_condition.push_back(token);
            }
            break;

        case 6://this is the condition
            v_condition.push_back(token);
            break;

        case 7://our token was operators
//            cout << "case 7 enter: my_t=" << my_t << ":toekn:" << token << ":quonum:" << quo << endl;
            if (quo == 1 && token == "\"")
            {
                v_condition.push_back(my_t);
                ptree["condition"] += v_condition;
                my_t = "";
                quo = 0;
            }
             else if (token == "\"")
            {
//                cout << "token:" << token << ":my_t:" << my_t << endl;
                v_condition.push_back( " " + my_t);
//                ptree["condition"] += v_condition;
                my_t = "";
                quo = 1;
            }
            else if (quo == 1)
            {
                my_t += token;
//                 cout<< "[" << my_t << "]" << endl;
            }

            else//= and othe operator
            {
                v_condition.push_back(token);
            }

            break;

        case 8://our token was a condition
//            cout << "case 8 enter: my_t=" << my_t << ":toekn:" << token << ":quonum:" << quo << endl;
            if(quo == 0 && token == "\"")
            {
                quo = 1;
            }
            else if(inputq.size() == i + 1)
            {

                if(!my_t.empty())
                {
                    v_condition.push_back(my_t);
                    my_t = "";
                    quo = 0;
                }
                else
                {
                    v_condition.push_back(" " + token);
                }

                ptree["condition"] += v_condition;
                quo = 0;
            }
            else if (quo == 1 && token == "\"")
            {
                v_condition.push_back(my_t);
                my_t = "";
                quo = 0;
            }
            else if (quo == 1)
            {
                my_t += " " + token;
//                cout << "---[" << my_t << "}---" << endl;
            }
            else
            {
                if(!my_t.empty())
                {
                   v_condition.push_back(my_t);
                   my_t = "";
                   quo = 0;
                }
                else {
                    v_condition.push_back(token);
                }

//                ptree["condition"] += v_condition;
            }
            break;

        case 9://our token was the 'table'
            create += " " + token;
            break;

        case 10://our token was the 'table'
            if(!create.empty())
            {
                create += " " + token;
                ptree["command"] += create;
            }
            else if (!drop.empty())
            {
                drop += " " + token;
                ptree["command"] += drop;
            }
            else {
                insert += " " + token;
                ptree["command"] += insert;
            }
            break;

        case 11://our token was the table name
            ptree["table"] += token;
            break;

        case 12:/*field name*/
            break;

        case 13://our token was the field

            if(quo == 0 && token == "\"")
            {
                quo = 1;
            }
            else if (token == "\"" && quo == 1)
            {
//                cout << "token got assed" << endl;
                ptree["field"] += my_t;
                my_t = "";
                quo = 0;
            }
            else if (quo == 1)
            {
//                cout << "my token: " << token << endl;
                my_t += " " + token;
            }
            else
            {
                ptree["field"] += token;
                quo = 0;
            }

            break;

        case 14://our token was the table name
            insert += token;
            break;

        case 15://our token was the table name
            //            ptree["command"] += token;
            drop += token;
            break;
        case 16://batch
            ptree["command"] += token;
            break;

        case 17://file name
            fil_name += token;
            break;

        case 18:
            if(token == ".")
            {
                fil_name += token;
            }
            else
            {
                fil_name += token;
                ptree["filename"] += fil_name;
            }
            break;
        }
    }

//    cout << "get oty while kllop" << adjacenct_table[state][0] << endl;
    //return true if it ended with sucess state
    if(adjacenct_table[state][0] == 1)
    {
//        cout << "Sucess ajacensyc Matrix" << endl;
        return true;
    }
    else
    {
        ptree.clear();//reset ptree
        return false;
    }

}
vector<string>& Parser_Class::convert_condition(const vector<string>& condition)
{
    char arr[300] = "";
    strcpy(arr, condition[0].c_str());
//    cout << arr << endl;
    STokenizer st(arr);
    Token t;
    st >> t;
    string next_token = "";
    string token = "";
    string name = "";
    while(!st.done())
    {
        //when the token is not space
        if(t.type() != 4)
        {
            string st = t.token_str();
            result.push_back(t.token_str());
        }
        st >> t;
    }
    st >> t;
    result.push_back(t.token_str());
    return result;
}
int Parser_Class::build_key_word_list(const string st)
{
//    cout << "st: " << st << endl;
    if(st == "Select" || st == "select" || st == "SELECT")
    {
        return SELECT;
    }
    else if(st == "From" || st == "from" || st == "FROM")
    {
        return FROM;
    }
    else if (st == ",")
    {
        return COMMA;
    }
    else if(st == "Where" || st == "where" || st == "WHERE")
    {
        return WHERE;
    }
    else if (st == "=")
    {
        return EQUAL;
    }
    else if (st == "<")
    {
        return LESS;
    }
    else if (st == ">")
    {
        return GREATER;
    }
    else if (st == "<=")
    {
        return LESSTHAN;
    }
    else if (st == ">=")
    {
        return GREATERTHAN;
    }
    else if (st == "(")
    {
        return LPARENTHESIS;
    }
    else if (st == ")")
    {
        return RPARENTATHESIS;
    }
    else if(st == "CREATE" || st == "Create" || st == "create")
    {
        return CREATE;
    }
    else if(st == "Make" || st == "MAKE" || st == "make")
    {
        return MAKE;
    }
    else if(st == "TABLE" || st == "Table" || st == "table")
    {
        return TABLE;
    }
    else if(st == "FIELDS" || st == "fields" || st == "Fields")
    {
        return FIELDS;
    }
    else if(st == "INSERT" || st == "Insert" || st == "insert")
    {
        return INSERT;
    }
    else if(st == "INTO" || st == "into" || st == "Into")
    {
        return INTO;
    }
    else if(st == "VALUES" || st == "values" || st == "Values")
    {
        return VALUE;
    }
    else if(st == "DROP" || st == "drop" || st == "Drop")
    {
        return DROP;
    }
    else if(st == "AND" || st == "and" || st == "AND")
    {
        return AND;
    }
    else if(st == "OR" || st == "Or" || st == "or")
    {
        return OR;
    }
    else if(st == "*")
    {
        return STAR;
    }
    else if (st == "BATCH" || st == "batch" || st == "Batch")
    {
        return  BATCH;
    }
    else if (st == " ")
    {

    }
    else
    {
        return SYM;//for symbol
    }
}

MMap<string, string> Parser_Class::parse_tree()
{
    return ptree;
}

