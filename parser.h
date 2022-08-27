#ifndef TABLE_CLASS_PARSER_H
#define TABLE_CLASS_PARSER_H
#include "Queue.h"
#include "STokenizer.h"
#include "map_bplus.h"
#include "mmap_bplus.h"
#include <cstring>

const int SYMBOL = 20;

class Parser
{
public:
    Parser(char* s);
    void set_string(char* str);

    // Accessors & Mutators
    bool fail(){return _flag;}
    MMap<string,string> parse_tree(){return _ptree;}

private:
    void make_table(int _table[][MAX_COLUMNS]);
    void build_keyword_list();
    int get_column(string str);
    bool get_parse_tree();

    bool _flag;
    static int _table[MAX_ROWS][MAX_COLUMNS];

    Queue<string> _input_q;         // holds tokens
    char _buffer[MAX_BUFFER];       // input string
    Map<string,int> _keywords;      // key words map
    MMap<string,string> _ptree;      // parse tree map
    enum keys {ZERO, SELECT, FROM, STAR, COMMA, WHERE, AND, OR, MAKE, CREATE,
               TABLE, FIELDS, INSERT, INTO, VALUES, DELETE, DROP};

};
int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser(char *s)
{
    // copy s to internal buffer
    strcpy(_buffer, s);

    // initialize "make" adjacency table
    make_table(_table);

    // build keyword list
    build_keyword_list();

    // call set_string
    set_string(_buffer);
}

void Parser::make_table(int _table[][MAX_COLUMNS])
{
    for(int i=0;i<MAX_ROWS;i++)
    {
        for(int j=0;j<MAX_COLUMNS;j++)
        {
            _table[i][j]=-1;
        }
    }
    //success state, column 0.
    _table[0][0] = 0;
    _table[1][0] = 0;
    _table[2][0] = 0;
    _table[3][0] = 0;
    _table[4][0] = 1;
    _table[5][0] = 0;
    _table[6][0] = 0;
    _table[7][0] = 0;
    _table[9][0] = 0;
    _table[10][0] = 1;
    _table[12][0] = 0;
    _table[13][0] = 0;
    _table[14][0] = 0;
    _table[15][0] = 0;
    _table[16][0] = 0;
    _table[17][0] = 1;
    _table[18][0] = 0;
    _table[19][0] = 0;
    _table[20][0] = 0;
    _table[21][0] = 0;
    _table[22][0] = 1;
    _table[23][0] = 0;
    _table[24][0] = 0;
    _table[25][0] = 0;
    _table[26][0] = 0;
    _table[27][0] = 0;
    _table[28][0] = 0;
    _table[29][0] = 1;
    _table[30][0] = 0;
    _table[31][0] = 0;
    _table[32][0] = 1;

    //SELECT, col 1
    _table[0][1] = 1;

    //FROM, col 2
    _table[2][2] = 3;
    _table[23][2] = 24;

    //STAR, col 3
    _table[1][3] = 2;

    //COMMA, col 4
    _table[2][4] = 12;
    _table[17][4] = 16;
    _table[22][4] = 21;

    // WHERE, col 5
    _table[4][5] = 5;
    _table[25][5] = 26;

    // AND, col 6
    _table[10][6] = 5;
    _table[29][6] = 26;

    // OR, col 7
    _table[10][7] = 5;
    _table[29][7] = 26;

    // Make, Create, col 8, 9
    _table[0][8] = 13;
    _table[0][9] = 13;

    // Table, col 10
    _table[13][10] = 14;
    _table[30][10] = 31;

    // Fields, col 11
    _table[15][11] = 16;

    // Insert, col 12
    _table[0][12] = 18;

    // Into, col 13
    _table[18][13] = 19;

    // Values, col 14
    _table[20][14] = 21;

    // delete, col 15
    _table[0][15] = 23;

    // drop, col 16
    _table[0][16] = 30;


    //SYMBOL, col 20
    _table[1][20] = 2;
    _table[3][20] = 4;
    _table[5][20] = 6;
    _table[6][20] = 7;
    _table[7][20] = 10;
    _table[10][20] = 10;
    _table[12][20] = 2;
    _table[14][20] = 15;
    _table[16][20] = 17;
    _table[19][20] = 20;
    _table[21][20] = 22;
    _table[24][20] = 25;
    _table[26][20] = 27;
    _table[27][20] = 28;
    _table[28][20] = 29;
    _table[29][20] = 29;
    _table[31][20] = 32;
}

