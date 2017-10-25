#include "Database.h"
using namespace std;

Database::Database() {
	
}

void Database::addTable(string key, Table table) {
	if (table.getKey() == "") throw NullKey();
	pair<string, Table> newPair(key, table);
	tables.insert(newPair);
}

void Database::dropTable(string tableName) {
	if (tables.find(tableName) == tables.end()) throw KeyNotFound();
	tables.erase(tableName);
}

vector<string> Database::listTables() {
	vector<string> returnVector;
	unordered_map<string, Table>::iterator it = tables.begin();
	while ( it != tables.end() ) {
		returnVector.push_back(it->first);
		it++;
	}
	return returnVector;
}

vector<Table> Database::getTables() {
	vector<Table> returnVector(tables.size());
	unordered_map<string, Table>::iterator it = tables.begin();
	int i = 0;
	while ( it != tables.end() ) {
		returnVector.at(i) = it->second;
		it++;
		i++;
	}
	return returnVector;
}

Table Database::query(string select, string from, string where) {
	
	if (tables.find(from) == tables.end()) throw KeyNotFound(); // table does not exist
	Table& searchTable = tables.find(from)->second;
	vector<string> selectedAtts = selectSeparator(select);
	parse(where);
	
	unordered_map<string, Record>::iterator it = searchTable.getRecord(true);
	Record& firstRecord = it->second;
	if (selectedAtts.at(0) == "*") {
		selectedAtts = firstRecord.listAttributes();
	}
	Table returnTable(selectedAtts);
	
	while (it != searchTable.getRecord(false)) {
		Record& currentRecord = it->second;
		if (recordIsValid(parseTree, currentRecord)) {
			Record newRecord(currentRecord.getRecordKey(), selectedAtts);
			for (int i = 0; i < newRecord.findSize(); i++) {
				newRecord.set(selectedAtts.at(i), currentRecord.getValue(selectedAtts.at(i)));
			}
			returnTable.addRecord(newRecord);
		}
		it++;
	}
	delete parseTree;
	return returnTable;
}



//------------------------------------------------------------------------------
//Private Parsing Functions
//used to seperate which atrributes to keep in the case multiple are passed into
//                   SELECT during a query
vector<string> Database::selectSeparator(const string& input) {
	int inputStart = 0;
	int inputLength = 0;
	string pushString;
	string starCheck = input;
	tidyInput(starCheck);
	vector<string> returnVector;
	
	while (inputLength + inputStart < input.size()) {
		if (input.at(inputLength + inputStart) == ',') {
			returnVector.push_back(input.substr(inputStart, inputLength));
			inputStart += (inputLength + 1);
			inputLength = 0;
		}
		else {
			inputLength++;
		}
	}
	returnVector.push_back(input.substr(inputStart));
	
	for (int i = 0; i < returnVector.size(); i++) {
		tidyInput(returnVector.at(i));
	
	}
	if (returnVector.size() == 0) throw BadSelectInput();
	string lastSelected = returnVector.at(returnVector.size() - 1);
	if (lastSelected.at(lastSelected.size() - 1) == ',') throw BadSelectInput();
	return returnVector;
}

//input tidying up, querys should idealy work with arbitary white space
//-----------------------------------------------------------------------------
void Database::removeHeadWhiteSpace(string& input) {
	int headSpace = 0;
	while (input.at(headSpace) == ' ') {
		headSpace++;
	}
	input = input.substr(headSpace);
}

void Database::removeTailWhiteSpace(string& input) {
	int tailSpace = input.size();
	while (input.at(tailSpace - 1) == ' ') {
		tailSpace--;
	}
	if (tailSpace != input.size()) {
		input = input.substr(0, tailSpace);
	}
}

void Database::tidyInput(string& input) {
	removeHeadWhiteSpace(input);
	removeTailWhiteSpace(input);
}
//-----------------------------------------------------------------------------/
//Parseing Tree for Where
void Database::parse(const string& input) {
	parseTree = new ParseTreeNode();
	vector<string> tokens = tokenizeInput(input);
	buildParseTree(tokens);
}

vector<string> Database::tokenizeInput(const string& input) {
	vector<string> returnVector;
	if(input == "") return returnVector;
	int inputStart = 0;
	int inputLength = 0;
	string modedInput = input;
	tidyInput(modedInput);
	string op;
	
	while (inputStart + inputLength < modedInput.size()) {
		if (isOperator(modedInput, inputStart + inputLength)) {
			string operand = modedInput.substr(inputStart, inputLength);
			op = whatOperator(modedInput, inputStart + inputLength);
			if (inputLength != 0 && !stringIsWhiteSpace(operand)) {
				returnVector.push_back(operand);
			}
			returnVector.push_back(op);
			inputStart += inputLength + op.size();
			inputLength = 0;
		}
		else {
			inputLength++;
		}
	}
	if (inputStart < modedInput.size()) {
		returnVector.push_back(modedInput.substr(inputStart));
	}
	
	for (int i = 0; i < returnVector.size(); i++) {
		tidyInput(returnVector.at(i));
	}
	return returnVector;
}

