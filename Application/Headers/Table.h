#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "stdlib.h"
#include <algorithm>
#include "Record.h"
using namespace std;

#ifndef TABLE_H
#define TABLE_H


// Table.h
class Table
{
private:
	string name;
	vector<string>* attributes;
	vector<Record*> records;
	string key;
public:
	Table(); // default constructor 
	Table(vector<string>* input); // a constuctor should also be supported that takes a list of attribute names
	void add_attribute(string atb); 
	// takes attribute string, add it to the vector, goes through records vector, appending empty str
	void remove_attribute(string atb);
	// get atb elements number in attributes and then remove all data about this element from record 
	void insert_record(Record* rec);
	// push back record* on to records 
	vector<string> get_attributes();
	// returns a list of the attributes for that table , in order
	int get_size();
	// the number of records in the table
	Record* get_record(int i);
	// return individual records from the table
	void set_key(string atb);
	// that allows a single attribute name to be designated as a key for the table.
	Table* cross_join(Table* a, Table* b);
	// takes two tables as input and produces one table as output using cartesian product.
	Table* natural_join(Table* a, Table* b);
	// A function that allows a single attribute name to be designated as a key for the table.
	int Count(string atb);
	// compute the size of a single attribute
	string Min(string atb);
	// compute the minimum in a single attribute 
	string Max(string atb);
	// compute the maximum in a single attribute
};

#endif

