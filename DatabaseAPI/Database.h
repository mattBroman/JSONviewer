#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <exception>

class KeyNotFound : public std::exception {
	public: 
		const char* what() const throw();
};
class AttributeNotFound : public std::exception {
	public: 
		const char* what() const throw();
};
class AlreadyDefined : public std::exception{	
	public: 
		const char* what() const throw();
};
class InvalidRecord : public std::exception{	
	public: 
		const char* what() const throw();
};
class InvalidJoin : public std::exception{	
	public: 
		const char* what() const throw();
};
class NullKey : public std::exception{	
	public: 
		const char* what() const throw();
};
class BadSelectInput : public std::exception{	
	public: 
		const char* what() const throw();
};
class NotAnOperator : public std::exception{	
	public: 
		const char* what() const throw();
};
class UnableToCreateTree : public std::exception{	
	public: 
		const char* what() const throw();
};
class UnbalancedParenthese : public std::exception{
	public:
		const char* what() const throw();
};

class Helper {
	public:
		bool stringIsNumeric(std::string input);
		bool stringContainsPoint(std::string input);
};

class Record{
	
	//changed to a vector of tuples in order to prerve ordering at cost of lookup ease and runtime
	std::vector<std::tuple<std::string, std::string>> attributes;
	std::string key;		//for identification in table
	
	public:
		Record(std::string key, std::vector<std::string> attr);		//constructor
		
		
		int findSize();		//Returns the size of the Record
		std::string getRecordKey();
		std::vector<std::string> listAttributes();
		std::string getValue(std::string key);
		void setRecordKey(std::string key);
		void set(std::string key, std::string value);	//Inserts data at the location of the key
		void addAttribute(std::string key, std::string value = "");
		void deleteAttribute(std::string key);
};

class Table {
	private:
		std::unordered_map<std::string, Record> records;		//contains records
		std::vector<std::string> attributes;					//a list of the current attributes in the table
		std::string key;										//unique ID for the current table
		Helper helper;
		//PRIVATE HELPER FUNCTIONS

		//check if two attribute lists share a common attribute
		bool checkSharedAttribute(const std::vector<std::string> &a, const std::vector<std::string> &b);

		//used within natural join; check if both records have same value for ALL shared attributes in a table
		bool checkAllValsMatch(std::vector<std::string> &sharedAttrs, Record &a, Record &b);
		bool checkAllValsNumeric(std::unordered_map<std::string, Record> records, std::string attribute);
	public:

		Table();
		Table(std::vector<std::string> attributes);					//attribute constructor
		
		void addAttribute(std::string newAttribute);	//add attribute to table
		void deleteAttribute(std::string attribute);	//delete attribute from table 
		void addRecord(Record& record);					//insert record to table 
		std::vector<std::string> listAttributes();			//list attributes

		int countAttribute(std::string attribute);		//find number of defined values for the requested attribute
		int getSize();
		std::string getKey();									//number of records in the table 
								
		std::unordered_map<std::string, Record>::iterator getRecord(bool begin);
		std::unordered_map<std::string, Record>::iterator getRecord(std::string key);
		
		void specifyKey(std::string key);			    //specify the table's identifier for database use
		void crossJoin(Table joinTable);		        //combine tables
		void naturalJoin(Table joinTable);   			//combine natural
		
		std::string minAttribute(std::string attribute); //find min attribute
		std::string maxAttribute(std::string attribute); //find max attribute
};

struct ParseTreeNode {
	ParseTreeNode();
	~ParseTreeNode();
	ParseTreeNode(std::string input);
	ParseTreeNode* up;
	ParseTreeNode* left;
	ParseTreeNode* right;
	ParseTreeNode* down;
	std::string data;
	void addRightNode(std::string data);
	void addLeftNode(std::string data);
	void addDownNode(std::string data);
};

class Database {
	public:
		/*-----------------------------------------------*
		 *   visable public members of the databaseAPI   *
		 *-----------------------------------------------*/
		Database();
		void addTable(std::string key, Table table);
		void dropTable(std::string tableName);
		std::vector<std::string> listTables();
		std::vector<Table> getTables();
		Table query(std::string select, std::string from, std::string where);
		
	private:
		/*-------------------------------------------------*
		 * tables are stored in a hash table inorder to    *
		 * allow a constant lookup time in addtion to allo-*
		 * wing us to search the tables by name with string*
		 *-------------------------------------------------*/
		std::unordered_map<std::string, Table> tables;
		ParseTreeNode* parseTree;
		Helper help;
		std::vector<std::string> selectSeparator(const std::string& input);
		void removeHeadWhiteSpace(std::string& input);
		void removeTailWhiteSpace(std::string& input);
		void tidyInput(std::string& input);
		void parse(const std::string& input);
		std::vector<std::string> tokenizeInput(const std::string& input);
		bool stringIsWhiteSpace(const std::string& operand);
		void buildParseTree(std::vector<std::string> tokens);
		int precidence(const std::string& input);
		bool recordIsValid(ParseTreeNode* node, Record& record);
		bool isOperator(const std::string& input, int loc);
		std::string whatOperator(const std::string& input, int loc);
};
