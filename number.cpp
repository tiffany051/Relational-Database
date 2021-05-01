#include "number.h"

Number::Number(int number):_num(number)
{
}

int Number::type_of()
{
    return NUMBER;
}
void Number::print()
{
    cout << _num << " ";
}
