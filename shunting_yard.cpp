#include "shunting_yard.h"

shunting_yard::shunting_yard(Queue <sy_Token*> infix):_infix(infix)
{


}

Queue <sy_Token*> shunting_yard::postfix()
{
    Stack_class<sy_Token*> _operator;//the stack that store operator
    Stack_class<sy_Token*> logical_operator;
    Queue <sy_Token*> _postfix;


    int prec = 0;

    while(_infix.empty() == false)
    {
        sy_Token* i = _infix.front()->_item;
        _infix.pop();
        if(i->type_of() == ALPHA)
        {//if is a Aplha push into the operator stack
            _postfix.push(i);
        }
        else if(i->type_of() == OPERATOR || i->type_of() == LOGICAL_OPERATOR)
        {//when its an operator
         //1. if the operator stack is empty, push the operator
         // 2. if the operator stack is not empty
               //1. get the precedence of current operator
               //2. compare with the operator on top of the stack
               //3. if the current operator has larger precedence, push on that stack
               //4. else if the current operator has smaller or equal precedence of the top stack
                      //pop the stack until it reach the less precedence
                      //and push those operators in the stack to queue
            sy_Token* _op_ptr;
            if(_operator.empty())
            {
                _operator.push(i);
            }
            else
            {//when is not empty stack
                _op_ptr = _operator.top();
                int stack_pre =  0;

                if(i->type_of() == OPERATOR)
                {
                    prec = static_cast<Operator*>(i)->prec();
                }
                else if(i->type_of() == LOGICAL_OPERATOR)
                {
                    prec = static_cast<Logical_operator*>(i)->prec();
                }

                //get the first item in the stack's prec
                if(_op_ptr->type_of() == OPERATOR)
                {
                    stack_pre = static_cast<Operator*>(_op_ptr)->prec();
                }
                else if (_op_ptr->type_of() == LOGICAL_OPERATOR)
                {

                    stack_pre = static_cast<Logical_operator*>(_op_ptr)->prec();
                }


                if(prec > stack_pre || _op_ptr->type_of() == L_PAR)
                {
                    _operator.push(i);
                }
                else
                {//when the current precedence is smaller of euqal to the top of stack
                    while (prec <= stack_pre && !_operator.empty())
                    {
                        _postfix.push(_operator.pop());
                        if(!_operator.empty())
                        {
                            _op_ptr = _operator.top();
                            if(_op_ptr->type_of() == OPERATOR)
                            {
                                stack_pre = static_cast<Operator*>(_op_ptr)->prec();
                            }
                            else
                            {
                                stack_pre = static_cast<Logical_operator*>(_op_ptr)->prec();
                            }
                        }

                    }
                    _operator.push(i);
                }
            }
        }

        else if(i->type_of() == L_PAR)
        {
            cout <<  "left parentathesis" << endl;
            _operator.push(i);
        }
        else if(i->type_of() == R_PAR)
        {
            sy_Token* _op_ptr = _operator.top();
            while(_op_ptr->type_of() != L_PAR)
            {//pop till you see the left parenthesis
                _postfix.push(_operator.pop());
                _op_ptr = _operator.top();
            }
            _postfix.push(_operator.pop());
        }
    }
    while(!_operator.empty())
    {//when the infix is empty but the operator stack is not
        _postfix.push(_operator.top());
        _operator.pop();
    }
    return _postfix;
}

void shunting_yard::print(Queue <sy_Token*> postfix)
{
    for (Queue <sy_Token*>::Iterator i = postfix.front(); i != nullptr; i++)
    {
         (*i)->print();
    }
}
