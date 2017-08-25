#include<bits/stdc++.h>
using namespace std;

string data_path = "./data/";     // path where data files for tables are stored

const char separator    = ' ';
const int nameWidth     = 22;
const int numWidth      = 2;

template<typename T> void printElement(T t, const int& width)     /* For displaying table data in a uniform way */
{
    cout << left << setw(width) << setfill(separator) << t;
}



/*
        Structures for mainting relations and objects related to them
*/


struct data_unit{                       /* Structure for a data unit i.e. a cell in relation table a numeric or string*/
    char type;
    int data1;
    string data2;
    data_unit(char type,string s){
        this->type = type;
        switch(type){
            case '1':
                this->data1 = atoi(s.c_str());
                break;
            case '2':
                this->data2 = s;
                break;
        }
    }
    string data(){              /* For returning output of a data unit */
        switch(this->type){
            case '1':
                return to_string(this->data1);
                break;
            case '2':
                return this->data2;
        }
    }
};


struct Table_row{                       /* Structure for a tuple of relation table */
    vector <data_unit> row;
};

struct Table{                           /* Structure for a a relation table containing relation name,column names and tuples */
    string table_name;
    vector <string> table_attr;
    vector <char> table_attr_type;
    vector<Table_row> table_row;

    int no_of_attribute(){
        return this->table_attr.size();
    }
    int no_of_record(){
        return this->table_row.size();
    }
};

map<string,Table> Table_all;    /* map for mapping relation name with it's relation table  */

struct opt{             /* Structure for defining an operator and performing operation on two data units based on type of operator */
    string type;
    opt(string s){
        this->type=s;
    }
    bool cal(data_unit a, data_unit b){
        if (this->type==">=" && a.type=='1' && b.type=='1' && a.data1>=b.data1) return true;
        else if (this->type==">" && a.type=='1' && b.type=='1' && a.data1>b.data1) return true;
        else if (this->type=="<=" && a.type=='1' && b.type=='1' && a.data1<=b.data1) return true;
        else if (this->type=="<" && a.type=='1' && b.type=='1' && a.data1<b.data1) return true;
        else if (this->type=="=" && a.type=='1' && b.type=='1' && a.data1==b.data1) return true;
        else if (this->type=="!=" && a.type=='1' && b.type=='1' && a.data1!=b.data1) return true;
        else if (this->type=="=" && a.type=='2' && b.type=='2' && a.data2==b.data2) return true;
        else if (this->type=="!=" && a.type=='2' && b.type=='2' && a.data2!=b.data2) return true;

        else return false;
    }
};

typedef pair< pair<string,string>,opt> cond; /* Structure for storing operand value and operator for making conditions */






/*
        Helping functions
*/



int parse_int(string s){  /* Function for converting a string to integer */

    return atoi( s.c_str() );
}

bool my_str_cmp(string a,string b){  /* Function for comparing two strings */
    if(a==b)return true;
    else return false;
}

string rem_spaces(string s){ /* Function to remove spaces from a parse_query string */
    string tok;
    istringstream iss(s);
    do
    {
        string sub;
        iss >> sub;
        tok+=sub;
    } while (iss);
    return tok;
}

vector<string> cs_parse(string s){ /* Function to return comma separted list of strings */

    vector<string> result;
    if (s.size()==0)return result;
    stringstream ss(s);
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        result.push_back( substr );
    }
    return result;
}

/* Function to check if a given character is of Relation Algebra operation like Project, Select etc. */
bool is_func(char c){
    if(c=='P'||c=='S'||c=='U'||c=='R' ||c=='C' || c=='D')return true;
    else return false;
}

/* boolean function which returns True/False if a given string is valid type of operator */
bool is_valid_opt(string s){

    if(s=="="||s==">"||s==">="||s=="<="||s=="<"||s=="!=")return true;
    else return false;
}

/* Function for printing contents of a relation */
void print_table(Table table1){
    cout<<table1.table_name<<endl;

    for(int i=0;i<table1.no_of_attribute();i++){
        printElement(table1.table_attr[i],nameWidth);
    }
    cout<<endl;

    for(int i=0;i<table1.no_of_record();i++)
    {
        for(int j=0;j<table1.no_of_attribute();j++)
        {
            if(table1.table_row[i].row[j].type==1)printElement(table1.table_row[i].row[j].data(),numWidth);
            else printElement(table1.table_row[i].row[j].data(),nameWidth);

        }
        cout << endl;
    }
}

