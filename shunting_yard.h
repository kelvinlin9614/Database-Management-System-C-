#ifndef TABLE_CLASS_SHUNTING_YARD_H
#define TABLE_CLASS_SHUNTING_YARD_H
#include "Queue.h"
#include "vector.h"
#include "Stack.h"

class Shunting_yard
{
public:
    Shunting_yard();
    Queue<string> convert(Vector<string> _condition);
    Queue<string> translate(const Queue<string>& _need_translate);
    bool is_operator(string str);
    void make_map();
private:
    Queue <string> _result;
    Map<string,int> _precedence;
};

Shunting_yard::Shunting_yard()
{
    make_map();
}

Queue<string> Shunting_yard::convert(Vector<string> _condition)
{
    Queue<string> temp;
    for(int i = 0; i < _condition.size(); i++)
    {
        temp.push(_condition[i]);
    }
    return temp;
}

Queue<string> Shunting_yard::translate(const Queue<string> &_need_translate)
{
    Queue<string> copy_condition(_need_translate);
    Stack<string> stack;
    while(!copy_condition.empty())
    {
        string item = copy_condition.pop();
        // if the string is a operator
        if(is_operator(item))
        {
            // if stack is empty, then just push the item into the stack
            if(stack.empty())
                stack.push(item);
            // if stack is not empty
            else
            {
                // if the item < the top of the stack, then just push the
                // item into the stack
                if(item != "(" && _precedence[item] < _precedence[stack.top()])
                {
                    stack.push(item);
                }
                else
                {
                    while(!stack.empty() && item != "(" && _precedence[item] >= _precedence[stack.top()])
                    {
                        // check the precedence, if the item > the top of the stack
                        // then pop the top and push it into the _result
                        _result.push(stack.pop());
                        //item = copy_condition.front();
                    }
                    stack.push(item);
                }
                if(stack.top() == "(")
                {
                    stack.push(item);
                }
            }
        }
        else if(item == "(")
        {
            stack.push(item);
        }
        else if(item == ")")
        {
            // if the operator at the top of the stack is not a left parenthesis
            while(stack.top() != "(")
            {
                // pop the operator and push it into the _result queue
                _result.push(stack.pop());
            }
            // if there is a left parenthesis at the top of the stack
            if(stack.top() == "(")
            {
                // pop the operator and discard it
                stack.pop();
            }

        }
        // if the string is not a operator
        else
        {
            _result.push(item);
        }
    }
    // pop the item from the stack and push into the result queue
    while(!stack.empty())
    {
        _result.push(stack.pop());
    }
    return _result;
}

bool Shunting_yard::is_operator(string str)
{
    return str == ">" || str == "<" || str == "=" || str == ">=" ||
           str == "<=" || str == "and" || str == "or";
}

void Shunting_yard::make_map()
{
    // according to the test file from canvas, the precedence of "or" is
    // greater than "and"
    _precedence.insert("(", 4);
    _precedence.insert("and", 2);
    _precedence.insert("or", 3);
    _precedence.insert(">", 1);
    _precedence.insert("<", 1);
    _precedence.insert("=", 1);
    _precedence.insert(">=", 1);
    _precedence.insert("<=", 1);
}

#endif //TABLE_CLASS_SHUNTING_YARD_H
