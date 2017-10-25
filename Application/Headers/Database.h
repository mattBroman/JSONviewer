#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include "Record.h"
#include "Table.h"
using namespace std;

// Database.h
class Database {
 private:
 	map<string,Table*> database;
 public:
 	Database(); //default constructor
 	void add_Table(Table* tab, string name); // add a new table to the end of the data base
 	void drop_Table(string name); // remove a specific table from the data base
 	vector<string> list_Tables(); // print a list of all table names in the database
	vector<Table*> get_Tables(); // return pointers of all the tables in the database
	Table* Query(string SELECT, string FROM, string WHERE); // Query member function
};
#endif
