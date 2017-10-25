#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include "json.hpp"
#include "Database.h"
#include "Table.h"
#include "Record.h"
#include "TableBuilder.h"
#include "GUI.h"

using json = nlohmann::json;
using namespace std;

Database* application = new Database();

void printRecord(Record* record) {
	//prtin them... strings i guess
	for (int i = 0; i < record->get_size(); i++) {
		cout << record->get_entry(i) << " ";
	}
	cout << endl;
}

int main() {
	int maxRows = 0;
	cout << "Enter number of rows to sample from datasets (-1 for all, 150 is the minimum) " << endl;
	cout << "Note the files are large and too many rows will result in excessive memory usage and slow runtimes" << endl;
	cout << "Sample Size: ";
	cin >> maxRows;
	
	json j;
	TableBuilder* tableBuilder = new TableBuilder(maxRows);
	
	string businessJSON = "dataset/business.json";
	string userJSON = "dataset/user.json";
	string reviewJSON = "dataset/review.json";
	string checkinJSON = "dataset/checkin.json";
	string tipJSON = "dataset/tip.json";
	
	cout << "Reading file " << businessJSON << "..." << endl;
	tableBuilder->setFilename(businessJSON);
	Table* newTable = tableBuilder->makeTable();
	application->add_Table(newTable, "Businesses");
	cout << "File 1/5 added to database" << endl;
	
	cout << "Reading file " << userJSON << "..." << endl; 
	tableBuilder->setFilename(userJSON);
	newTable = tableBuilder->makeTable();
	application->add_Table(newTable, "Users");
	cout << "File 2/5 added to database" << endl;
	
	cout << "Reading file " << checkinJSON << "..." << endl;
	tableBuilder->setFilename(checkinJSON);
	newTable = tableBuilder->makeTable();
	application->add_Table(newTable, "Check In's");
	cout << "File 3/5 added to database" << endl;
	
	cout << "Reading file " << tipJSON << "..." << endl;
	tableBuilder->setFilename(tipJSON);
	newTable = tableBuilder->makeTable();
	application->add_Table(newTable, "Tips");
	cout << "File 4/5 added to database" << endl;
	
	cout << "Reading file " << reviewJSON <<  "..." << endl;
	tableBuilder->setFilename(reviewJSON);
	newTable = tableBuilder->makeTable();
	application->add_Table(newTable, "Reviews");
	cout << "File 5/5 added to database" << endl;
	
	
	GUI* frontend = new GUI(application);
	return Fl::run();
	/*
	while(!quitFlag){
		getline(cin, userInput);
		selecter.setInput(userInput);
		handler();
	}*/
	/*
	ifstream ifs;
	ifs.open("dataset/tip.json");
	if(!ifs.good()) cout << "stream failed" << endl;
	json j;
	string jline;
	while(getline(ifs,jline)) {
		//cout << jline << endl;
		json::parse(jline);
		//cout << j << endl;
	}
	//yall ready for those dank querys?
	Database* testDatabase = new Database();
	Table* testTable = new Table();
	Record* testRecord = new Record(2);
	Record* testRecord1 = new Record(2);
	//set these bad bois up
	testRecord->set_entry(0, "John");
	testRecord->set_entry(1, "12200");
	//watch me break this
	testRecord1->set_entry(0, "123");
	testRecord1->set_entry(1, "Mark");
	//i dont like how they do this
	//it makes it so we can do dumb shit like this.
	testTable->add_attribute("Name");
	testTable->add_attribute("Age");
	testTable->insert_record(testRecord);
	testTable->insert_record(testRecord1);
	testDatabase->add_Table(testTable, "People");
	//what does this even do
	testTable->set_key("People");
	//HERE WE GO
	printTable(testTable);
	//this one broke, oh no
	//Table* testQuery = testDatabase->Query("*","People","Age >= 8 AND Name = John");
	//I gave them test cases for this shit too
	//printTable(testQuery);
	//not this one we must use paraenthese, NOT AS DANK CONFIRMED
	Table* testQuery = testDatabase->Query("*","People","(Age >= 8) AND (Name = John)");
	printTable(testQuery);
	//Min/Max Broke
	cout << testTable->Max("Age") << endl;
	//can we just chose a table?
	testQuery = testDatabase->Query("*", "People", "");
	printTable(testQuery);
	//shit dog we can
	//This is the C of Basic SQL implentations we can do whatever we fucking want
	//to but if your not carefull the data will fuck up because the Records have 
	//no concept of what data is what, Hope your fucking happy team who dropped pur API
	*/
}
