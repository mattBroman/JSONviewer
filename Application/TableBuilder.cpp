#define RECORD_SIZE 150
#include "TableBuilder.h"
using json = nlohmann::json;
using namespace std;

TableBuilder::TableBuilder(int limit) {
	filename = "";
	keyLoc = 0;
	if (limit > 0 && limit < 150) {
		maxRows = 151;
	}
	else {
		maxRows = limit;
	}
	currRecord = new Record(RECORD_SIZE);
	records = new vector<Record*>(0);
}

TableBuilder::TableBuilder(string file, int limit) {
	filename = file;
	keyLoc = 0;
	if (limit > 0 && limit < 150) {
		maxRows = 151;
	}
	else {
		maxRows = limit;
	}
	currRecord = new Record(RECORD_SIZE);
	records = new vector<Record*>(0);
}

void TableBuilder::setFilename(string name) {
	filename = name;
}

//parse the given file using nolhnamm::json line by line making one record per
//json entry. pass these intp a table pointer and return the table, set the key
//to the name of the json file by default
Table* TableBuilder::makeTable() {
	//set up the basics that we need
	json JSON;
	string currentLine;
	long int iteration = 0;
	keyLoc = 0;
	Table* contructTable = new Table();
	openFile();
	for (int i = 0; i < currRecord->get_size(); i++) {
		currRecord->set_entry(i, "");
	}
	
	//loop through each line of the json file
	if (maxRows > -1) {
		while (getline(filestream, currentLine) && iteration < maxRows) {
			records->push_back(currRecord);
			JSON = json::parse(currentLine);
			flatten(JSON);
			currRecord = new Record(RECORD_SIZE);
			iteration++;
		}
	}
	else {
		while (getline(filestream, currentLine)) {
			records->push_back(currRecord);
			JSON = json::parse(currentLine);
			flatten(JSON);
			currRecord = new Record(RECORD_SIZE);
		}
	}
	
	//add the keys into the table
	for (int i = 0; i < keys.size(); i++) {
		contructTable->add_attribute(keys.at(i));
	}
	
	//we add the records after inorder to API bugs
	for (int i = 0; i < records->size(); i++) {
		contructTable->insert_record(records->at(i));
	}
	//reset for the next run
	keys.clear();
	records->clear();
	keyMappings.clear();
	closeFile();
	
	return contructTable;
}

void TableBuilder::closeFile() {
		filestream.close();
}

//avoids the nested json objects that come from the json::parse
void TableBuilder::flatten(json JSON) {
	//run over every object in the json we recived
	for (json::iterator Jdata = JSON.begin(); Jdata != JSON.end(); Jdata++) {
		flattenHelper(Jdata);
	}
}

//flatten helper grabs the nested json objects since we need strings
//we continue to recurse in this until we find a value type we can do somthing with
void TableBuilder::flattenHelper(json::iterator Jdata) {
	if(isPrimative(Jdata)) {
		string data = rawConvert(Jdata);
		addData(Jdata, data);
	}
	else if (Jdata.value().type() == json::value_t::array) {
		string data = arrayConvert(Jdata);
		addData(Jdata, data);
	}
	else {
		json subJSON = Jdata.value();
		//if (subJSON != JSON.end()) {
			flatten(subJSON);
		//} 
	}
}

void TableBuilder::addData(json::iterator Jdata, string value) {
	checkNewKey(Jdata.key());
	addValueToRecord(Jdata.key(), value);
}

//see if the key we found was a new one, if so update
void TableBuilder::checkNewKey(string key) {
	if (keyMappings.find(key) == keyMappings.end()) {
		pair<string, int> keyValue(key, keyLoc);
		keyMappings.insert(keyValue);
		keyLoc++;
		keys.push_back(key);
	}
}

void TableBuilder::addValueToRecord(string key, string value) {
	int loc = keyMappings.find(key)->second;
	currRecord->set_entry(loc, value);
}

//we need to go deeper if its not one of these
bool TableBuilder::isPrimative(json::iterator Jdata) {
	return Jdata.value().type() == json::value_t::string           ||
		   Jdata.value().type() == json::value_t::number_integer   ||
		   Jdata.value().type() == json::value_t::number_float     ||
		   Jdata.value().type() == json::value_t::number_unsigned  ||
		   Jdata.value().type() == json::value_t::boolean          ||
		   Jdata.value().type() == json::value_t::null;
}

void TableBuilder::openFile() {
	filestream.open(filename);
	if(!filestream.good()) throw "2";
	 //failed to open file | BadFileName(filename);
}

//we need to change the json::value_t into a string, this acts as a manager
//by converting json::iterators into a string, value_t can be implicity converted
//to a c++ type if its valid, from there we need to convert into a string
string TableBuilder::rawConvert(json::iterator data) {
	if (data.value().type() == json::value_t::string) {
		string value = *data;
		return value;
	}
	else if (data.value().type() == json::value_t::number_integer ||
			 data.value().type() == json::value_t::number_unsigned) {
		int value = *data;
		return numberConvert(value);
	}
	else if (data.value().type() == json::value_t::number_float) {
		float value = *data;
		return numberConvert(value);
	}
	else if (data.value().type() == json::value_t::boolean) {
		return *data ? "True" : "False";
	}
	else if (data.value().type() == json::value_t::null) {
		return "";
	}
	else {
		throw " 1"; // somthing has gone horribly wrong
	}
}

string TableBuilder::numberConvert(int data) {
	stringstream ss;
	ss << data;
	return ss.str();
}

string TableBuilder::numberConvert(float data) {
	stringstream ss;
	ss << data;
	return ss.str();
}

//arrays are not json iterators so they are a special case
string TableBuilder::arrayConvert(json::iterator Jdata) {
	auto array = Jdata.value();
	stringstream ss;
	for(auto it = array.begin(); it != array.end(); it++) {
		ss << *it;
	}
	return ss.str();
}