/* Function for printing error in reference to error code provided */
void error_generate(int code){
    cout<<"error_code: "<<code<<" : ";
    switch(code){
        case 0: cout<<"Table not present\n";
            break;
        case 1: cout<<"Column name not present in table\n";
            break;
        case 2: cout<<"No of column does not match\n";
            break;
        case 3: cout<<"Condition specified not present in table\n";
            break;
        case 4: cout<<"Wrong condition operation\n";
            break;
        case 5: cout<<"Insert semicolon at the end of parse_query\n";
            break;
        case 6: cout<<"Syntax error in query\n";
            break;
        case 7: cout<<"Multiple columns with same name please perform Rename operation\n";
            break;
        case 8: cout<<"Relations are Union incompatible\n";
            break;
    }
    exit(0);
}







/*
         Special function based on requirements of parse_query and table creation and loading
*/



/* boolean function which returns True/False if a given set of conditions satisfies on a particular tuple */
bool cond_check(vector<cond> cons,Table_row tr,vector<string> table_attr){
    bool flag=true;
    int i;
    for(auto f : cons){
        i=0;
        for(i=0;i<table_attr.size();i++){
            if((f).first.first == table_attr[i]){
                int j;
                 //if value is another attribute of relation
                for(j=0;j<table_attr.size();j++){
                        if((f).first.second == table_attr[j]){
                            if(!(f).second.cal(tr.row[i],tr.row[j]) ){
                                flag=false;
                                return flag;
                            }
                            break;
                        }
                }
                //if value is constant
                if(j==table_attr.size()){
                    data_unit dt = data_unit(tr.row[i].type,(f).first.second);
                    if(!(f).second.cal(tr.row[i],dt) ){
                                flag=false;
                                return flag;
                    }
                }
                break;
            }
        }
        if(i==table_attr.size()){ // attribute specified in condition not present in relation table
            error_generate(3);
        }
    }
    return true;
}

/* Function for building set of condition by parsing string containing multiple conditions */
vector<cond> build_cond(vector<string> attr_list,vector<char> attr_type,vector<string> s){
    vector<cond> cons;
    char attr_code = '1';

    for(int i=0;i<s.size();i++){
        int idx,flag=-1;
        for(idx=0;idx<s[i].size()-1;idx++){
            if(is_valid_opt(s[i].substr(idx,2))){
                flag=2;
                break;
            }
            if(is_valid_opt(s[i].substr(idx,1))){
                flag=1;
                break;
            }
        }
        if(flag==-1){            // if given condition contain no valid operator
            error_generate(4);
        }
        string attr = s[i].substr(0,idx);
        string op = s[i].substr(idx,flag);
        string val = s[i].substr(idx+flag,s[i].size()-idx-flag);
        if(flag!=-1){
            opt op1(op);
            cond en1 = make_pair(make_pair(attr,val),op1);
            cons.push_back(en1);
        }
    }
    return cons;
}

/* For comparing two data unit whether they are equal or not */
bool cmp_data(data_unit a, data_unit b){
    if(a.type!=b.type)return 0;
    if(a.type=='1')return a.data1==b.data1;
    if(a.type=='2')return a.data2==b.data2;
}

/* Function for creating a table from data files in memory based on table name provided */
Table create_table(string table_name)
{

    Table new_table;
    string file_path1 = data_path+table_name+"_desc.txt"; //load desc file of table
    string file_path2 = data_path+table_name+"_data.txt"; //load data file of table

    ifstream infile(file_path1);
    if(infile.fail()){
        error_generate(0);
    }
    int cnt=0;
    while(infile)
    {
        string s;
        if(!getline(infile,s)) break;

        istringstream ss( s );
        while(ss){
            string s;
            if(!getline(ss,s,'\t')) break;
            if(cnt==0){
                new_table.table_name=s;

            }
            else if(cnt==1){
               new_table.table_attr.push_back(s);

            }
            else if(cnt==2){
                new_table.table_attr_type.push_back(s[0]);
            }
        }
        cnt++;
    }

    ifstream infile2(file_path2);
    if(infile2.fail()){
        error_generate(0);
    }
    while(infile2)
    {
        string s;
        if(!getline(infile2,s)) break;

        istringstream ss( s );
        Table_row record;
        cnt=0;
        while(ss){
            string s;
            if(!getline(ss,s,'\t')) break;

            data_unit dt(new_table.table_attr_type[cnt],s);
            record.row.push_back(dt);
            cnt++;
        }

        new_table.table_row.push_back(record);

    }

    Table_all[table_name] = new_table;
    return new_table;

}

