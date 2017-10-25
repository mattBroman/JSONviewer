#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Record.h"
#include "Table.h"
#include "json.hpp"

class TableBuilder {
	private:
		int keyLoc;
		int maxRows;
		Record* currRecord;
		std::ifstream filestream;
		std::string filename;
		std::vector<std::string> keys;
		std::unordered_map<string, int> keyMappings;
		std::vector<Record*>* records;
		
		Record* makeRecord();
		bool isPrimative(nlohmann::json::iterator Jdata);
		void openFile();
		void closeFile();
		void setAttrIfNecessary(Table* checkTable, nlohmann::json Jdata);
		void flatten(nlohmann::json JSON);
		void flattenHelper(nlohmann::json::iterator Jdata);
		void addData(nlohmann::json::iterator Jdata, string value);
		void checkNewKey(string key);
		void addValueToRecord(string key, string value);
		
		string rawConvert(nlohmann::json::iterator data);
		string numberConvert(int data);
		string numberConvert(float data);
		string arrayConvert(nlohmann::json::iterator Jdata);
		
	public:
		TableBuilder(int limit);
		TableBuilder(std::string file, int limit);
		void setFilename(std::string name);
		Table* makeTable();
};
