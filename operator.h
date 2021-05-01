#ifndef OPERATOR_H
#define OPERATOR_H
#include <cstring>
#include <iostream>
#include "sy_token.h"

using namespace std;


class Operator: public sy_Token
{
public:
    Operator();
    Operator(string op);
    int type_of();
    void print();
    int prec();
    string get_operator();


private:
    int _op;
    string _operator;
    int _pre;
};

#endif // OPERATOR_H
