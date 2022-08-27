#ifndef TABLE_CLASS_TABLE_H
#define TABLE_CLASS_TABLE_H

#include "record.h"
#include "map_bplus.h"
#include "mmap_bplus.h"
#include "parser.h"
#include "vector.h"

long SERIAL_NUM = 0;

class Table
{
public:
    // CTOR
    Table(){_how_many_record = 0;}
    // open an exist table
    Table(const string& name);
    // create a new table
    Table(const string& name, const Vector<string> fieldname);
    // insert info into the table
    void insert_into(Vector<string> field_list);
    // delete info
    void erase(Vector<long> record_num);
    // drop table
    void drop_table();
    // return a new table that contains the qualified info with all fields
    Table select_all(Vector<long> rpn = {});
    // return a vector of record number that contains the qualified info
    Vector<long> select_condition(Vector<string> command);
    // return a new table that contains the qualified info
    Table select(Vector<string> columns, Vector<long> rpn = {});
    //string get_temp_name(){return _temp_name;}
    //long get_how_many(){return _how_many_record;}
    friend ostream& operator<<(ostream& outs, const Table& print_me)
    {
        print_me.print_table();
        return outs;
    }
private:
    string _file_name;
    string _temp_name;
    long _how_many_record;
    // resize the vector
    void resize_vector(Vector<string>& v);
    void print_table() const;
    // contains the fieldnames
    Vector<string> _fieldnames;
    Map<string, long> _fieldmap;
    Vector<MMap<string, long> > _indices;
};

// open an existing table
Table::Table(const string &name)
{
    _how_many_record = 0;
    fstream f;
    _file_name = name + ".bin";
    open_fileRW(f, _file_name.c_str());
    // read all info: 1. field names 2. # of vecs 3. file name 4. reindex()
    Record r;
    r.read(f,0);
    Vector<string> field = r.get_record();
    _fieldnames = field;
    resize_vector(_fieldnames);
    for(int i = 0; i < _fieldnames.size(); i++)
    {
        _fieldmap.insert(_fieldnames[i], i);
        _indices.push_back(MMap<string, long>());
    }
    int recno = 1;
    r.read(f, recno);
    while(!f.eof())
    {
        Vector<string> temp = r.get_record();
        resize_vector(temp);
        for(int i = 0; i < temp.size(); i++)
            _indices[i].insert(temp[i], recno);
        recno++;
        r.read(f, recno);
    }
    f.close();
}

// create a new table
Table::Table(const string& name, const Vector<string> fieldnames)
{
    _how_many_record = 0;
    SERIAL_NUM += 4;
    _fieldnames = fieldnames;
    _file_name = name + ".bin";
    for(int i = 0; i < _fieldnames.size(); i++)
    {
        _fieldmap.insert(_fieldnames[i], i);
        _indices.push_back(MMap<string, long>());
    }
    fstream f;
    open_fileW(f, _file_name.c_str());
    Record rec(_fieldnames);
    rec.write(f);
    f.close();
}

void Table::resize_vector(Vector<string>& v)
{
    int k = 0;
    while(!v[k].empty())
        k++;
    v.set_size(k);
}

void Table::insert_into(Vector<string> field_list)
{
    fstream f;
    open_fileRW(f, _file_name.c_str());
    Record rec(field_list);
    // write the field_list into the file and get the record number
    long reco_num = rec.write(f);
    // insert the record into the indices
    // key is the field_name, value is the record number
    for(long i = 0; i < field_list.size(); i++)
        _indices[i].insert(field_list[i], reco_num);
    f.close();
}

//void Table::erase(Vector<long> recno)
//{
//    fstream f;
//    open_fileRW(f, _file_name.c_str());
//    for(long i = 0; i < recno.size(); i++)
//    {
//        Record r;
//        // get the start position of the record number
//        long pos= recno[i] * r.get_record_size();
//        // point to the start position
//        f.seekg(pos, ios_base::beg);
//        f.write(" * ", 3);
//    }
//}

void Table::drop_table()
{
    // directly remove the file
    remove(_file_name.c_str());
    // clear the MAP
    _fieldmap.clear();
    // clear the indices
    for(int i = 0; i < _indices.size(); i++)
    {
        _indices[i].clear();
    }
    _indices.set_size(0);
    _fieldnames.set_size(0);

}

// print out all the information
void Table::print_table() const
{
    Record r(_fieldnames);
    fstream f;
    open_fileRW(f, _file_name.c_str());
    int recno = 0;
    r.read(f, recno);
    cout << "Table name: " << _temp_name << ", records: "
         << _how_many_record <<  endl;
    while (!f.eof()){
        cout << recno << " " <<setw(16) << left << r << endl;
        recno++;
        r.read(f, recno);
    }
    f.close();
}