void Parser::set_string(char* str)
{
    // tokenize input buffer into input_q
    STokenizer stk(str);
    Token t;
    stk >> t;
    while(stk.more())
    {
        if(t.token_str() == "\"")
        {
            stk >> t;
            string temp;
            while(t.token_str() != "\"")
            {
                temp += t.token_str();
                t = Token();
                stk >> t;
            }
            _input_q.push(temp);
        }
        else if(t.type_string() != "SPACE")
            _input_q.push(t.token_str());
        t = Token();
        stk >> t;
    }

    // call get_parse_tree & sets/resets fail flag
    _flag = !get_parse_tree();
}

void Parser::build_keyword_list()
{
    _keywords.insert("select", SELECT);
    _keywords.insert("from", FROM);
    _keywords.insert("*", STAR);
    _keywords.insert(",", COMMA);
    _keywords.insert("where", WHERE);
    _keywords.insert("and", AND);
    _keywords.insert("or", OR);
    _keywords.insert("make", MAKE);
    _keywords.insert("create", CREATE);
    _keywords.insert("table", TABLE);
    _keywords.insert("fields", FIELDS);
    _keywords.insert("insert", INSERT);
    _keywords.insert("into", INTO);
    _keywords.insert("values", VALUES);
    _keywords.insert("delete", DELETE);
    _keywords.insert("drop", DROP);
}

int Parser::get_column(string str)
{
    if(_keywords.contains(str))
        return _keywords[str];
    else
        return SYMBOL;
}

bool Parser::get_parse_tree()
{
    int state = 0;
    string token;
    do
    {
        token = _input_q.pop();
        state = _table[state][get_column(token)];
        switch (state)
        {
            // select * from student where last=kevin
            case 1:
                _ptree["command"] += token;
                break;
            case 2:
                _ptree["fields"] += token;
                break;
            case 3:
                break;
            case 4:
                _ptree["table"] += token;
                break;
            case 5:
                if(_ptree["where"].front() == "")
                    _ptree["where"] += "yes";
                else
                    _ptree["condition"] += token;
                break;
            case 6:
                _ptree["condition"] += token;
                break;
            case 7:
                _ptree["condition"] += token;
                break;
            case 10:
                _ptree["condition"] += token;
                break;
            // make table employee fields last, first, age
            case 13:
                _ptree["command"] += token;
                break;
            case 15:
                _ptree["table"] += token;
                break;
            case 17:
                _ptree["fields"] += token;
                break;
            // insert into employee values blow, joe, cs
            case 18:
                _ptree["command"] += token;
                break;
            case 20:
                _ptree["table"] += token;
                break;
            case 22:
                _ptree["fields"] += token;
                break;
            case 23:
                _ptree["command"] += token;
                break;
            case 25:
                _ptree["table"] += token;
                break;
            case 26:
                if(_ptree["where"].front() == "")
                    _ptree["where"] += "yes";
                else
                    _ptree["condition"] += token;
            case 27:
                _ptree["condition"] += token;
                break;
            case 28:
                _ptree["condition"] += token;
                break;
            case 29:
                _ptree["condition"] += token;
                break;
            case 30:
                _ptree["command"] += token;
                break;
            case 32:
                _ptree["table"] += token;
                break;
            default:
                break;
        }
    }
    while(!_input_q.empty() && _table[state][get_column(_input_q.front())] != -1);
    if(_table[state][0] == 1)
        return true;
    else
    {
        _ptree.clear();
        return false;
    }
}

#endif //TABLE_CLASS_PARSER_H
