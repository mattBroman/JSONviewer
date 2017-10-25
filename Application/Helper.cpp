#include "Helper.h"
using namespace std;

void Helper::printRecord(Record* record) {
	for (int i = 0; i < record->get_size(); i++) {
		cout << record->get_entry(i) << " ";
	}
	cout << endl;
}

void Helper::printTable(Table* table) {
	//shall never know the tables name BIBLETHUMP
	//gonna be anther thing we have to just fucking know
	cout << "No Key Rip" << endl;
	
	//print them atty light names
	vector<string> attrs = table->get_attributes();
	for (int i = 0; i < attrs.size(); i++) {
		cout << attrs.at(i) << " ";
	}
	cout << endl;
	//print them dank records
	for (int i = 0; i < table->get_size(); i++) {
		printRecord(table->get_record(i));
	}
	cout << endl;	
}
