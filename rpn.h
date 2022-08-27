#ifndef TABLE_CLASS_RPN_H
#define TABLE_CLASS_RPN_H

#include "shunting_yard.h"
#include "table.h"

class RPN
{
public:
    RPN (Queue<string> q);
    Vector<long> evaluate(Table t);

private:
    bool is_operator(string str);
    Vector<long> union_vector(Vector<long> first, Vector<long> second);
    Vector<long> intersection_vector(Vector<long> first, Vector<long> second);
    Queue<string> postfix;

};

RPN::RPN(Queue<string> q)
{
    postfix = q;
}

Vector<long> RPN::evaluate(Table t)
{
    Stack<string> non_operator;
    Stack<Vector<long> > final_result;

    // copy the postfix
    Queue<string> shunting_yard = postfix;

    while(!shunting_yard.empty())
    {
        string temp = shunting_yard.pop();
        if(!is_operator(temp))
        {
            non_operator.push(temp);
        }
        else
        {
            // if the string is "and" or "or"
            if(temp == "and" or temp == "or")
            {
                // pop two Vector from the final_result stack
                // and do intersection or union
                if(temp == "and")
                {
                    Vector<long> recon_1 = final_result.pop();
                    Vector<long> recon_2 = final_result.pop();
                    final_result.push(intersection_vector(recon_1, recon_2));
                }
                else
                {
                    Vector<long> recon_1 = final_result.pop();
                    Vector<long> recon_2 = final_result.pop();
                    final_result.push(union_vector(recon_1, recon_2));
                }
            }
            // if the string is "=", ">", "<", ">=", "<="
            else
            {
                Vector<string> temp_vector;
                string temp1 = non_operator.pop();
                string temp2 = non_operator.pop();
                temp_vector.push_back(temp2);
                temp_vector.push_back(temp);
                temp_vector.push_back(temp1);
                // push the Vector that contains the recno into the final stack
                final_result.push(t.select_condition(temp_vector));
            }
        }
    }
    Vector<long> output = final_result.pop();
    if(output.size() == 1 && output.index_of(-1) != -1)
    {
        // do nothing
    }
    else if(output.size() > 1 && output.index_of(-1) != -1)
    {
        output.erase(output.index_of(-1));
    }
    return output;
}

bool RPN::is_operator(string str)
{
    return str == ">" || str == "<" || str == "=" || str == ">=" ||
           str == "<=" || str == "and" || str == "or";
}

// or
Vector<long> RPN::union_vector(Vector<long> first, Vector<long> second)
{
    // push the two vectors' item into a new vector
    Vector<long> combined;
    for(int i = 0; i < first.size(); i++)
    {
        combined.push_back(first[i]);
    }
    for(int i = 0; i < second.size(); i++)
    {
        combined.push_back(second[i]);
    }
    // find and remove duplicate
    for(int i = 0; i < combined.size(); i++)
    {
        for(int j = i + 1; j < combined.size(); j++)
        {
            if(combined[i] == combined[j])
            {
                combined.erase(j);
            }
        }
    }
    return combined;
}

// and
Vector<long> RPN::intersection_vector(Vector<long> first, Vector<long> second)
{
    // grab each element in the first vector and compare the each element in the second
    // if find duplicate, then push the item into a new vector
    Vector<long> combined;
    for(int i = 0; i < first.size(); i++)
    {
        for(int j = 0; j < second.size(); j++)
        {
            if(first[i] == second[j])
            {
                combined.push_back(first[i]);
            }
        }
    }
    if(combined.empty())
    {
        combined.push_back(-1);
    }
    return combined;
}

#endif //TABLE_CLASS_RPN_H
