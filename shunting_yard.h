#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <iostream>
#include "../CS008_Final_Project/!include/queue.h"
#include "../CS008_Final_Project/!include/stack_class.h"
#include "operator.h"
#include "number.h"
#include "alpha.h"
#include "left_parenthesis.h"
#include "right_parenthesis.h"
#include "logical_operator.h"
using namespace std;


class shunting_yard
{
public:
    shunting_yard(Queue <sy_Token*> infix);
    Queue <sy_Token*> postfix();
    void print(Queue <sy_Token*> postfix);
    friend ostream& operator <<(ostream& outs, const shunting_yard& sy);

private:
    Queue <sy_Token*> _postfix;
    Queue <sy_Token*> _infix;

};

#endif // SHUNTING_YARD_H
