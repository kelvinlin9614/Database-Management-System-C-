#ifndef TABLE_CLASS_STOKENIZER_H
#define TABLE_CLASS_STOKENIZER_H
#include <iostream>
#include <cstring>
#include "token.h"
using namespace std;
const int MAX_BUFFER = 100;
const int MAX_COLUMNS = 127;
const int MAX_ROWS = 100;

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens

    //extract one token (very similar to the way cin >> works)
    friend STokenizer& operator >> (STokenizer& s, Token& t)
    {
        // every time we extract one token, we need to declare a empty string and a start_state = 0
        // pass to the get_token function
        string token_temp;
        int start_state = 0;

        /**
         * get_token:
         *  get one token, put it into the token_temp. update the last state, and the last position.
         **/
        if(s.get_token(start_state, token_temp))
        {
            // pass the new token_temp and start_state to Token function(string str, int type)
            t = Token(token_temp, start_state);
        };
        return s;
    }

    //set a new string as the input string
    void set_string(char str[]);

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int &start_state, string& token);
    //---------------------------------
    char _buffer[MAX_BUFFER];       //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer()
{
    _pos = 0;
}

STokenizer::STokenizer(char str[])
{
    make_table(_table);
    set_string(str);
    _pos = 0;
}

//true: there are no more tokens
bool STokenizer::done()
{
    return _pos > strlen(_buffer);
}

//true: there are more tokens
bool STokenizer::more()
{
    return _pos <= strlen(_buffer);
}

//set a new string as the input string
void STokenizer::set_string(char str[])
{
    strcpy(_buffer, str);
}

//create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
        {
            _table[i][j] = -1;
        }
    }
    // number (0 - 9)
    for(int i = 48; i < 58; i++)
    {
        _table[0][i] = 1;
        _table[1][i] = 1;
        _table[2][i] = 3;
        _table[3][i] = 3;
    }

    // dot
    _table[1][46] = 2;

    // space
    _table[0][32] = 5;
    _table[5][32] = 5;

    // tab
    _table[0][9] = 5;
    _table[5][9] = 5;

    // VT
    _table[0][11] = 5;
    _table[5][11] = 5;

    // <, > , =
    _table[0][60] = 99;
    _table[0][62] = 99;
    _table[99][61] = 99;
    _table[99][0] = 1;

//    // 's
//    _table[4][39] = 6;
//    _table[6][83] = 7;
//    _table[6][115] = 7;

    // character a-z, A-Z
    for(int i = 65; i < 123; i++)
    {
        _table[0][i] = 4;
        _table[4][i] = 4;
    }

    // success state
    _table[0][0] = 0;
    _table[1][0] = 1;
    _table[2][0] = 0;
    _table[3][0] = 1;
    _table[4][0] = 1;
    _table[5][0] = 1;
    _table[6][0] = 0;
    _table[7][0] = 1;
}

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int &start_state, string& token)
{
    int success_pos = 0;        // hold the last success position

    /*
     * The _pos always update to the last position that we read. always check with the table. if it is not -1, then we
     * update the state number, save the success character to the token, update the last success position, increment
     * the _pos. If it is -1, First we will check the success_pos. If the success_pos = 0, it means that the token
     * that we get is only one character. Then we check the current state number, if it is = 1, then return true if we
     * token is not empty. If the state number = 0, then we need delete the last character of the token.
     */
    while(_buffer[_pos] != '\0')
    {
        if(_table[start_state][_buffer[_pos]] != -1)
        {
            start_state = _table[start_state][_buffer[_pos]];
            token += _buffer[_pos];
            success_pos = _pos;
            _pos++;
        }
        else
        {
            if(success_pos == 0)
            {
                token += _buffer[_pos];
                _pos++;
                return true;
            }
            if(_table[start_state][0] == 1)
            {
                return token.length() != 0;
            }
            else if(_table[start_state][0] == 0)
            {
                token.substr(0, success_pos);
                return token.length() != 0;
            }
        }
    }
    if(token.length()==0)
    {
        _pos++;
        return false;
    }
    return true;
}

#endif //TABLE_CLASS_STOKENIZER_H