/* Function returns table if it is already loaded else first create it and then returns */
Table load_table(string rel_name){

    if( Table_all.find( rel_name ) != Table_all.end()){
        return Table_all[rel_name];
    }
    Table_all[rel_name] = create_table(rel_name);
    return Table_all[rel_name];
}










/*
         Functions for performing various relational algebra operations
*/



/* Function to project a table on sets of attributes provided  */
Table Project(Table table1,vector<string> sets_attr){

    Table res_table;
    vector<bool> attr_chk(table1.no_of_attribute(),false); // boolean array to check whether the attribute is present in table or not.
     
    for(int i=0;i<sets_attr.size();i++){
        int j=0;
        for(;j<table1.no_of_attribute();j++){
            if(my_str_cmp(sets_attr[i],table1.table_attr[j])){
                attr_chk[j]=true;
                break;
            }
        }
        if(j==table1.no_of_attribute()){
            //error column name not present in table
            error_generate(1);
        }
    }
    for(int i=0;i<table1.no_of_record();i++){
        Table_row record;
        for(int j=0;j<table1.no_of_attribute();j++){
            if(attr_chk[j]){                       // if this attribute is present in set of attribute.
                record.row.push_back(table1.table_row[i].row[j]); // push the cell to record.
            }
        }
        res_table.table_row.push_back(record); // push the record to result table.
    }

    for(int j=0;j<table1.no_of_attribute();j++){  // setting column name of res table
            if(attr_chk[j]){
                res_table.table_attr.push_back(table1.table_attr[j]);
                res_table.table_attr_type.push_back(table1.table_attr_type[j]);
            }
        }

    res_table.table_name = "";
    return res_table;
}

/* Function to select all tuples of a table based on the set of conditions provided */
Table Select(Table table1,vector<cond> cons){
    Table new_table;

    for(int i=0;i<table1.no_of_record();i++){
        if(cond_check(cons,table1.table_row[i],table1.table_attr )){ // if set of conditions satisfies a tuple.
            new_table.table_row.push_back(table1.table_row[i]);
        }
    }
    for(int j=0;j<table1.no_of_attribute();j++){       // setting column name of res table
        new_table.table_attr.push_back(table1.table_attr[j]);
        new_table.table_attr_type.push_back(table1.table_attr_type[j]);
    }

    new_table.table_name = "";
    return new_table;
}

/* Function to rename a table */
Table Rename(Table table1,vector<string> sets_attr,string new_name){

    Table new_table;
    bool flag=1;
    if(sets_attr.size()==0)flag=0;
    if(flag && sets_attr.size()!=table1.table_attr.size()){
        // if attributes count does not match to attribute count of table
        error_generate(2);
    }
    for(int i=0;i<table1.no_of_record();i++){
        Table_row record;
        for(int j=0;j<table1.no_of_attribute();j++){
            if(i==0){
                if(flag){                       // if list of new attributes is provided
                    new_table.table_attr.push_back(sets_attr[j]);
                    new_table.table_attr_type.push_back(table1.table_attr_type[j]);
                }
                else{                           // if list of new attributes is not provided
                    new_table.table_attr.push_back(table1.table_attr[j]);
                    new_table.table_attr_type.push_back(table1.table_attr_type[j]);
                }
            }
            record.row.push_back(table1.table_row[i].row[j]);

        }
        new_table.table_row.push_back(record);   // insert tuple in new table
    }

    new_table.table_name = new_name;
    return new_table;
}

/* Function to perform Union operation between two tables */
Table Union(Table table1, Table table2){

    if(table1.no_of_attribute()!=table2.no_of_attribute()){
        // if attributes count of table1 does not match to attribute count of table2
        error_generate(1);
    }

    vector<bool> attr_chk(false,table1.no_of_attribute()); // boolean array to check whether the attribute is present in table or not.

    for(int i=0;i<table1.no_of_attribute();i++){
       
        if(!my_str_cmp(table1.table_attr[i],table2.table_attr[i]) || table1.table_attr_type[i]!=table2.table_attr_type[i]){
            error_generate(8);
        }
    }

    for(int i=0;i<table2.no_of_record();i++){  // for each tuple in table2 insert it into table1 if it is not
                                                // present in table2.
        Table_row record;
        bool flag=1;

        for(int j=0;j<table1.no_of_record();j++){
            int cnt=0;
            for(int k=0;k<table2.no_of_attribute();k++){
                if(cmp_data(table2.table_row[i].row[k],table1.table_row[j].row[k])){
                    cnt++;
                }
            }
            if(cnt==table2.no_of_attribute()){ // if all attributes matches then two tuples are same
                                               // set flag to 0.
                flag=0;
                break;
            }
        }

        for(int j=0;j<table1.no_of_attribute();j++){   // construct a new record to insert.

            record.row.push_back(table2.table_row[i].row[j]);
        }

        if(flag)table1.table_row.push_back(record);

    }

    return table1;
}

