#ifndef ALPHA_H
#define ALPHA_H
#include "sy_token.h"


class Alpha: public sy_Token
{
public:
    Alpha(string st);
    int type_of();
    void print();
    string get_alpha();

private:
    string _alpha;
};

#endif // ALPHA_H
