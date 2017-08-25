# cool-RDBMS
C++ implementation of RDBMS with interactive client interface.
Operations like Project, Select, Rename, UNion, Caretesion Product and Set Difference are avaiable.
## Files Description <br />
● data - Directory contains all files related to saved table.<br />
- For each table there are two files table_name_data.txt which contains all tuples of table and table_name_desc.txt which
contains information about table columns or attributes first line contains table name, second line names of all column and third line contains code for table columns data type.<br />
● code.cpp - Complete documented c++ code for this project.<br />
● queries.txt - Contains various queries which can be performed for tables stored in data file like Customer and CustomerPhone.<br />
● Readme.pdf - Contains description related to input format and how to set up this program running and install dependencies .

## Setup <br />
● Extract the zip folder in CD.<br />
● Open shell and go inside this folder using cd command in terminal.<br />
● Run the code.cpp using command “g++ -std=c++11 code.cpp -o code” for compiling and then “./code” for execution.<br />
● If not able to compile then directly run compiled file by “./code” .● “Welcome to SQL..” message appears then enter any query command from queries.txt or making you own command.<br />
● After performing all queries enter exit to move out of the program “Good bye...” message appears.<br />


## Queries:<br />
● Project<br />
: P( [ col1, col2, col3 ], table_name );<br />
- col1, col2, col3 and so on..are name of columns present in table.
- table_name name of table on which projection has to be applied.<br />
- In place of table_name nested queries can be given.<br />
Examples:<br />
- P([Name,Age,Sex],Customer);<br />
-P([Name,Age,Sex],S([Age<=20],Customer));<br />
● Select : S( [ cond1, cond2, cond3 ], table_name );<br />
- cond1, cond2, cond3 and so on..are condition to be applied on table_name.<br />
- C ond1 is like Age > 30 or it may be like Name = Arpit or can compare two columns like Id=Cust_Id.<br />
List of operators are:- >, < , >=, <=, != .<br />
- table_name name of table on which selection has to be applied<br />
- In place of table_name nested queries can be given.<br />
Examples:<br />
- S([Age>20,Sex=F],Customer);- S([Age<=22,Sex=F],P([Name,Age,Sex],Customer));<br />
● Rename : R( new_name, [ col1, col2, col3 ], table_name );<br />
- col1, col2, col3 and so on..are name of new columns to replace earlier columns in table.<br />
- new_name is new name of table.<br />
- table_name name of table on which Rename has to be done.<br />
- In place of table_name nested queries can be given.<br />
Examples:<br />
-R(new_Customer,[],Customer);<br />
-R(new_Customer,[Cust_Name,Cust_Age,Cust_Sex],P([Name,Age,Sex],Customer));<br />
● Union : U( table_name1 , table_name2 );<br />
- table_name1 and table_name2 are names of two table on which union has to be performed.<br />
- table_name1 and table_name2 has to Union compatible.<br />
- In place of table_name1 and table_name2 nested queries can be given.<br />
Examples:<br />
- U( Customer,Customer);<br />
- U( S([Age<20],Customer), S([City=Delhi],Customer));<br />
● Cartesian Product :<br />
C( table_name1 , table_name2 );- table_name1 and table_name2 are names of two table on which cartesian product has to be performed.<br />
- In place of table_name1 and table_name2 nested queries can be given.<br />
Examples:<br />
- C( Customer, R(Customer2,[ ],Customer) );<br />
● Set Difference : D( table_name1 , table_name2 );<br />
- table_name1 and table_name2 are names of two table on which set difference operation has to be performed .<br />
- It perform set difference operation Table1 - Table2.<br />
- table_name1 and table_name2 has to Union compatible.<br />
- In place of table_name1 and table_name2 nested queries can be given.<br />
Examples:<br />
- D(S([Age>20],Customer),S([Sex=F],Customer));<br />
● exit : for exit the Interface.<br />
Examples:<br />
-exit<br />

## Error HandlingError codes and their description :- <br />
● error_code 0 : Table not present.<br />
● error_code 1 : Column name not present in table.<br />
● error_code 2 : No of column does not match.<br />
● error_code 3 : Condition specified not present in table.<br />
● error_code 4 : Wrong condition operation.<br />
● error_code 5 : Insert semicolon at the end of parse_query.<br />
● error_code 6 : Syntax error in query.<br />
● error_code 7 : Multiple columns with same name please perform<br />
● Rename operation.<br />
● error_code 8 : Relations are Union incompatible.<br />
