#ifndef LOGICAL_OPERATOR_H
#define LOGICAL_OPERATOR_H
#include "sy_token.h"
#include <iostream>

using namespace std;


class Logical_operator: public sy_Token
{
public:
    Logical_operator();
    Logical_operator(string l_operator);
    int type_of();
    void print();
    int prec();
    string get_Loperator();

private:
    string _loperator;
    int _pre;

};


#endif // LOGICAL_OPERATOR_H
