# cool-RDBMS

## Files Description

● data - Directory contains all files related to saved table.<br />
- For each table there are two files table_name_data.txt which contains all tuples of table and table_name_desc.txt which
contains information about table columns or attributes first line contains table name, second line names of all column and third line contains code for table columns data type.
● code.cpp - Complete documented c++ code for this project.
● queries.txt - Contains various queries which can be performed for tables stored in data file like Customer and CustomerPhone.
● Readme.pdf - Contains description related to input format and how to
set up this program running and install dependencies .

##Setup
● Extract the zip folder in CD.
● Open shell and go inside this folder using cd command in terminal.
● Run the code.cpp using command “g++ -std=c++11 code.cpp -o code” for compiling and then “./code” for execution.
● If not able to compile then directly run compiled file by “./code” .● “Welcome to SQL..” message appears then enter any query command from queries.txt or making you own command.
● After performing all queries enter exit to move out of the program “Good bye...” message appears.

##Queries:
● Project
: P( [ col1, col2, col3 ], table_name );
- col1, col2, col3 and so on..are name of columns present in
table.
- table_name name of table on which projection has to be applied
- In place of table_name nested queries can be given.
Examples:
- P([Name,Age,Sex],Customer);
-P([Name,Age,Sex],S([Age<=20],Customer));
● Select : S( [ cond1, cond2, cond3 ], table_name );
- cond1, cond2, cond3 and so on..are condition to be applied on
table_name.
- C ond1 is like Age > 30 or it may be like Name = Arpit or
can compare two columns like Id=Cust_Id.
List of operators are:- >, < , >=, <=, != .
- table_name name of table on which selection has to be applied
- In place of table_name nested queries can be given.
Examples:
- S([Age>20,Sex=F],Customer);- S([Age<=22,Sex=F],P([Name,Age,Sex],Customer));
● Rename : R( new_name, [ col1, col2, col3 ], table_name );
- col1, col2, col3 and so on..are name of new columns to replace
earlier columns in table.
- new_name is new name of table.
- table_name name of table on which Rename has to be done.
- In place of table_name nested queries can be given.
Examples:
-R(new_Customer,[],Customer);
-R(new_Customer,[Cust_Name,Cust_Age,Cust_Sex],P([Name,Age,S
ex],Customer));
● Union : U( table_name1 , table_name2 );
- table_name1 and table_name2 are names of two table on
which union has to be performed .
- table_name1 and table_name2 has to Union compatible.
- In place of table_name1 and table_name2 nested queries can
be given.
Examples:
- U( Customer,Customer);
- U( S([Age<20],Customer), S([City=Delhi],Customer));
● Cartesian Product :
C( table_name1 , table_name2 );- table_name1 and table_name2 are names of two table on
which cartesian product has to be performed .
- In place of table_name1 and table_name2 nested queries can
be given.
Examples:
- C( Customer, R(Customer2,[ ],Customer) );
● Set Difference : D( table_name1 , table_name2 );
- table_name1 and table_name2 are names of two table on
which set difference operation has to be performed .
- It perform set difference operation T
able1 - Table2.
- table_name1 and table_name2 has to Union compatible.
- In place of table_name1 and table_name2 nested queries can
be given.
Examples:
- D(S([Age>20],Customer),S([Sex=F],Customer));
● exit : for exit the Interface.
Examples:
-exit

#Error HandlingError codes and their description :-
● error_code 0 : Table not present.
● error_code 1 : Column name not present in table.
● error_code 2 : No of column does not match.
● error_code 3 : Condition specified not present in table.
● error_code 4 : Wrong condition operation.
● error_code 5 : Insert semicolon at the end of parse_query.
● error_code 6 : Syntax error in query.
● error_code 7 : Multiple columns with same name please perform
● Rename operation.
● error_code 8 : Relations are Union incompatible.
