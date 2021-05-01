#ifndef VECTOR_LONG_H
#define VECTOR_LONG_H
#include <cstring>
#include <iostream>
#include "sy_token.h"
#include "vector"

using namespace std;

class vector_long: public sy_Token
{
public:
    vector_long();
    vector_long(vector<long> v);
    int type_of();
    
    vector<long> get_vector_long();
    
private:
    vector<long> vec;
};

#endif // VECTOR_LONG_H
