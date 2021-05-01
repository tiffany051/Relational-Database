#include "vector_long.h"

vector_long::vector_long(vector<long> v):vec(v)
{
    
}
int vector_long::vector_long::type_of()
{
    return VECTOR_LONG;
}

vector<long> vector_long::get_vector_long()
{
    return vec;
}