// return a vector that contains the record number
Vector<long> Table::select_condition(Vector<string> command)
{
    Vector<long> recno;
    Vector<long> no_record_num;     // return this vector if there is no record
    no_record_num.push_back(-1);
    // handle "="
    if(command[1] == "=")
    {
        if(_indices[_fieldmap[command[0]]].contains(command[2]))
            return _indices[_fieldmap[command[0]]][command[2]];
        else
            return no_record_num;
    }
    // handle ">"
    else if(command[1] == ">")
    {
        MMap<string, long>::Iterator end(_indices[_fieldmap[command[0]]].end());
        MMap<string, long>::Iterator walker(_indices[_fieldmap[command[0]]].
                upper_bound(command[2]));
        // if the given item is bigger than our maximun item in the record,
        // then return -1
        if(walker == end)
        {
            return no_record_num;
        }
        // normal condition
        else
        {
            while(walker != end)
            {
                for(int  i= 0; i < (*walker).value_list.size(); i++)
                {
                    recno.push_back((*walker).value_list[i]);
                }
                walker++;
            }
            return recno;
        }
    }
    // handle ">="
    else if(command[1] == ">=")
    {
        MMap<string, long>::Iterator walker(_indices[_fieldmap[command[0]]].
                lower_bound(command[2]));
        MMap<string, long>::Iterator end(_indices[_fieldmap[command[0]]].end());
        if(walker == end)
        {
            return no_record_num;
        }
        else
        {
            while(walker != end)
            {
                for(int  i= 0; i < (*walker).value_list.size(); i++)
                {
                    recno.push_back((*walker).value_list[i]);
                }
                walker++;
            }
            return recno;
        }
    }
    // handle "<"
    else if(command[1] == "<")
    {
        MMap<string, long>::Iterator end(_indices[_fieldmap[command[0]]].
                lower_bound(command[2]));
        MMap<string, long>::Iterator begin(_indices[_fieldmap[command[0]]].begin());
        if(begin == end)
        {
            return no_record_num;
        }
        else
        {
            while(begin != end)
            {
                for(int  i= 0; i < (*begin).value_list.size(); i++)
                {
                    recno.push_back((*begin).value_list[i]);
                }
                begin++;
            }
            return recno;
        }
    }
    // handle "<="
    else if(command[1] == "<=")
    {
        MMap<string, long>::Iterator end(_indices[_fieldmap[command[0]]].
                upper_bound(command[2]));
        MMap<string, long>::Iterator begin(_indices[_fieldmap[command[0]]].begin());
        if(begin == end)
        {
            return no_record_num;
        }
        else
        {
            while(begin != end)
            {
                for(int  i= 0; i < (*begin).value_list.size(); i++)
                {
                    recno.push_back((*begin).value_list[i]);
                }
                begin++;
            }
            return recno;
        }
    }
}

Table Table::select_all(Vector<long> rpn)
{
    string name = "_select_table_" + to_string(SERIAL_NUM);
    // create a new table
    Table temp(name, _fieldnames);
    Record r;
    fstream f;
    // open the original file to read
    open_fileRW(f, _file_name.c_str());
    // if there is at least 1 condition
    if(rpn.size() != 0)
    {
        Vector<long> recno = rpn;
        for(long i = 0; i < recno.size(); i++)
        {
            Vector<string> selection;
            r.read(f, recno[i]);
            for(int i = 0; i < _fieldnames.size(); i++)
            {
                selection.push_back(r.get_record()[_fieldmap[_fieldnames[i]]]);
            }
            temp.insert_into(selection);
        }
    }
        // if there is no condition
    else
    {
        long recno = 1;
        r.read(f, recno);
        while(!f.eof())
        {
            Vector<string> selection;
            for(int i = 0; i < _fieldnames.size(); i++)
            {
                selection.push_back(r.get_record()[_fieldmap[_fieldnames[i]]]);
            }
            temp.insert_into(selection);
            recno++;
            r.read(f, recno);
        }
    }
    return temp;
}
// return a new table that contains the qualified information
Table Table::select(Vector<string> columns, // field name
                    Vector<long> rpn)       // get from rpn
{
    _temp_name = "_select_table_" + to_string(SERIAL_NUM);
    if(columns[0] == "*")
    {
        columns = _fieldnames;
    }
    // create a new table
    Table temp(_temp_name, columns);
    temp._temp_name = _temp_name;
    Record r;
    fstream f;
    // open the original file to read
    open_fileRW(f, _file_name.c_str());
    // if there is at least 1 condition
    if(rpn.size() != 0)
    {
        Vector<long> recno = rpn;
        for(long i = 0; i < recno.size(); i++)
        {
            Vector<string> selection;
            r.read(f, recno[i]);
            for(int i = 0; i < columns.size(); i++)
            {
                selection.push_back(r.get_record()[_fieldmap[columns[i]]]);
            }
            temp._how_many_record++;
            temp.insert_into(selection);
        }
    }
    // if there is no condition
    else
    {
        long recno = 1;
        r.read(f, recno);
        while(!f.eof())
        {
            Vector<string> selection;
            for(int i = 0; i < columns.size(); i++)
            {
                selection.push_back(r.get_record()[_fieldmap[columns[i]]]);
            }
            temp._how_many_record++;
            temp.insert_into(selection);
            recno++;
            r.read(f, recno);
        }
    }
    return temp;
}

#endif //TABLE_CLASS_TABLE_H