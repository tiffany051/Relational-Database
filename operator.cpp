#include "operator.h"

Operator::Operator()
{

}
Operator::Operator(string op):_operator(op),_pre(0)
{
    if(op == "=" || op == "<=" || op == ">=" || op == "<" || op == ">")
    {
        _pre = 3;
    }
}

int Operator::type_of()
{
    return OPERATOR;
}

void Operator::print()
{
    cout << _operator << " ";
}
int Operator::prec()
{
    return _pre;
}
string Operator::get_operator()
{
     return _operator;
}

