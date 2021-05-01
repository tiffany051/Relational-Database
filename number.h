#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include "sy_token.h"

using namespace std;


class Number : public sy_Token
{
public:
    Number(int number);
    int type_of() override;
    void print() override;
    int get_num();

private:
    int _num;
};

#endif // NUMBER_H
