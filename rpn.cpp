#include "rpn.h"

RPN::RPN(Queue <sy_Token*> postfix, vector<MMap<string, long> > indices, Map<string, long> field_name):_post_fix(postfix), _indices(indices), _field_name(field_name)
{

}

vector<long> RPN::operator()()
{
    Queue <sy_Token*> _before = _post_fix;
    Stack_class<sy_Token*> result;

    while(!_before.empty())
    {
        sy_Token* begin = _before.pop();
//        begin->print();
        if (begin->type_of() == OPERATOR)
        {
            Operator* _op = static_cast <Operator*>(begin);
            string op = _op->get_operator();
            sy_Token* value = result.pop();
            sy_Token* field = result.pop();

            //get string og valeu
            Alpha* _v = static_cast <Alpha*>(value);
            string v = _v->get_alpha();

            //get string of field
            Alpha* _f = static_cast <Alpha*>(field);
            string f = _f->get_alpha();

            int index = _field_name.get(f);
            MMap<string, long> temp = _indices[index];

            string st = "";
            make_string(st, v);
            string my_st = " " + st;
            if(op == "=")
            {
                vector<long> result_v;
                if(_indices[index].contains(my_st))//contain space
                {

                    result_v += temp.get(my_st);
                }
                if(_indices[index].contains(st))//contain no space
                {
                    result_v += temp.get(st);
                }
                 vector_long insert(result_v);
                 result.push(new vector_long(result_v));
                 //                cout << "my vector long=:"<< result_v << endl;
             }
            else if(op == "<")
            {
//                cout << "less enter: "<< endl;
                MMap<string, long>::Iterator low = temp.lower(st);
                vector<long> result_v;

                for (MMap<string, long>::Iterator it = temp.begin(); it != low; it++)
                {
                    string st1 = "";
                    make_string(st1, (*it).key);
                    if(st1 < st)
                    {
                        result_v += (*it).value_list;
                    }
                }
                vector_long insert(result_v);
                result.push(new vector_long(result_v));
            }
            else if (op == ">")
            {
                MMap<string, long>::Iterator high = temp.upper(st);
                vector<long> result_v;
                int i = 0;
                for (MMap<string, long>::Iterator it = temp.begin(); it !=  temp.end(); it++)
                {
                    string st1 = "";
                    make_string(st1, (*it).key);
//                    cout << "<=st1:" << st1 << ":st:" << st << ":key:" << (*it).key << ":v:" << v <<endl;
                    if(st1 > st)
                    {
                        result_v += (*it).value_list;
                    }
                }
                vector_long insert(result_v);
                result.push(new vector_long(result_v));
            }
            else if (op == "<=")
            {
                MMap<string, long>::Iterator upper = temp.upper(st);
                vector<long> result_v;
                string st1 = "";

                for (MMap<string, long>::Iterator it = temp.begin(); it != temp.end(); it++)
                {

                    make_string(st1, (*it).key);
//                    cout << ">=st1:" << st1 << ":st:" << st << ":key:" << (*it).key << endl;
                    if(st1 <= st)
                    {
                        result_v += (*it).value_list;
                    }
                }
                vector_long insert(result_v);
                result.push(new vector_long(result_v));
            }
            else if (op == ">=")
            {
                MMap<string, long>::Iterator lower = temp.lower(st);
                vector<long> result_v;
                 string st1 = "";
                for (MMap<string, long>::Iterator it = temp.begin(); it != temp.end(); it++)
                {
                    make_string(st1, (*it).key);
//                    cout << "<=st1:" << st1 << ":st:" << st << ":key:" << (*it).key << ":v:" << v <<endl;

                    if(st1 >= st)
                    {
                        result_v += (*it).value_list;
                    }
                }
                vector_long insert(result_v);
                result.push(new vector_long(result_v));
            }
            else
            {
                cout << "*******Error occur in Relational Operator*******" << endl;
            }

            st = "";
        }
        else if(begin->type_of() == LOGICAL_OPERATOR)
        {
            Logical_operator* l_op = static_cast <Logical_operator*>(begin);
            string _l_op = l_op->get_Loperator();

            sy_Token* condition1 = result.pop();
            sy_Token* condition2 = result.pop();

            vector_long* _v1 = static_cast <vector_long*>(condition1);
            vector<long> v1 = _v1->get_vector_long();

            vector_long* _v2 = static_cast <vector_long*>(condition2);
            vector<long> v2 = _v2->get_vector_long();

            //sort and remove duplicate
            std::sort(v1.begin(),v1.end());
            std::sort(v2.begin(),v2.end());
            v1.erase( unique( v1.begin(), v1.end() ), v1.end() );
            v2.erase( unique( v2.begin(), v2.end() ), v2.end() );

            if(_l_op == "OR" || _l_op == "or" || _l_op == "Or")
            {

                vector<long> result_vector = Union(v1, v2);
                result.push(new vector_long(result_vector));
            }
            else if(_l_op == "AND" || _l_op == "And" || _l_op == "and")
            {
//                std::sort(v1.begin(),v1.end());
//                std::sort(v2.begin(),v2.end());
                vector<long> result_vector = intersection(v1, v2);
//                cout << "v1:" << v1 << endl << "v2: " << v2  << endl<< "result:" << result_vector << endl;
                result.push(new vector_long(result_vector));
            }
            else
            {
                cout << "*******Error occur in Logical Operator*******" << endl;
            }
        }
        else
        {
            result.push(begin);
        }


    }

    //get vector long from token
    sy_Token* re = result.pop();
    vector_long* _v = static_cast <vector_long*>(re);
    vector<long> v = _v->get_vector_long();
    return v;
}

vector<long> RPN::Union(const vector<long>& v1, const vector<long>& v2)
{
    //given two vector, find their union
    vector<long> result;
    long i = 0;
    long j = 0;
    while (i < v1.size() && j < v2.size())
    {
        if(v1[i] < v2[j])
        {
            result.push_back(v1[i]);
            i++;
        }
        else if (v1[i] > v2[j])
        {
            result.push_back(v2[j]);
            j++;
        }
        else
        {
            result.push_back(v2[j]);
            j++;
            i++;
        }
    }
    while(i < v1.size())
    {
        result.push_back(v1[i]);
        i++;
    }
    while(j < v2.size())
    {
        result.push_back(v2[j]);
        j++;
    }

//    cout << "union:" << result << endl;
    return result;
}
vector<long> RPN::intersection(const vector<long>& v1, const vector<long>& v2)
{
    //given two vector find their intersection
    vector<long> result;
    long i = 0;
    long j = 0;
    while (i < v1.size() && j < v2.size())
    {
//        cout << "v1:" << v1[i] << "v2:" << v2[j] << endl;
        if(v1[i] < v2[j])
        {
            i++;
        }
        else if (v1[i] > v2[j])
        {
            j++;
        }
        else
        {
//            cout << "the same: " << j << endl;
            result.push_back(v2[j]);
            j++;
            i++;
        }
    }
//    cout << "intersection:" << result << endl;
    return result;
}
void RPN::make_string(string& st1, const string& st2)
{
    int count = 0;
    string my_string = "";
    if(st2[0] != ' ')
    {
        count++;
    }
    for (int i = 0; i < st2.length();i++)
    {
        if(st2[i] == ' ' && count == 0)
        {
            count++;
        }
        else if(st2[i + 1] == '.' && st2[i] != ' ')
        {
            my_string += st2[i];
            my_string += ' ';

            count ++;
        }
        else if(/*st2[i] != ' ' && */count > 0)
        {
            my_string += st2[i];
            count++;
        }


    }
    st1 = my_string;

}

