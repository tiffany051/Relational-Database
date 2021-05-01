#ifndef RIGHT_PARENTHESIS_H
#define RIGHT_PARENTHESIS_H
#include <iostream>
#include "sy_token.h"

using namespace std;


class Right_Parenthesis:public sy_Token
{
public:
    Right_Parenthesis(string r_par);
    int type_of();
    void print();

private:
    string _r_par;
};

#endif // RIGHT_PARENTHESIS_H
