#include "Database.h"

using namespace std;

//empty placeholder functions 

Table::Table() : key("") {}
Table::Table(vector<string> attributes) : attributes(attributes), key("") {}		
		
void Table::addAttribute(string newAttribute) {
	//check if attribute is already in the attribute vector
	auto requestedAttr = find(attributes.begin(), attributes.end(), newAttribute);
	if (requestedAttr != attributes.end()) {
		throw AlreadyDefined();
	}
	
	//add the attribute to the attribute vector
	attributes.push_back(newAttribute);
	
	//iterate over every record and add the new attribute to each one
	for (pair<string, Record> currentEntry : records) {
		currentEntry.second.addAttribute(newAttribute);
	}
}
void Table::deleteAttribute(string attribute) {
	auto requestedAttr = find(attributes.begin(), attributes.end(), attribute);
	if (requestedAttr == attributes.end()) {
		//if the attribute is not in the table, don't delete anything
		throw AttributeNotFound();
	}

	//delete the attribute from the attributes vector if it was found (erase-remove idiom)
	attributes.erase(remove(attributes.begin(), attributes.end(),
			         *requestedAttr), attributes.end());
	
	//iterate over each record and delete the found attribute
	for (pair<string, Record> currentEntry : records) {
		currentEntry.second.deleteAttribute(attribute);
	}	
	
}			
void Table::addRecord(Record& record) {
	//don't add a record with too many elements 
	//pass it by referance fam
	if (records.find(record.getRecordKey()) != records.end()) {
		throw AlreadyDefined();
	}
	if (record.findSize() > this->attributes.size()) {
		throw InvalidRecord();
	}
		//check if attributes are valid here
	vector<string> recordAttrs = record.listAttributes();
	sort(recordAttrs.begin(), recordAttrs.end());
	vector<string> sortedTableAttrs = this->attributes;
	sort(sortedTableAttrs.begin(), sortedTableAttrs.end());
	
	for (int i = 0; i < recordAttrs.size(); i++) {
		if (recordAttrs.at(i) != sortedTableAttrs.at(i)) {
			throw InvalidRecord();
		}
	}
	
	pair<string, Record> newPair(record.getRecordKey(), record);
	records.insert(newPair);
}					
vector<string> Table::listAttributes() {	
	return attributes;
}					

int Table::countAttribute(string attribute) {
	int attributeCount = 0;
	for (pair<string, Record> currentEntry : records) {
		if (currentEntry.second.getValue(attribute) != "") {
			//if the value mappeed to the attr is not empty, count it
			attributeCount++; 
		}
	}
	return attributeCount;	
}
int Table::getSize() {
	//proper getSize function
	return records.size();
}

unordered_map<string, Record>::iterator Table::getRecord(bool begin) {
	if (begin) {
		return records.begin();
	}
	return records.end();
}
								
unordered_map<string, Record>::iterator Table::getRecord(string record) {
	unordered_map<string, Record>::iterator iter = records.find(record);

	//iter will == records.end() if item is not found - how to handle this?
	if (iter == records.end()) {
		throw KeyNotFound();
	}
	return iter;
}
	
		
void Table::specifyKey(string key) {
	this->key = key;
}		    
void Table::crossJoin(Table joinTable) {
	//FIX: add method to filter by attributes of each table? should this be handled by query?
	vector<string> crossAttrs = this->attributes; //combined attribute list
	vector<string> joinTableAttrs = joinTable.listAttributes(); //attribute list from argument table

	//combine attributes from calling table and argument table 
	crossAttrs.insert(crossAttrs.begin(), joinTableAttrs.begin(), joinTableAttrs.end());
	
	Table crossTable;
	crossTable.attributes = crossAttrs;
	
	for (pair<string, Record> currentEntry1 : records) {
		for (pair<string, Record> currentEntry2: joinTable.records) {
			Record crossRecord = currentEntry1.second;
			crossRecord.setRecordKey(currentEntry1.second.getRecordKey()
									 + " " + currentEntry2.second.getRecordKey());
			
			for (int i = 0; i < joinTableAttrs.size(); i++) {
				//combine the records
				crossRecord.addAttribute(joinTableAttrs.at(i),
										 currentEntry2.second.getValue(joinTableAttrs.at(i)));
			}
			crossTable.addRecord(crossRecord);
		}
	}
	this->attributes = crossAttrs;
	this->records = crossTable.records; //overwrite caller's table
}	
void Table::naturalJoin(Table joinTable) {
	//check if at least one attribute matches between the two tables
	
	vector<string> joinTableAttrs = joinTable.listAttributes();
	if (!checkSharedAttribute(this->attributes, joinTableAttrs)) {
		//if the two tables have no attributes in common, don't join
		throw InvalidJoin();
	}
	//column names are determined implicitly, determine them here and clean up the records

	vector<string> sharedAttrs;
	
	for (int i = 0; i < this->attributes.size(); i++) {
		for (int j = 0; j < joinTableAttrs.size(); j++) {
			if (this->attributes.at(i) == joinTableAttrs.at(j)) {
				//keep track of shared attributes
				sharedAttrs.push_back(joinTableAttrs.at(j));
			}
		}
	}
	
	Table naturalTable; //the result table
	//build the result table's attributes
	naturalTable.attributes = this->attributes;

	//combined attributes from input tables
	naturalTable.attributes.insert(naturalTable.attributes.begin(), joinTableAttrs.begin(), joinTableAttrs.end());
	for (int i = 0; i < sharedAttrs.size(); i++) {
		//remove duplicate shared attributes from the combined attr list (erase-remove idiom)
		naturalTable.attributes.erase(remove(naturalTable.attributes.begin(),
		naturalTable.attributes.end(), sharedAttrs.at(i)), naturalTable.attributes.end());
	}
	//add the (non-duplicated) shared attributes
	naturalTable.attributes.insert(naturalTable.attributes.begin(), sharedAttrs.begin(), sharedAttrs.end());
	//create attribute vectors for input tables which exclude shared values
	vector<string> argRemainders = joinTableAttrs;
	for (int i = 0; i < sharedAttrs.size(); i++) {
		//remove shared attributes from the argument attr list (erase-remove idiom)
		argRemainders.erase( remove(argRemainders.begin(), argRemainders.end(), sharedAttrs.at(i)), argRemainders.end() );
	}
	//create the new records and add them to the result table
	for (pair<string, Record> callerEntry : this->records) {
		for (pair<string, Record> argEntry : joinTable.records) {
			if (checkAllValsMatch(sharedAttrs, callerEntry.second, argEntry.second)) {
				//create a record for tne result table if all values match for a shared attribute

				//at this point, result record should have all shared key val pairs, and all key val pairs from caller table 
				Record resultRecord = callerEntry.second;
				resultRecord.setRecordKey(callerEntry.second.getRecordKey()
									 + " " + argEntry.second.getRecordKey());		 
				//add remaining attrs from the arg table
				for (int i = 0; i < argRemainders.size(); i++) {
					resultRecord.addAttribute(argRemainders.at(i), argEntry.second.getValue(argRemainders.at(i)));
				}
				naturalTable.addRecord(resultRecord);
			}
		}
	}

	//overwrite the caller's table
	this->attributes = naturalTable.attributes;
	this->records = naturalTable.records;
} 
		
