#ifndef SY_TOKEN_H
#define SY_TOKEN_H
#include <iostream>

using namespace std;


const int OPERATOR = 3;
const int NUMBER = 1;
const int LOGICAL_OPERATOR = 6;
const int VECTOR_LONG = 7;
const int ALPHA = 2;
const int R_PAR = 4;
const int L_PAR = 5;

class sy_Token
{
public:
    
    sy_Token();
    virtual int type_of();
    virtual void print();
};

#endif // SY_TOKEN_H
