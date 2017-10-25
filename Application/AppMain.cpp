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
}