bool Database::stringIsWhiteSpace(const string& operand) {
	for (int i = 0; i < operand.size(); i++) {
		if (operand.at(i) != ' ') {
			return false;
		}
	}
	return true;
}

void Database::buildParseTree(vector<string> tokens) {
	ParseTreeNode* head;
	if (tokens.size() == 0) return;
	vector<string> postFixForm;
	stack<string> operators;
	stack<ParseTreeNode*> nodes;
	stack<string> operands;
	
	for (int i = 0; i < tokens.size(); i++) {
		if (!isOperator(tokens.at(i), 0)) {
			postFixForm.push_back(tokens.at(i));
		}
		else if (operators.empty()) {
			operators.push(tokens.at(i));
		}
		else if (tokens.at(i) == "(") {
			operators.push(tokens.at(i));
		}
		else if (precidence(tokens.at(i)) < precidence(operators.top())) {
			operators.push(tokens.at(i));
		}
		else if (tokens.at(i) == ")") {
			while (!operators.empty() && operators.top() != "(") {
				postFixForm.push_back(operators.top());
				operators.pop();
			}
			if(!operators.empty()) { 
				operators.pop();
			}
			else throw UnbalancedParenthese();
		}
		else {
			while(!operators.empty() && precidence(tokens.at(i)) >= precidence(operators.top())) {
				postFixForm.push_back(operators.top());
				operators.pop();
			}
			operators.push(tokens.at(i));
		}
	}
	while (!operators.empty()) {
		if (operators.top() == "(") throw UnbalancedParenthese();
		postFixForm.push_back(operators.top());
		operators.pop();
	}
	
	for (int i = 0; i < postFixForm.size(); i++) {
		if (!isOperator(postFixForm.at(i), 0)) {
			operands.push(postFixForm.at(i));
		}
		else if (postFixForm.at(i) != "AND" && postFixForm.at(i) != "OR" && postFixForm.at(i) != "NOT") {
			ParseTreeNode* node = new ParseTreeNode(postFixForm.at(i));
			head = node;
			if (operands.empty()) throw UnableToCreateTree();
			node->addRightNode(operands.top());
			operands.pop();
			if (operands.empty()) throw UnableToCreateTree();
			node->addLeftNode(operands.top());
			operands.pop();
			nodes.push(node);
		}
		else if (postFixForm.at(i) == "NOT") {
			ParseTreeNode* node = new ParseTreeNode(postFixForm.at(i));
			head = node;
			if (nodes.empty()) throw UnableToCreateTree();
			node->down = nodes.top();
			nodes.pop();
			nodes.push(node);
		}
		else {
			ParseTreeNode* node = new ParseTreeNode(postFixForm.at(i));
			head = node;
			if (nodes.empty()) throw UnableToCreateTree();
			node->right = nodes.top();
			nodes.pop();
			if (nodes.empty()) throw UnableToCreateTree();
			node->left = nodes.top();
			nodes.pop();
			nodes.push(node);
		}
	}
	
	parseTree = head;
}

int Database::precidence(const string& input) {
	if (input == "(" || input == ")") {
		return 100;
	}
	else if (input == "<" || input == ">" || input == "<=" ||
			 input == ">=" || input == "<>") {
		return 2;
	}
	else if (input == "NOT") {
		return 3;
	}
	else if (input == "AND") {
		return 4;
	}
	else if (input == "OR") {
		return 5;
	}
}