string Table::minAttribute(string attribute) {
	//at start of func, current min value is the beginning of the table
	string currMin = records.begin()->second.getValue(attribute);
	//check the data type of the attribute
	if (!checkAllValsNumeric(records, attribute)) {
		//if all not all values are numeric, we must compare by string
		for (pair<string, Record> currentEntry : records) {
			string currVal = currentEntry.second.getValue(attribute);
			if (currVal < currMin) {
				currMin = currVal;
			}
		}
		return currMin;
	}

	//if all values are numeric
	for (pair<string, Record> currentEntry : records) {
		string currVal = currentEntry.second.getValue(attribute);

		//check if current value is floating point string
		if ((helper.stringIsNumeric(currVal)) && (helper.stringContainsPoint(currVal))) {
			if (stod(currVal) < stod(currMin)) {
				//overwrite the current minimum if we find a smaller double str
				currMin = currVal; 
			}
		}
		//check if current value is integer string
		if ((helper.stringIsNumeric(currVal)) && (!helper.stringContainsPoint(currVal))) {
			if (stoi(currVal) < stoi(currMin)) {
				//overwrite the current minimum if we find a smaller int string
				currMin = currVal; 
			}	
			
		}
	}
	return currMin;
}
string Table::maxAttribute(string attribute) {
	//at start of func, current max value is the beginning of the table
	string currMax = records.begin()->second.getValue(attribute);
	//check the data type of the attribute
	if (!checkAllValsNumeric(records, attribute)) {
		//if all not all values are numeric, we must compare by string
		for (pair<string, Record> currentEntry : records) {
			string currVal = currentEntry.second.getValue(attribute);
			if (currVal > currMax) {
				currMax = currVal;
			}
		}
		return currMax;
	}

	//if all values are numeric
	for (pair<string, Record> currentEntry : records) {
		string currVal = currentEntry.second.getValue(attribute);

		//check if current value is floating point string
		if ((helper.stringIsNumeric(currVal)) && (helper.stringContainsPoint(currVal))) {
			if (stod(currVal) > stod(currMax)) {
				//overwrite the current minimum if we find a smaller double str
				currMax = currVal; 
			}
		}
		//check if current value is integer string
		if ((helper.stringIsNumeric(currVal)) && (!helper.stringContainsPoint(currVal))) {
			if (stoi(currVal) > stoi(currMax)) {
				//overwrite the current minimum if we find a smaller int string
				currMax = currVal; 
			}	
			
		}
	}
	return currMax;
}

string Table::getKey() {
	return this->key;
}

bool Table::checkSharedAttribute(const vector<string> &a, const vector<string> &b) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (a.at(i) == b.at(j)) {
				return true; //if an attribute is shared between a and b, true
			}
		}
	}
	return false;
}

bool Table::checkAllValsMatch(vector<string> &sharedAttrs, Record &a, Record &b) {
	for (int i = 0; i < sharedAttrs.size(); i++) {
		if (a.getValue(sharedAttrs.at(i)) != b.getValue(sharedAttrs.at(i))) {
			return false; //if there is a mismatch 
		}
	}
	return true; //if all values of a and b match for the shared attributes
}

bool Table::checkAllValsNumeric(unordered_map<string, Record> records, string attribute) {
	for (pair<string, Record> currentEntry : records) {
		if (!helper.stringIsNumeric(currentEntry.second.getValue(attribute))) {
			return false;
		}
	}
	return true;
}
