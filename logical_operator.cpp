#include "logical_operator.h"

Logical_operator::Logical_operator(string l_operator):_loperator(l_operator)
{

    if(_loperator == "AND")
    {
        _pre = 2;
    }
    else if (_loperator == "OR")
    {
        _pre = 1;
    }
}
int Logical_operator::type_of()
{
    return LOGICAL_OPERATOR;
}
void Logical_operator::print()
{
    cout << _loperator << " ";
}
int Logical_operator::prec()
{
    return _pre;
}
string Logical_operator::get_Loperator()
{
    return _loperator;
}