bool Database::recordIsValid(ParseTreeNode* node, Record& record) {
	string token = node->data;
	if (node->data == "") return true;
	if (token == "AND") {
		return recordIsValid(node->left, record) && recordIsValid(node->right, record);
	}
	else if (token == "OR") {
		return recordIsValid(node->left, record) || recordIsValid(node->right, record);
	}
	else if (token == "NOT") {
		return !recordIsValid(node->down, record);
	}
	else if (token == "=") {
		string attribute = node->left->data;
		string comp = node->right->data;
		return record.getValue(attribute).compare(comp) == 0;
	}
	else if (token == "<") {
		string attribute = node->left->data;
		string comp = node->right->data;
		if(help.stringIsNumeric(record.getValue(attribute)) && help.stringIsNumeric(comp)) {
			if (help.stringContainsPoint(record.getValue(attribute))) {
				return stof(record.getValue(attribute)) < stof(comp);
			}
			else {
				return stoi(record.getValue(attribute)) < stoi(comp);
			}
		}
		return record.getValue(attribute).compare(comp) < 0;
	}
	else if(token == ">") {
		string attribute = node->left->data;
		string comp = node->right->data;
		if(help.stringIsNumeric(record.getValue(attribute)) && help.stringIsNumeric(comp)) {
			if (help.stringContainsPoint(record.getValue(attribute))) {
				return stof(record.getValue(attribute)) > stof(comp);
			}
			else {
				return stoi(record.getValue(attribute)) > stoi(comp);
			}
		}
		return record.getValue(attribute).compare(comp) > 0;
	}
	else if(token == "<>") {
		string attribute = node->left->data;
		string comp = node->right->data;
		return record.getValue(attribute).compare(comp) != 0;
	}
	else if(token == "<=") {
		string attribute = node->left->data;
		string comp = node->right->data;
		if(help.stringIsNumeric(record.getValue(attribute)) && help.stringIsNumeric(comp)) {
			if (help.stringContainsPoint(record.getValue(attribute))) {
				return stof(record.getValue(attribute)) <= stof(comp);
			}
			else {
				return stoi(record.getValue(attribute)) <= stoi(comp);
			}
		}
		return record.getValue(attribute).compare(comp) <= 0;
	}
	else if(token == ">=") {
		string attribute = node->left->data;
		string comp = node->right->data;
		if(help.stringIsNumeric(record.getValue(attribute)) && help.stringIsNumeric(comp)) {
			if (help.stringContainsPoint(record.getValue(attribute))) {
				return stof(record.getValue(attribute)) >= stof(comp);
			}
			else {
				return stoi(record.getValue(attribute)) >= stoi(comp);
			}
		}
		return record.getValue(attribute).compare(comp) >= 0;
	}
	else throw NotAnOperator(); //NotVaild
}

bool Database::isOperator(const string& input, int loc) {
	if (input.at(loc) == '<' || input.at(loc) == '>' || input.at(loc) == '='
		|| input.at(loc) == '(' || input.at(loc) == ')') {
		return true;
	}
	else if (input.at(loc) == 'A' && loc + 2 < input.size()
			 && input.at(loc + 1) == 'N' && input.at(loc + 2) == 'D') {
		return true;
	}
	else if (input.at(loc) == 'O' && loc + 1 < input.size() && input.at(loc + 1) == 'R') {
		return true;
	}
	else if (input.at(loc) == 'N' && loc + 2 < input.size()
			 && input.at(loc + 1) == 'O' && input.at(loc + 2) == 'T') {
				return true;
	}
	else return false;
}

string Database::whatOperator (const string& input, int loc) {
	if (input.at(loc) == '<') {
		if (loc + 1 < input.size()) {
			if (input.at(loc + 1) == '>') {
				return "<>";
			}
			else if (input.at(loc + 1) == '=') {
				return "<=";
			}
		}
		return "<";
	}
	else if (input.at(loc) == '>') {
		if (loc + 1 < input.size() && input.at(loc + 1) == '=') {
			return ">=";
		}
		return ">";
	}
	else if (input.at(loc) == '=') {
		return "=";
	}
	else if (input.at(loc) == '(') {
		return "(";
	}
	else if (input.at(loc) == ')') {
		return ")";
	}
	else if (input.at(loc) == 'A' && loc + 2 < input.size()
			 && input.at(loc + 1) == 'N' && input.at(loc + 2) == 'D') {
		return "AND";
	}
	else if (input.at(loc) == 'O' && loc + 1 < input.size() && input.at(loc+1) == 'R') {
		return "OR";
	}
	else if (input.at(loc) == 'N' && loc + 2 < input.size()
			 && input.at(loc + 1) == 'O' && input.at(loc + 2) == 'T') {
		return "NOT";
	}
	else throw NotAnOperator(); //How
}
//-------------------------------------------------------------------------------
//Parseing Tree Functions.
ParseTreeNode::ParseTreeNode() {
	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	data = "";
}

ParseTreeNode::ParseTreeNode(string input) {
	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	data = input;
}

ParseTreeNode::~ParseTreeNode() {
	if (down != nullptr) {
		delete down;
	}
	if (left != nullptr) {
		delete left;
	}
	if (right != nullptr) {
		delete right;
	}
}

void ParseTreeNode::addLeftNode(string data) {
	ParseTreeNode* newNode = new ParseTreeNode(data);
	newNode->up = this;
	left = newNode;
}

void ParseTreeNode::addRightNode(string data) {
	ParseTreeNode* newNode = new ParseTreeNode(data);
	newNode->up = this;
	right = newNode;
}

void ParseTreeNode::addDownNode(string data) {
	ParseTreeNode* newNode = new ParseTreeNode(data);
	newNode->up = this;
	down = newNode;
}
