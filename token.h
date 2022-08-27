#ifndef TABLE_CLASS_TOKEN_H
#define TABLE_CLASS_TOKEN_H
#include<iostream>
using namespace std;

class Token
{
public:
    // CTOR
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t)
    {
        outs << "|" << t.token_str() << "|";
        return outs;
    }
    // return the type number
    int type();
    // return the type
    string type_string();
    // return the token
    string token_str() const;
private:
    string _token;
    int _type;
};

// CTOR
Token::Token()
{
    _token = "";
    _type = 0;
}

Token::Token(string str, int type)
{
    _token = str;
    _type = type;
}

int Token::type()
{
    return _type;
}

string Token::type_string()
{
    if(type() == 4 || type() == 7)
    {
        return "ALPHA";
    }
    else if(type() == 5)
    {
        return "SPACE";
    }
    else if(type() == 1 || type() == 3)
    {
        return "NUMBER";
    }
    else if(type() == 99)
    {
        return "OPERATOR";
    }
    else
    {
        return "UNKNOWN";
    }
}

string Token::token_str() const
{
    return _token;
}


#endif //TABLE_CLASS_TOKEN_H
