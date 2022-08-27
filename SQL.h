#ifndef TABLE_CLASS_SQL_H
#define TABLE_CLASS_SQL_H
#include "table.h"
#include "parser.h"
#include "shunting_yard.h"
#include "rpn.h"

class SQL
{
public:
    SQL(string file_name);
    void run();

private:
    void output_make(MMap<string, string> ptree);
    void output_insert(MMap<string, string> ptree);
    void output_select(MMap<string, string> ptree);
    void output_delete(MMap<string, string> ptree);
    void output_drop(MMap<string, string> ptree);
    Map<string,Table> _tables;
    string _file_name;
};

SQL::SQL(string file_name)
{
    _file_name = file_name;
    string name;
    // fill up  the MAP _tables with the file name and the Table obj
    ifstream inFile("File_name.txt");
    if(inFile.is_open())
    {
        while(!inFile.eof())
        {
            getline(inFile, name);
            if(!name.empty())
            {
                Table t(name);
                _tables.insert(name, t);
            }
        }
    }
    inFile.close();
}

void SQL::run()
{
    long counter = 0;
    string command;
    ifstream inFile;
    inFile.open(_file_name);
    if(inFile.is_open())
    {
        while(getline(inFile, command))
        {
            if(command[0] == '/' || command[0] == ' ' || command[0] == '\n' ||
                !isalpha(command[0]))
            {
                cout << command << endl;
            }
            else
            {
                // convert string to c_string
                char command_ch[command.length()];
                int i = 0;
                for(; i < command.length(); i++)
                {
                    command_ch[i] = command[i];
                }
                command_ch[i] = '\0';

                Parser p(command_ch);
                // if the SQL statement is invalid
                if(p.fail())
                {
                    cout << "invalid SQL statement! " << endl;
                }

                // if the SQL statement is valid
                else
                {
                    MMap<string,string> ptree = p.parse_tree();
                    cout << "[" << counter++ << "] ";
                    cout << command << endl;
                    if(ptree["command"][0] == "make")
                    {
                        output_make(ptree);
                    }
                    else if(ptree["command"][0] == "insert")
                    {
                        output_insert(ptree);
                    }
                    else if(ptree["command"][0] == "select")
                    {
                        output_select(ptree);
                    }
                    else if(ptree["command"][0] == "delete")
                    {
                        output_delete(ptree);
                    }
                    else if(ptree["command"][0] == "drop")
                    {
                        output_drop(ptree);
                    }
                    cout << endl << endl << "SQL: DONE." << endl;
                }
            }

        }
        inFile.close();
    }
    else
    {
        cout << "file open failure!" << endl;
    }
}

void SQL::output_make(MMap<string, string> ptree)
{
    ptree["fields"].insert(0, "del");
    Table t(ptree["table"][0], ptree["fields"]);

    // write the file name into the File_name.txt
    ifstream inFile("File_name.txt");

    // check if it is the first time open the .txt
    if(!(inFile.is_open()))
    {
        inFile.close();
        ofstream outFile("File_name.txt");
        outFile << ptree["table"][0] << endl;
        outFile.close();
    }
    // if it is not the first time open the .txt
    else
    {
        string name;
        bool check_same = false;
        // check if the file name in the text file is the same with current name
        while(!inFile.eof())
        {
            getline(inFile, name);
            if(name == ptree["table"][0])
            {
                check_same = true;
                break;
            }
        }
        inFile.close();

        // if there is no same name, then append the file name into the .txt
        if(!check_same)
        {
            ofstream outFile("File_name.txt", ios::app);
            outFile << ptree["table"][0] << endl;
            outFile.close();
        }
    }
    // store the table name and table obj into the map
    _tables.insert(ptree["table"][0], t);

    cout << "command: " << ptree["command"] << " table: " << ptree["table"]
         << " cols: " << ptree["fields"] << endl;
    cout << "Table " << ptree["table"] << " created. cols: " << ptree["fields"]
         << endl;
}

void SQL::output_insert(MMap<string, string> ptree)
{
    ptree["fields"].insert(0, "   ");
    _tables[ptree["table"][0]].insert_into(ptree["fields"]);
    cout << "SQL::run: inserted." << endl;
}

void SQL::output_select(MMap<string, string> ptree)
{
    if(ptree["where"][0] == "yes")
    {
        Shunting_yard sy;
        Queue<string> shuntingYard;
        shuntingYard = sy.translate(sy.convert(ptree["condition"]));
        RPN rpn(shuntingYard);
        Vector<long> rpn_num = rpn.evaluate(_tables[ptree["table"][0]]);
        cout << _tables[ptree["table"][0]].select(ptree["fields"], rpn_num);
    }
    else
    {
       cout << _tables[ptree["table"][0]].select(ptree["fields"]);
    }
}

void SQL::output_delete(MMap<string, string> ptree)
{
//    if(ptree["where"][0] == "yes")
//    {
//        Shunting_yard sy;
//        Queue<string> shuntingYard;
//        shuntingYard = sy.translate(sy.convert(ptree["condition"]));
//        RPN rpn(shuntingYard);
//        Vector<long> rpn_num = rpn.evaluate(_tables[ptree["table"][0]]);
//        _tables[ptree["table"][0]].erase(rpn_num);
//        Table t = _tables[ptree["table"][0]].select(ptree["fields"]);
//        cout << t << endl;
//    }
}

void SQL::output_drop(MMap<string, string> ptree)
{
    _tables[ptree["table"][0]].drop_table();
    _tables.erase(ptree["table"][0]);
    ofstream outFile("File_name.txt");
    Map<string,Table>:: Iterator walker = _tables.begin();
    for(int i = 0; i < _tables.size(); i++)
    {
        outFile << (*(walker)).key << endl;
        walker++;
    }
    outFile.close();
    cout << "drop table " << ptree["table"][0] << " completed" << endl;
}


#endif //TABLE_CLASS_SQL_H
