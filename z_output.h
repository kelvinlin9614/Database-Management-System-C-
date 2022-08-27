#ifndef TABLE_CLASS_Z_OUTPUT_H
#define TABLE_CLASS_Z_OUTPUT_H

/*
***** ALL RESULTS ARE VERIFIED ******
YOUTUBE LINK: https://youtu.be/Jo5ENPwrTC0
//****************************************************************************
//              CREATE TABLES AND INSERT RECORDS
//****************************************************************************


[0] make table employee fields  last,           first,                  dep,            salary,         year
command: make table: employee cols: del last first dep salary year
Table employee created. cols: del last first dep salary year


SQL: DONE.
[1] insert into employee values Blow,           Joe,                    CS,                     100000,         2018
SQL::run: inserted.


SQL: DONE.
[2] insert into employee values Blow,           JoAnn,                  Physics,        200000,         2016
SQL::run: inserted.


SQL: DONE.
[3] insert into employee values Johnson,        Jack,                   HR,             150000,         2014
SQL::run: inserted.


SQL: DONE.
[4] insert into employee values Johnson,        "Jimmy",                Chemistry,      140000,         2018
SQL::run: inserted.


SQL: DONE.
[5] insert into employee values Yao,            Jimmy,                  Math,           145000,         2014
SQL::run: inserted.


SQL: DONE.
[6] insert into employee values "Yao",          Flo,                    CS,                     147000,         2012
SQL::run: inserted.


SQL: DONE.
[7] insert into employee values Yang,           Bo,                     CS,                     160000,         2013
SQL::run: inserted.


SQL: DONE.
[8] insert into employee values Jackson,        "Flo",                  Math,           165000,         2017
SQL::run: inserted.


SQL: DONE.
[9] insert into employee values Jackson,        Bo,                             Chemistry,      130000,         2011
SQL::run: inserted.


SQL: DONE.
[10] insert into employee values "Jackson",     Billy,                  Math,           170000,         2017
SQL::run: inserted.


SQL: DONE.
[11] insert into employee values Johnson,       "Mary Ann",     Math,           165000,         2014
SQL::run: inserted.


SQL: DONE.
[12] insert into employee values Johnson,       "Billy Bob",    Physics,        142000,         2014
SQL::run: inserted.


SQL: DONE.
[13] insert into employee values Johnson,       Billy,                  "Phys Ed",      102000,         2014
SQL::run: inserted.


SQL: DONE.
[14] insert into employee values "Van Gogh",    Vincent,                Art,            240000,         2015
SQL::run: inserted.


SQL: DONE.
[15] insert into employee values "Van Gogh",    Vincent,                CS,                     245000,         2015
SQL::run: inserted.


SQL: DONE.
[16] insert into employee values "Van Gogh",    "Jim Bob",              "Phys Ed",      230000,         2010
SQL::run: inserted.


SQL: DONE.
[17] select * from employee
Table name: _select_table_4, records: 16
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Blow            JoAnn           Physics         200000          2016
3                 Johnson         Jack            HR              150000          2014
4                 Johnson         Jimmy           Chemistry       140000          2018
5                 Yao             Jimmy           Math            145000          2014
6                 Yao             Flo             CS              147000          2012
7                 Yang            Bo              CS              160000          2013
8                 Jackson         Flo             Math            165000          2017
9                 Jackson         Bo              Chemistry       130000          2011
10                 Jackson         Billy           Math            170000          2017
11                 Johnson         Mary Ann        Math            165000          2014
12                 Johnson         Billy Bob       Physics         142000          2014
13                 Johnson         Billy           Phys Ed         102000          2014
14                 Van Gogh        Vincent         Art             240000          2015
15                 Van Gogh        Vincent         CS              245000          2015
16                 Van Gogh        Jim Bob         Phys Ed         230000          2010


SQL: DONE.

[18] make table student fields fname, lname, major, age, company
command: make table: student cols: del fname lname major age company
Table student created. cols: del fname lname major age company


SQL: DONE.
[19] insert into student values Flo,                    Yao,            CS,                             20,     Google
SQL::run: inserted.


SQL: DONE.
[20] insert into student values Bo,                             Yang,           CS,                             28,
                Microsoft
SQL::run: inserted.


SQL: DONE.
[21] insert into student values "Sammuel L.",   Jackson,        CS,                             40,             Uber
SQL::run: inserted.


SQL: DONE.
[22] insert into student values "Flo",                  "Jackson",      Math,                           21,
        Google
SQL::run: inserted.


SQL: DONE.
[23] insert into student values "Greg",                         "Pearson",      Physics,                        20,
                Amazon
SQL::run: inserted.


SQL: DONE.
[24] insert into student values "Jim Bob",              Smith,          Math,                           23,
        Verizon
SQL::run: inserted.


SQL: DONE.
[25] insert into student values Calvin,                         Woo,            Physics,                        22,
                Uber
SQL::run: inserted.


SQL: DONE.
[26] insert into student values "Anna Grace",   "Del Rio",      CS,                                     22,
        USAF
SQL::run: inserted.


SQL: DONE.
[27] insert into student values "Teresa Mae",   Gowers,         Chemistry,                      22,             Verizon
SQL::run: inserted.


SQL: DONE.
[28] insert into student values Alex,                   Smith,          "Gender Studies",       53,             Amazon
SQL::run: inserted.


SQL: DONE.
[29] select * from student
Table name: _select_table_12, records: 10
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Bo              Yang            CS              28              Microsoft
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Flo             Jackson         Math            21              Google
5                 Greg            Pearson         Physics         20              Amazon
6                 Jim Bob         Smith           Math            23              Verizon
7                 Calvin          Woo             Physics         22              Uber
8                 Anna Grace      Del Rio         CS              22              USAF
9                 Teresa Mae      Gowers          Chemistry       22              Verizon
10                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.


//****************************************************************************
//              SIMPLE SELECT:
//****************************************************************************

[30] select * from student
Table name: _select_table_16, records: 10
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Bo              Yang            CS              28              Microsoft
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Flo             Jackson         Math            21              Google
5                 Greg            Pearson         Physics         20              Amazon
6                 Jim Bob         Smith           Math            23              Verizon
7                 Calvin          Woo             Physics         22              Uber
8                 Anna Grace      Del Rio         CS              22              USAF
9                 Teresa Mae      Gowers          Chemistry       22              Verizon
10                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.

//------- simple strings -------------------
[31] select * from student where lname = Jackson
Table name: _select_table_20, records: 2
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Flo             Jackson         Math            21              Google


SQL: DONE.
[32] select * from student where major = CS
Table name: _select_table_24, records: 4
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Bo              Yang            CS              28              Microsoft
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Anna Grace      Del Rio         CS              22              USAF


SQL: DONE.
[33] select * from student where company = Uber
Table name: _select_table_28, records: 2
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Calvin          Woo             Physics         22              Uber


SQL: DONE.

//----- quoted strings ---------------------
[34] select * from student where lname = "Del Rio"
Table name: _select_table_32, records: 1
0 del             fname           lname           major           age             company
1                 Anna Grace      Del Rio         CS              22              USAF


SQL: DONE.
[35] select * from student where fname = "Jim Bob"
Table name: _select_table_36, records: 1
0 del             fname           lname           major           age             company
1                 Jim Bob         Smith           Math            23              Verizon


SQL: DONE.
[36] select * from student where fname = "Anna Grace"
Table name: _select_table_40, records: 1
0 del             fname           lname           major           age             company
1                 Anna Grace      Del Rio         CS              22              USAF


SQL: DONE.
[37] select * from student where fname = "Teresa Mae"
Table name: _select_table_44, records: 1
0 del             fname           lname           major           age             company
1                 Teresa Mae      Gowers          Chemistry       22              Verizon


SQL: DONE.

//-------- non-existing string ------------------
[38] select * from student where lname = "Does Not Exist"
Table name: _select_table_48, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.

//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[39] select * from student where lname > Yang
Table name: _select_table_52, records: 1
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google


SQL: DONE.
[40] select * from student where major > Math
Table name: _select_table_56, records: 2
0 del             fname           lname           major           age             company
1                 Greg            Pearson         Physics         20              Amazon
2                 Calvin          Woo             Physics         22              Uber


SQL: DONE.
[41] select * from student where fname > "Sammuel L."
Table name: _select_table_60, records: 1
0 del             fname           lname           major           age             company
1                 Teresa Mae      Gowers          Chemistry       22              Verizon


SQL: DONE.
[42] select * from employee where salary > 200000
Table name: _select_table_64, records: 3
0 del             last            first           dep             salary          year
1                 Van Gogh        Jim Bob         Phys Ed         230000          2010
2                 Van Gogh        Vincent         Art             240000          2015
3                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.
[43] select * from employee where dep > Chemistry
Table name: _select_table_68, records: 9
0 del             last            first           dep             salary          year
1                 Johnson         Jack            HR              150000          2014
2                 Yao             Jimmy           Math            145000          2014
3                 Jackson         Flo             Math            165000          2017
4                 Jackson         Billy           Math            170000          2017
5                 Johnson         Mary Ann        Math            165000          2014
6                 Johnson         Billy           Phys Ed         102000          2014
7                 Van Gogh        Jim Bob         Phys Ed         230000          2010
8                 Blow            JoAnn           Physics         200000          2016
9                 Johnson         Billy Bob       Physics         142000          2014


SQL: DONE.
[44] select * from employee where last > Jackson
Table name: _select_table_72, records: 11
0 del             last            first           dep             salary          year
1                 Johnson         Jack            HR              150000          2014
2                 Johnson         Jimmy           Chemistry       140000          2018
3                 Johnson         Mary Ann        Math            165000          2014
4                 Johnson         Billy Bob       Physics         142000          2014
5                 Johnson         Billy           Phys Ed         102000          2014
6                 Van Gogh        Vincent         Art             240000          2015
7                 Van Gogh        Vincent         CS              245000          2015
8                 Van Gogh        Jim Bob         Phys Ed         230000          2010
9                 Yang            Bo              CS              160000          2013
10                 Yao             Jimmy           Math            145000          2014
11                 Yao             Flo             CS              147000          2012


SQL: DONE.
[45] select * from employee where first > "Billy Bob"
Table name: _select_table_76, records: 13
0 del             last            first           dep             salary          year
1                 Yang            Bo              CS              160000          2013
2                 Jackson         Bo              Chemistry       130000          2011
3                 Yao             Flo             CS              147000          2012
4                 Jackson         Flo             Math            165000          2017
5                 Johnson         Jack            HR              150000          2014
6                 Van Gogh        Jim Bob         Phys Ed         230000          2010
7                 Johnson         Jimmy           Chemistry       140000          2018
8                 Yao             Jimmy           Math            145000          2014
9                 Blow            JoAnn           Physics         200000          2016
10                 Blow            Joe             CS              100000          2018
11                 Johnson         Mary Ann        Math            165000          2014
12                 Van Gogh        Vincent         Art             240000          2015
13                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[46] select * from student where age > 50
Table name: _select_table_80, records: 1
0 del             fname           lname           major           age             company
1                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[47] select * from student where age > 35
Table name: _select_table_84, records: 2
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[48] select * from student where fname > T
Table name: _select_table_88, records: 1
0 del             fname           lname           major           age             company
1                 Teresa Mae      Gowers          Chemistry       22              Verizon


SQL: DONE.
[49] select * from employee where salary > 130000
Table name: _select_table_92, records: 13
0 del             last            first           dep             salary          year
1                 Johnson         Jimmy           Chemistry       140000          2018
2                 Johnson         Billy Bob       Physics         142000          2014
3                 Yao             Jimmy           Math            145000          2014
4                 Yao             Flo             CS              147000          2012
5                 Johnson         Jack            HR              150000          2014
6                 Yang            Bo              CS              160000          2013
7                 Jackson         Flo             Math            165000          2017
8                 Johnson         Mary Ann        Math            165000          2014
9                 Jackson         Billy           Math            170000          2017
10                 Blow            JoAnn           Physics         200000          2016
11                 Van Gogh        Jim Bob         Phys Ed         230000          2010
12                 Van Gogh        Vincent         Art             240000          2015
13                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.
[50] select * from employee where  year > 2009
Table name: _select_table_96, records: 16
0 del             last            first           dep             salary          year
1                 Van Gogh        Jim Bob         Phys Ed         230000          2010
2                 Jackson         Bo              Chemistry       130000          2011
3                 Yao             Flo             CS              147000          2012
4                 Yang            Bo              CS              160000          2013
5                 Johnson         Jack            HR              150000          2014
6                 Yao             Jimmy           Math            145000          2014
7                 Johnson         Mary Ann        Math            165000          2014
8                 Johnson         Billy Bob       Physics         142000          2014
9                 Johnson         Billy           Phys Ed         102000          2014
10                 Van Gogh        Vincent         Art             240000          2015
11                 Van Gogh        Vincent         CS              245000          2015
12                 Blow            JoAnn           Physics         200000          2016
13                 Jackson         Flo             Math            165000          2017
14                 Jackson         Billy           Math            170000          2017
15                 Blow            Joe             CS              100000          2018
16                 Johnson         Jimmy           Chemistry       140000          2018


SQL: DONE.

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[51] select * from student where age  > 53
Table name: _select_table_100, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[52] select * from student where lname > Yao
Table name: _select_table_104, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[53] select * from student where fname > "Teresa Mae"
Table name: _select_table_108, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[54] select * from employee where last > "Van Gogh"
Table name: _select_table_112, records: 3
0 del             last            first           dep             salary          year
1                 Yang            Bo              CS              160000          2013
2                 Yao             Jimmy           Math            145000          2014
3                 Yao             Flo             CS              147000          2012


SQL: DONE.
[55] select * from employee where first > Vincent
Table name: _select_table_116, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[56] select * from employee where salary > 260000
Table name: _select_table_120, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.

//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[57] select * from student where age > 54
Table name: _select_table_124, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[58] select * from student where lname > Zoolander
Table name: _select_table_128, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[59] select * from employee where last > Zoolaner
Table name: _select_table_132, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[60] select * from employee where first > Xu
Table name: _select_table_136, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.

//.................
//:Greater Equal  :
//.................
[61] select * from student where lname >= Yang
Table name: _select_table_140, records: 2
0 del             fname           lname           major           age             company
1                 Bo              Yang            CS              28              Microsoft
2                 Flo             Yao             CS              20              Google


SQL: DONE.
[62] select * from student where fname >= "Sammuel L."
Table name: _select_table_144, records: 2
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Teresa Mae      Gowers          Chemistry       22              Verizon


SQL: DONE.
[63] select * from student where age >= 40
Table name: _select_table_148, records: 2
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[64] select * from employee where last >= Jack
Table name: _select_table_152, records: 14
0 del             last            first           dep             salary          year
1                 Jackson         Flo             Math            165000          2017
2                 Jackson         Bo              Chemistry       130000          2011
3                 Jackson         Billy           Math            170000          2017
4                 Johnson         Jack            HR              150000          2014
5                 Johnson         Jimmy           Chemistry       140000          2018
6                 Johnson         Mary Ann        Math            165000          2014
7                 Johnson         Billy Bob       Physics         142000          2014
8                 Johnson         Billy           Phys Ed         102000          2014
9                 Van Gogh        Vincent         Art             240000          2015
10                 Van Gogh        Vincent         CS              245000          2015
11                 Van Gogh        Jim Bob         Phys Ed         230000          2010
12                 Yang            Bo              CS              160000          2013
13                 Yao             Jimmy           Math            145000          2014
14                 Yao             Flo             CS              147000          2012


SQL: DONE.
[65] select * from employee where first >= Bill
Table name: _select_table_156, records: 16
0 del             last            first           dep             salary          year
1                 Jackson         Billy           Math            170000          2017
2                 Johnson         Billy           Phys Ed         102000          2014
3                 Johnson         Billy Bob       Physics         142000          2014
4                 Yang            Bo              CS              160000          2013
5                 Jackson         Bo              Chemistry       130000          2011
6                 Yao             Flo             CS              147000          2012
7                 Jackson         Flo             Math            165000          2017
8                 Johnson         Jack            HR              150000          2014
9                 Van Gogh        Jim Bob         Phys Ed         230000          2010
10                 Johnson         Jimmy           Chemistry       140000          2018
11                 Yao             Jimmy           Math            145000          2014
12                 Blow            JoAnn           Physics         200000          2016
13                 Blow            Joe             CS              100000          2018
14                 Johnson         Mary Ann        Math            165000          2014
15                 Van Gogh        Vincent         Art             240000          2015
16                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.
[66] select * from employee where salary >= 235000
Table name: _select_table_160, records: 2
0 del             last            first           dep             salary          year
1                 Van Gogh        Vincent         Art             240000          2015
2                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.


//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[67] select * from student where lname < Jackson
Table name: _select_table_164, records: 2
0 del             fname           lname           major           age             company
1                 Anna Grace      Del Rio         CS              22              USAF
2                 Teresa Mae      Gowers          Chemistry       22              Verizon


SQL: DONE.
[68] select * from student where major < Math
Table name: _select_table_168, records: 6
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Bo              Yang            CS              28              Microsoft
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Anna Grace      Del Rio         CS              22              USAF
5                 Teresa Mae      Gowers          Chemistry       22              Verizon
6                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[69] select * from student where fname < "Jim Bob"
Table name: _select_table_172, records: 7
0 del             fname           lname           major           age             company
1                 Alex            Smith           Gender Studies  53              Amazon
2                 Anna Grace      Del Rio         CS              22              USAF
3                 Bo              Yang            CS              28              Microsoft
4                 Calvin          Woo             Physics         22              Uber
5                 Flo             Yao             CS              20              Google
6                 Flo             Jackson         Math            21              Google
7                 Greg            Pearson         Physics         20              Amazon


SQL: DONE.
[70] select * from employee where salary < 200000
Table name: _select_table_176, records: 12
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Johnson         Billy           Phys Ed         102000          2014
3                 Jackson         Bo              Chemistry       130000          2011
4                 Johnson         Jimmy           Chemistry       140000          2018
5                 Johnson         Billy Bob       Physics         142000          2014
6                 Yao             Jimmy           Math            145000          2014
7                 Yao             Flo             CS              147000          2012
8                 Johnson         Jack            HR              150000          2014
9                 Yang            Bo              CS              160000          2013
10                 Jackson         Flo             Math            165000          2017
11                 Johnson         Mary Ann        Math            165000          2014
12                 Jackson         Billy           Math            170000          2017


SQL: DONE.
[71] select * from employee where dep < CS
Table name: _select_table_180, records: 1
0 del             last            first           dep             salary          year
1                 Van Gogh        Vincent         Art             240000          2015


SQL: DONE.
[72] select * from employee where last < Jackson
Table name: _select_table_184, records: 2
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Blow            JoAnn           Physics         200000          2016


SQL: DONE.
[73] select * from employee where first < "Billy Bob"
Table name: _select_table_188, records: 2
0 del             last            first           dep             salary          year
1                 Jackson         Billy           Math            170000          2017
2                 Johnson         Billy           Phys Ed         102000          2014


SQL: DONE.

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[74] select * from student where age  < 20
Table name: _select_table_192, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[75] select * from student where lname < "Del Rio"
Table name: _select_table_196, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[76] select * from student where fname < Alex
Table name: _select_table_200, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[77] select * from employee where last < Blow
Table name: _select_table_204, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[78] select * from employee where first < Billy
Table name: _select_table_208, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[79] select * from employee where salary < 100000
Table name: _select_table_212, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[80] select * from student where age  < 19
Table name: _select_table_216, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[81] select * from student where lname < Adams
Table name: _select_table_220, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[82] select * from student where fname < Adam
Table name: _select_table_224, records: 1
0 del             fname           lname           major           age             company
1


SQL: DONE.
[83] select * from employee where last < Alex
Table name: _select_table_228, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[84] select * from employee where first < Avory
Table name: _select_table_232, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.
[85] select * from employee where dep < Alchemy
Table name: _select_table_236, records: 1
0 del             last            first           dep             salary          year
1


SQL: DONE.


//.................
//:Less Equal     :
//.................

[86] select * from student where lname <= Smith
Table name: _select_table_240, records: 7
0 del             fname           lname           major           age             company
1                 Anna Grace      Del Rio         CS              22              USAF
2                 Teresa Mae      Gowers          Chemistry       22              Verizon
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Flo             Jackson         Math            21              Google
5                 Greg            Pearson         Physics         20              Amazon
6                 Jim Bob         Smith           Math            23              Verizon
7                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[87] select * from student where fname <= Greg
Table name: _select_table_244, records: 7
0 del             fname           lname           major           age             company
1                 Alex            Smith           Gender Studies  53              Amazon
2                 Anna Grace      Del Rio         CS              22              USAF
3                 Bo              Yang            CS              28              Microsoft
4                 Calvin          Woo             Physics         22              Uber
5                 Flo             Yao             CS              20              Google
6                 Flo             Jackson         Math            21              Google
7                 Greg            Pearson         Physics         20              Amazon


SQL: DONE.
[88] select * from student where age <= 40
Table name: _select_table_248, records: 9
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Greg            Pearson         Physics         20              Amazon
3                 Flo             Jackson         Math            21              Google
4                 Calvin          Woo             Physics         22              Uber
5                 Anna Grace      Del Rio         CS              22              USAF
6                 Teresa Mae      Gowers          Chemistry       22              Verizon
7                 Jim Bob         Smith           Math            23              Verizon
8                 Bo              Yang            CS              28              Microsoft
9                 Sammuel L.      Jackson         CS              40              Uber


SQL: DONE.

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[89] select * from employee where last <= Peach
Table name: _select_table_252, records: 10
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Blow            JoAnn           Physics         200000          2016
3                 Jackson         Flo             Math            165000          2017
4                 Jackson         Bo              Chemistry       130000          2011
5                 Jackson         Billy           Math            170000          2017
6                 Johnson         Jack            HR              150000          2014
7                 Johnson         Jimmy           Chemistry       140000          2018
8                 Johnson         Mary Ann        Math            165000          2014
9                 Johnson         Billy Bob       Physics         142000          2014
10                 Johnson         Billy           Phys Ed         102000          2014


SQL: DONE.
[90] select * from employee where first <= Gary
Table name: _select_table_256, records: 7
0 del             last            first           dep             salary          year
1                 Jackson         Billy           Math            170000          2017
2                 Johnson         Billy           Phys Ed         102000          2014
3                 Johnson         Billy Bob       Physics         142000          2014
4                 Yang            Bo              CS              160000          2013
5                 Jackson         Bo              Chemistry       130000          2011
6                 Yao             Flo             CS              147000          2012
7                 Jackson         Flo             Math            165000          2017


SQL: DONE.
[91] select * from employee where salary <= 23500
Table name: _select_table_260, records: 14
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Johnson         Billy           Phys Ed         102000          2014
3                 Jackson         Bo              Chemistry       130000          2011
4                 Johnson         Jimmy           Chemistry       140000          2018
5                 Johnson         Billy Bob       Physics         142000          2014
6                 Yao             Jimmy           Math            145000          2014
7                 Yao             Flo             CS              147000          2012
8                 Johnson         Jack            HR              150000          2014
9                 Yang            Bo              CS              160000          2013
10                 Jackson         Flo             Math            165000          2017
11                 Johnson         Mary Ann        Math            165000          2014
12                 Jackson         Billy           Math            170000          2017
13                 Blow            JoAnn           Physics         200000          2016
14                 Van Gogh        Jim Bob         Phys Ed         230000          2010


SQL: DONE.

//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[92] select * from student where fname = "Flo" and lname = "Yao"
Table name: _select_table_264, records: 1
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google


SQL: DONE.
[93] select * from student where major = "CS" and age < 25
Table name: _select_table_268, records: 2
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Anna Grace      Del Rio         CS              22              USAF


SQL: DONE.
[94] select * from student where major < Math and age > 25
Table name: _select_table_272, records: 3
0 del             fname           lname           major           age             company
1                 Bo              Yang            CS              28              Microsoft
2                 Sammuel L.      Jackson         CS              40              Uber
3                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[95] select * from employee where dep = CS and salary > 150000
Table name: _select_table_276, records: 2
0 del             last            first           dep             salary          year
1                 Yang            Bo              CS              160000          2013
2                 Van Gogh        Vincent         CS              245000          2015


SQL: DONE.
[96] select * from employee where last = Jackson and year < 2015
Table name: _select_table_280, records: 1
0 del             last            first           dep             salary          year
1                 Jackson         Bo              Chemistry       130000          2011


SQL: DONE.
[97] select * from employee where last = Johnson and year >=2014
Table name: _select_table_284, records: 5
0 del             last            first           dep             salary          year
1                 Johnson         Jack            HR              150000          2014
2                 Johnson         Mary Ann        Math            165000          2014
3                 Johnson         Billy Bob       Physics         142000          2014
4                 Johnson         Billy           Phys Ed         102000          2014
5                 Johnson         Jimmy           Chemistry       140000          2018


SQL: DONE.


//.................
//:OR            :
//.................
[98] select * from student where fname = Flo or lname = Jackson
Table name: _select_table_288, records: 3
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Flo             Jackson         Math            21              Google
3                 Flo             Yao             CS              20              Google


SQL: DONE.
[99] select * from student where age >=40  or company = Verizon
Table name: _select_table_292, records: 4
0 del             fname           lname           major           age             company
1                 Jim Bob         Smith           Math            23              Verizon
2                 Teresa Mae      Gowers          Chemistry       22              Verizon
3                 Sammuel L.      Jackson         CS              40              Uber
4                 Alex            Smith           Gender Studies  53              Amazon


SQL: DONE.
[100] select * from employee where first = Bo or last = Johnson
Table name: _select_table_296, records: 7
0 del             last            first           dep             salary          year
1                 Johnson         Jack            HR              150000          2014
2                 Johnson         Jimmy           Chemistry       140000          2018
3                 Johnson         Mary Ann        Math            165000          2014
4                 Johnson         Billy Bob       Physics         142000          2014
5                 Johnson         Billy           Phys Ed         102000          2014
6                 Yang            Bo              CS              160000          2013
7                 Jackson         Bo              Chemistry       130000          2011


SQL: DONE.
[101] select * from employee where year >= 2015 or dep = CS
Table name: _select_table_300, records: 9
0 del             last            first           dep             salary          year
1                 Blow            Joe             CS              100000          2018
2                 Yao             Flo             CS              147000          2012
3                 Yang            Bo              CS              160000          2013
4                 Van Gogh        Vincent         CS              245000          2015
5                 Van Gogh        Vincent         Art             240000          2015
6                 Blow            JoAnn           Physics         200000          2016
7                 Jackson         Flo             Math            165000          2017
8                 Jackson         Billy           Math            170000          2017
9                 Johnson         Jimmy           Chemistry       140000          2018


SQL: DONE.


//.................
//:OR AND         :
//.................
[102] select * from student where fname = Flo or major = CS and age <= 23
Table name: _select_table_304, records: 3
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Anna Grace      Del Rio         CS              22              USAF
3                 Flo             Jackson         Math            21              Google


SQL: DONE.
[103] select * from student where lname = Jackson or age < 23 and company > Uber
Table name: _select_table_308, records: 3
0 del             fname           lname           major           age             company
1                 Teresa Mae      Gowers          Chemistry       22              Verizon
2                 Sammuel L.      Jackson         CS              40              Uber
3                 Flo             Jackson         Math            21              Google


SQL: DONE.
[104] select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000
Table name: _select_table_312, records: 5
0 del             last            first           dep             salary          year
1                 Jackson         Flo             Math            165000          2017
2                 Jackson         Billy           Math            170000          2017
3                 Van Gogh        Vincent         Art             240000          2015
4                 Van Gogh        Vincent         CS              245000          2015
5                 Van Gogh        Jim Bob         Phys Ed         230000          2010


SQL: DONE.


//.................
//:AND OR AND     :
//.................

[105] select * from student where age <30 and major=CS or major = Physics and company = Amazon
Table name: _select_table_316, records: 4
0 del             fname           lname           major           age             company
1                 Greg            Pearson         Physics         20              Amazon
2                 Flo             Yao             CS              20              Google
3                 Bo              Yang            CS              28              Microsoft
4                 Anna Grace      Del Rio         CS              22              USAF


SQL: DONE.
[106] select * from student where age <=40 and company=Uber or major = CS and company = Google
Table name: _select_table_320, records: 3
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Sammuel L.      Jackson         CS              40              Uber
3                 Calvin          Woo             Physics         22              Uber


SQL: DONE.
[107] select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"
Table name: _select_table_324, records: 3
0 del             last            first           dep             salary          year
1                 Van Gogh        Vincent         Art             240000          2015
2                 Van Gogh        Vincent         CS              245000          2015
3                 Yang            Bo              CS              160000          2013


SQL: DONE.


//.................
//:OR AND OR      :
//.................

[108] select * from student where lname = Yang or major = CS and age < 23 or company = Google
Table name: _select_table_328, records: 4
0 del             fname           lname           major           age             company
1                 Flo             Yao             CS              20              Google
2                 Flo             Jackson         Math            21              Google
3                 Anna Grace      Del Rio         CS              22              USAF
4                 Bo              Yang            CS              28              Microsoft


SQL: DONE.
[109] select * from student where major = Physics or major = Math and company = Google or lname = Jackson
Table name: _select_table_332, records: 4
0 del             fname           lname           major           age             company
1                 Sammuel L.      Jackson         CS              40              Uber
2                 Flo             Jackson         Math            21              Google
3                 Greg            Pearson         Physics         20              Amazon
4                 Calvin          Woo             Physics         22              Uber


SQL: DONE.
[110] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 265000
Table name: _select_table_336, records: 8
0 del             last            first           dep             salary          year
1                 Van Gogh        Vincent         Art             240000          2015
2                 Van Gogh        Vincent         CS              245000          2015
3                 Blow            JoAnn           Physics         200000          2016
4                 Jackson         Flo             Math            165000          2017
5                 Jackson         Billy           Math            170000          2017
6                 Blow            Joe             CS              100000          2018
7                 Yao             Flo             CS              147000          2012
8                 Yang            Bo              CS              160000          2013


SQL: DONE.

[111] drop table student
drop table student completed


SQL: DONE.











Process finished with exit code 0
*/

#endif //TABLE_CLASS_Z_OUTPUT_H
