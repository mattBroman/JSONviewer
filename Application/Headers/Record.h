#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

#ifndef RECORD_H
#define RECORD_H

// Record.h
class Record 
{
private:
public:
	vector<string> rec;
	Record(int size);
	// A constructor that allows creation of a record of arbitrary size, and initialization of the entries to a null string
	int get_size();
	// the size of the record 
	void set_entry(int i, string val);
	// set rec[i] = val
	string get_entry(int i);
	// return rec[i]
};

#endif
