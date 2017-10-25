/*Record Class Template
 */
#include "Database.h"
using namespace std;

//Empty Constructor
Record::Record(string key, vector<string> attr){
	this -> key = key;
	for(int i = 0; i < attr.size(); i++){
		tuple<string, string> keyPair;
		get<0>(keyPair) = attr.at(i);	
		attributes.push_back(keyPair);
	}
}

//Returns size of Record
int Record::findSize(){
	return attributes.size();
}

vector<string> Record::listAttributes(){
	vector<string> keyVector;
	for (int i = 0; i < attributes.size(); ++i){
		keyVector.push_back(get<0>(attributes.at(i)));
	}
	return keyVector;
}

string Record::getRecordKey(){
	return key;
}
//Returns value at the location of the key passed in
string Record::getValue(string key){
	for (int i = 0; i < attributes.size(); ++i){
		if (get<0>(attributes.at(i))== key){
			return get<1>(attributes.at(i));
		}
	}
	throw KeyNotFound();
}
//Redifine unique identification for a Record
void Record::setRecordKey(string key){
	this -> key = key;
}

//Set the value at a certain key
void Record::set(string key, string value){
	int i = 0;
	while (i != attributes.size()){
		if (get<0>(attributes.at(i)) == key) {
			get<1>(attributes.at(i)) = value;
			return;
		}
		++i;
	}
	throw KeyNotFound();
	
}
//Pushes new attribute tuple onto the vector of attributes
void Record::addAttribute(string key, string value){
	tuple<string, string> pair = tuple<string, string>(key, value);
	//tuple<string key, string value> pair;
	attributes.push_back(pair);
}
//Removes an attribute from the vector of attributes
void Record::deleteAttribute(std::string key){
	int i = 0;
	while (get<0>(attributes.at(i)) != key && i != attributes.size()){
		++i;
	}
	//key if no results were found
	if (get<0>(attributes.at(i)) != key){
		throw KeyNotFound();
	}
	//remove attribute at location specfied by key
	//attributes.erase(remove(attributes.begin(), attributes.end(), i), attributes.end());
	attributes.erase(attributes.begin() + i);
}