/* Function to perform Cartesian Product operation between two tables */
Table CartesianProduct(Table table1, Table table2){

    Table new_table;

    vector<bool> attr_chk(false,table1.no_of_attribute()); // boolean array to check whether the attribute is present in table or not.
     
    for(int i=0;i<table1.no_of_record();i++){  // concatenate every tuple of table1 with every tuple of table2

        for(int j=0;j<table2.no_of_record();j++){
            Table_row record;
            for(int k=0;k<table1.no_of_attribute();k++){
                record.row.push_back(table1.table_row[i].row[k]);
            }
            for(int k=0;k<table2.no_of_attribute();k++){
                record.row.push_back(table2.table_row[j].row[k]);
            }

            new_table.table_row.push_back(record);
        }

    }
    // change the name of table1 atrribute to table1.attribute and same for table2
    for(int k=0;k<table1.no_of_attribute();k++){
        new_table.table_attr.push_back(table1.table_name+"."+table1.table_attr[k]);
        new_table.table_attr_type.push_back(table1.table_attr_type[k]);
    }

    for(int k=0;k<table2.no_of_attribute();k++){
        new_table.table_attr.push_back(table2.table_name+"."+table2.table_attr[k]);
        new_table.table_attr_type.push_back(table2.table_attr_type[k]);
    }
    for(int i=0;i<new_table.no_of_attribute();i++)
        for(int j=0;j<new_table.no_of_attribute();j++)if(i!=j && my_str_cmp(new_table.table_attr[i],new_table.table_attr[j])){
                //same column name;
            error_generate(7);
        }
    return new_table;
}

/* Function to perform Set Difference operation between two tables  as table1 - table2 */
Table SetDifference(Table table1, Table table2){

    if(table1.no_of_attribute()!=table2.no_of_attribute()){
        // if attributes count of table1 does not match to attribute count of table2
        error_generate(1);
    }
    Table new_table;

    vector<bool> attr_chk(false,table1.no_of_attribute()); // boolean array to check whether the attribute is present in table or not.
     

    for(int i=0;i<table1.no_of_attribute();i++){
       
        if(!my_str_cmp(table1.table_attr[i],table2.table_attr[i]) || table1.table_attr_type[i]!=table2.table_attr_type[i]){
            error_generate(8);
        }
    }
    for(int i=0;i<table1.no_of_record();i++){  // for each tuple in table1 which is not present in table2 push in new table.
        Table_row record;
        bool flag=1;
        for(int j=0;j<table2.no_of_record();j++){
            int cnt=0;
            for(int k=0;k<table2.no_of_attribute();k++){
                if(cmp_data(table2.table_row[j].row[k],table1.table_row[i].row[k])){ // if two cells matches.
                    cnt++;
                }
            }
            if(cnt==table2.no_of_attribute()){ // if two tuples matches.
                flag=0;
                break;
            }
        }

        record = table1.table_row[i];
        if(flag)new_table.table_row.push_back(record);

    }
    // assigning column names to new table same as that of table1.
    for(int k=0;k<table1.no_of_attribute();k++){
            new_table.table_attr.push_back(table1.table_attr[k]);
            new_table.table_attr_type.push_back(table1.table_attr_type[k]);
    }
    new_table.table_name="";
    return new_table;
}










/*
        Parsing functions for various queries
*/



Table parse_query(string );

/* Function to perform parsing for Project query */
Table parse_query_Project(string s){
    Table table1;
    vector<string> attr_list;
    if(s[2]=='['){
        int i;
        for(i=3;s[i]!=';' && s[i]!=']';i++);
        if(s[i]==']'){
            string attr = s.substr(3,i-3);
            attr_list = cs_parse(attr); //return commas seperated list of string

            if(s[i+1]==',' && (is_func(s[i+2]))&&(s[i+3]=='(')){ //recursion for nested queries

                string s2 = s.substr(i+2,s.size()-i-4)+';';
                Table res = parse_query(s2);  // resultant table after performing nested query.

                if(attr=="*"){       // if to project all attributes
                    attr_list = res.table_attr;
                }

                table1 = Project(res,attr_list); // final projected table.
            }
            else{
                string rel_name = s.substr(i+2,s.size()-i-4);
                Table table2 = load_table(rel_name);// load table rel_name

                if(attr=="*"){
                    attr_list = table2.table_attr;
                }
                table1 = Project(table2,attr_list);  // final projected table.
             }
        }
        else{
            // syntax error
            error_generate(6);
        }
    }
    else{
        // syntax error
        error_generate(6);
    }
    return table1;
}

