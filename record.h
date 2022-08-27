#ifndef TABLE_CLASS_RECORD_H
#define TABLE_CLASS_RECORD_H

#include <iostream>
#include <fstream>
#include "vector.h"
#include <cstring>
using namespace std;

bool file_exists(const char filename[]);
void open_fileRW(fstream& f, const char filename[]) throw(char*);
void open_fileW(fstream& f, const char filename[]);

typedef Vector<string> vectorstr;

class Record{
public:
    Record(){
        for (int i= 0; i<MAX_ROWS; i++)
            record[i][0] = NULL;
        recno = -1;
        _num_of_fields = 0;
    }
    Record(const vectorstr& v){
        for (int i= 0; i<MAX_ROWS; i++)
            record[i][0] = NULL;
        for (int i= 0; i<v.size(); i++){
            strcpy(record[i], v[i].c_str());
        }
        _num_of_fields = v.size();
    }
    vectorstr get_record(){
        vectorstr v;
        for (int i = 0; i<MAX_ROWS; i++){
            v.push_back(string(record[i]));
        }
        return v;
    }

    long get_record_size()
    {
        return sizeof(record);
    }

    long write(fstream& outs);
    long read(fstream& ins, long recno);


    friend ostream& operator<<(ostream& outs,
                               const Record& r);
private:
    static const int MAX_ROWS = 20;
    static const int MAX_COLS = 50;
    int recno;
    int _num_of_fields;
    char record[MAX_ROWS][MAX_COLS];
};
long Record::write(fstream &outs){
    //write to the end of the file.
    outs.seekg(0, outs.end);
    long pos = outs.tellp();
    //outs.write(&record[0], sizeof(record));
    outs.write(&record[0][0], sizeof(record));
    return pos/sizeof(record);
}
long Record::read(fstream &ins, long recno){
    long pos= recno * sizeof(record);
    ins.seekg(pos, ios_base::beg);
    ins.read(&record[0][0], sizeof(record));
    return ins.gcount();
}

ostream& operator<<(ostream& outs,
                    const Record& r){
    for (int i= 0; i<r._num_of_fields; i++){
        outs<< setw(16) << left << r.record[i];
    }
    return outs;
}

//-------------------------------------------------
bool file_exists(const char filename[]){
    const bool debug = false;
    fstream ff;
    ff.open (filename,
             std::fstream::in | std::fstream::binary );
    if (ff.fail()){
        if (debug) cout<<"file_exists(): File does NOT exist: "<<filename<<endl;
        return false;
    }
    if (debug) cout<<"file_exists(): File DOES exist: "<<filename<<endl;
    ff.close();
    return true;
}

void open_fileRW(fstream& f, const char filename[]) throw(char*){
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)){
        f.open(filename, std::fstream::out|std::fstream::binary);
        if (f.fail()){
            cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
            throw("file RW failed  ");
        }
        else{
            if (debug) cout<<"open_fileRW: file created successfully: "
                           <<filename<<endl;
        }
    }
    else{
        f.open (filename,
                std::fstream::in | std::fstream::out| std::fstream::binary );
        if (f.fail()){
            cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
            throw("file failed to open.");
        }
    }

}
void open_fileW(fstream& f, const char filename[])
{
    f.open (filename,
            std::fstream::out| std::fstream::binary );
    if (f.fail()){
        cout<<"file open failed: "<<filename<<endl;
        throw("file failed to open.");
    }
}

//template<typename T>
//ostream& operator <<(ostream& outs, const Vector<T>& v){
//    for (int i = 0; i<v.size(); i++){
//        outs<<v[i]<<" ";
//    }
//    return outs;
//}

#endif //TABLE_CLASS_RECORD_H