/* Function to perform parsing for Select query */
Table parse_query_Select(string s){
    Table table1;
    vector<cond> cons;
    vector<string> cndn_list;
    if(s[2]=='['){
        int i;

        for(i=3;s[i]!=';' && s[i]!=']';i++);
        if(s[i]==']'){

            string attr = s.substr(3,i-3);
            if(attr=="*"){   // if to select all attributes
                string new_q = s;
                new_q[0]='P';
                return parse_query(new_q);
            }
            cndn_list = cs_parse(attr); //return commas seperated list of string

            if(s[i+1]==',' && (is_func(s[i+2])) &&(s[i+3]=='(')){ //recursion for nested queries

                string s2 = s.substr(i+2,s.size()-i-4)+';';
                Table res = parse_query(s2); // resultant table after performing nested query.

                cons = build_cond(res.table_attr,res.table_attr_type,cndn_list); // build set of constraint from condition given.
                table1 = Select(res,cons); // final selected table.
            }
            else{
                string rel_name = s.substr(i+2,s.size()-i-4);
                Table table2 = load_table(rel_name); // load table rel_name

                cons = build_cond(table2.table_attr,table2.table_attr_type,cndn_list); // build set of constraint from condition given.
                table1 = Select(table2,cons);  // final selected table.
             }
        }
        else{
            // syntax error
            error_generate(6);
        }
    }
    else{
        // syntax error
        error_generate(6);
    }
    return table1;
}

/* Function to perform parsing for Rename query */
Table parse_query_Rename(string s){
    Table table1;
    vector<string> attr_list; // for storing new names for attributes.
    int i,i_old;

    for(i=3;s[i]!=';' && s[i]!=',';i++);
    string new_name = s.substr(2,i-2);
    if(s[i+1]=='[' || (is_func(s[i+1]) &&(s[i+2]=='(')) ){
        i_old=i;
        if(s[i+1]=='[')for(i=i+2;s[i]!=';' && s[i]!=']';i++);
        string attr;    // contains new attributes
        if(i!=i_old){
            attr = s.substr(i_old+2,i-i_old-2);
            attr_list = cs_parse(attr); //return commas seperated list of string

         }
         else{
            i--;
         }

        if(s[i+1]==',' && (is_func(s[i+2])) &&(s[i+3]=='(')){ //recursion for nested queries

            string s2 = s.substr(i+2,s.size()-i-4)+';';
            Table res = parse_query(s2);
            table1 = Rename(res,attr_list,new_name); // final renamed table.
        }
        else{
            string rel_name = s.substr(i+2,s.size()-i-4);

            Table table2 = load_table(rel_name);   // load table rel_name

            table1 = Rename(table2,attr_list,new_name);  // final renamed table.
         }
    }
    else{
        // syntax error
        error_generate(6);
    }
    return table1;
}

/* Function to perform parsing for Union query */
Table parse_query_Union(string s){
    Table table1;
    vector<string> attr_list;   // for storing new names for attributes.

    if(is_func(s[2]) &&s[3]=='('){   //recursion for nested queries
        int cnt=1;
        int idx=4;
        while(cnt!=0){          // for finding index after end of nested query.
            if(s[idx]=='(')cnt++;
            if(s[idx]==')')cnt--;
            idx++;
        }
        string s2 = s.substr(2,idx-2)+';';

        Table table1 = parse_query(s2);  // resultant table after performing nested query.

        Table table2;
        if(is_func(s[idx+1])&&s[idx+2]=='('){  //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2);  // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }

        Table res = Union(table1,table2);  // resultant table Union operation
        return res;
    }
    else{
        int idx=2;
        while(s[idx]!=','){
            idx++;
        }
        string rel_name = s.substr(2,idx-2);
        Table table1 = load_table(rel_name);   // load table rel_name
        Table table2;

        if(is_func(s[idx+1])&&s[idx+2]=='('){   //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2); // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }
        Table res = Union(table1,table2);  // resultant table Union operation
        return res;
    }

    return table1;
}

/* Function to perform parsing for Cartesian Product query */
Table parse_query_CartesianProduct(string s){
    Table table1;
    vector<string> attr_list;   // for storing new names for attributes.

    if(is_func(s[2]) &&s[3]=='('){   //recursion for nested queries
        int cnt=1;
        int idx=4;
        while(cnt!=0){          // for finding index after end of nested query.
            if(s[idx]=='(')cnt++;
            if(s[idx]==')')cnt--;
            idx++;
        }

        string s2 = s.substr(2,idx-2)+';';

        Table table1 = parse_query(s2);  // resultant table after performing nested query.

        Table table2;
        if(is_func(s[idx+1])&&s[idx+2]=='('){  //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2);  // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }

        Table res = CartesianProduct(table1,table2);  // resultant table CartesianProduct operation
        return res;
    }
    else{
        int idx=2;
        while(s[idx]!=','){
            idx++;
        }
        string rel_name = s.substr(2,idx-2);
        Table table1 = load_table(rel_name);   // load table rel_name
        Table table2;

        if(is_func(s[idx+1])&&s[idx+2]=='('){   //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2); // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }
        Table res = CartesianProduct(table1,table2);  // resultant table CartesianProduct operation
        return res;
    }

    return table1;
}


/* Function to perform parsing for Set Diff query */
Table parse_query_SetDifference(string s){
    Table table1;
    vector<string> attr_list;   // for storing new names for attributes.

    if(is_func(s[2]) &&s[3]=='('){   //recursion for nested queries
        int cnt=1;
        int idx=4;
        while(cnt!=0){          // for finding index after end of nested query.
            if(s[idx]=='(')cnt++;
            if(s[idx]==')')cnt--;
            idx++;
        }

        string s2 = s.substr(2,idx-2)+';';

        Table table1 = parse_query(s2);  // resultant table after performing nested query.

        Table table2;
        if(is_func(s[idx+1])&&s[idx+2]=='('){  //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2);  // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }

        Table res = SetDifference(table1,table2);  // resultant table SetDifference operation
        return res;
    }
    else{
        int idx=2;
        while(s[idx]!=','){
            idx++;
        }

        string rel_name = s.substr(2,idx-2);
        Table table1 = load_table(rel_name);   // load table rel_name
        Table table2;

        if(is_func(s[idx+1])&&s[idx+2]=='('){   //recursion for nested queries
            string s2 = s.substr(idx+1,s.size()-idx-3)+';';
            table2 = parse_query(s2); // resultant table after performing nested query.
        }
        else{
            string rel_name = s.substr(idx+1,s.size()-idx-3);
            table2 = load_table(rel_name);  // load table rel_name
        }
        Table res = SetDifference(table1,table2);  // resultant table SetDifference operation
        return res;
    }

    return table1;
}

/* Function to perform parsing for all queries */
Table parse_query(string s){

    if(s[s.size()-1]!=';'){  // if query not terminated with ';' .
        error_generate(5);
    }

    if(s[0]=='P' && s[1]=='('){   // Project query
        return parse_query_Project(s);
    }
    else if(s[0]=='S' && s[1]=='('){ // Select query
        return parse_query_Select(s);
    }
    else if(s[0]=='R' && s[1]=='('){ // Rename query
        return parse_query_Rename(s);
    }
    else if(s[0]=='U' && s[1]=='('){  // Union query
        return parse_query_Union(s);
    }
    else if(s[0]=='C' && s[1]=='('){   // CartesianProduct query
        return parse_query_CartesianProduct(s);
    }
    else if(s[0]=='D' && s[1]=='('){   // SetDifference query
        return parse_query_SetDifference(s);
    }
    else{
        error_generate(6);  // no such query exist
    }
}




int main()
{

    string proj_parse_query;
    cout<<"Welcome to SQL..\n\n";
    cout<<">> ";
    while(getline(cin,proj_parse_query)){   // gets input until their is query to be execute.
        string par_proj_parse_query = rem_spaces(proj_parse_query); //remove extra spaces from query string
        if(par_proj_parse_query=="exit"){
            cout<<"\n\nGood bye...\n";
            break;
        }
        else if(par_proj_parse_query!=""){
            Table res = parse_query(par_proj_parse_query);
            cout<<"\n";
            print_table(res);
        }
        cout<<"\n>> ";                     // print contents of table.
    }

    return 0;
}


