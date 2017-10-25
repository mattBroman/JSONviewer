#include "GUI.h"
using namespace std;

//adding more agurments for table join callbacks
struct menu_args {
	GUI* gui;
	string* table1;
	bool isNaturalJoin;
	
	menu_args(GUI* _gui, string* _table1, bool _isNatural) {
		gui = _gui;
		table1 = _table1;
		isNaturalJoin = _isNatural;
	}
};

GUI::GUI(Database* database)  : Fl_Double_Window(1280, 720, "JSON Viewer") {
	this->database = database; //set the database
	this->displayTable = nullptr;
	this->buttonX = 0;
	this->buttonY = 660;
	//for dynamic button names
	this->numCrossJoins = 0;
	this->numNaturalJoins = 0;
	
	//create the user input widgets 
	this->selectInputBox = new Fl_Input(0, 700, 590, 20);
	this->whereInputBox = new Fl_Input(590, 700, 590, 20);
	this->joinInputBox = new Fl_Input(200, 680, 1080, 20);
	this->submitInputBtn = new Fl_Button(1180, 700, 100, 20, "Search");
	this->naturalJoinBtn = new Fl_Menu_Button(0, 680, 100, 20, "Natural Join");
	this->crossJoinBtn = new Fl_Menu_Button(100, 680, 100, 20, "Cross Join");

	//iterate over the database tables and add them as entries to the join buttons
	vector<string> allTableNames = database->list_Tables();
	for (int i = 0; i < allTableNames.size(); i++) {
		string* currTable = new string(allTableNames.at(i));
		crossJoinBtn->add(currTable->c_str(), 0, tableJoinCallback, new menu_args(this, currTable, false), 0);
		naturalJoinBtn->add(currTable->c_str(), 0, tableJoinCallback, new menu_args(this, currTable, true), 0);
	}
	
	//automaticly create the default buttons
	makeButton("Businesses");
	makeButton("Users");
	makeButton("Reviews");
	makeButton("Check In's");
	makeButton("Tips");
	
	this->selector = new InputSelector();
	
	submitInputBtn->callback(submitButtonCallback, this); //register callback 
	
	this->show();
}

//dynamically make new print table Btns
void GUI::makeButton(const char* label) {
	if (this->buttonX > 1180) {
		this->buttonX = 0;
		this->buttonY -= 20;
	}
	PrintTableBtn* pBtn = new PrintTableBtn(buttonX, buttonY, 100, 20, label);
	pBtn->callback(printBtnCallback, this);
	printBtns.push_back(pBtn);
	this->buttonX += 100;

	this->add(pBtn);
	this->redraw();
}

//callback for searching the displayed table
void submitButtonCallback(Fl_Widget* w, void* v) {
	//cast pointers so we can interact with the window/database 
	Fl_Button* submitInputBtn = (Fl_Button*)w;
	GUI* window = (GUI*)v;
	string select = window->selectInputBox->value();
	string where = window->whereInputBox->value();
	//querys break here so set a default
	if (stringIsWhiteSpace(where) || where == "") {
		where = "True";
	}
	if (stringIsWhiteSpace(select) || select == ""){
		select = "*";
	}
	//avoids a segfault
	if (window->displayTable == nullptr) return;
	string from = string(window->displayTable->name);
	//avoids thrown error
	if (from == "") return;
	Database* database = window->database;
	
	Table* queryTable = database->Query(select, from, where);
	printTable(queryTable, window, window->displayTable->name);
}

void printBtnCallback(Fl_Widget* w, void* v) {
	PrintTableBtn* printBtn = (PrintTableBtn*)w;
	GUI* window = (GUI*)v;
	Database* database = window->database;
	
	string from = string(printBtn->tableName);
	Table* queryTable = database->Query("*", from, "");
	printTable(queryTable, window, printBtn->tableName);
} 

void printTable(Table* table, GUI* window, const char* name) {
	if (window->displayTable != nullptr){
		Fl::delete_widget(window->displayTable);
	}
	window->displayTable = new SQLTable(0, 20, 1280, 600, name, table);
	window->add(window->displayTable);
	window->displayTable->show();
	window->redraw();
}

void tableJoinCallback(Fl_Widget* w, void* v) {
	menu_args* args = (menu_args*)v;
	GUI* window = args->gui;

	if (window->displayTable == nullptr) return;
	
	string* joinTableName = args->table1;
	string* baseTableName = new string(window->displayTable->name);
	string key;
	bool isNaturalJoin = args->isNaturalJoin;
	

	if (isNaturalJoin) {
		try{
		key = string(window->joinInputBox->value());
		if (stringIsWhiteSpace(key) || key == "") return;
		Table* joinTable = window->database->Query("*", *joinTableName, "");
		Table* baseTable = window->database->Query("*", *baseTableName, "");

		joinTable->set_key(key);
		Table* naturalTable = joinTable->natural_join(baseTable, joinTable);
		string* naturalTableName = new string("nat " + to_string(window->numNaturalJoins));
		window->numNaturalJoins++;
		window->database->add_Table(naturalTable, *naturalTableName);

		window->makeButton(naturalTableName->c_str());
		window->naturalJoinBtn->add(naturalTableName->c_str(), 0, tableJoinCallback, new menu_args(window, naturalTableName, true), 0);
		}
		catch(...){
			return;
		}
	
	}
	else {
		Table* joinTable = window->database->Query("*", *joinTableName, "");
		Table* baseTable = window->database->Query("*", *baseTableName, "");
		Table* crossTable = joinTable->cross_join(baseTable, joinTable);

		string* crossTableName = new string("cross " + to_string(window->numCrossJoins));
		window->numCrossJoins++;
		window->database->add_Table(crossTable, *crossTableName);

		window->makeButton(crossTableName->c_str());
		window->crossJoinBtn->add(crossTableName->c_str(), 0, tableJoinCallback, new menu_args(window, crossTableName, false), 0);
	}
	
}
//utility function
bool stringIsWhiteSpace(string data) {
	for (int i = 0; i < data.size(); i++) {
		if (data.at(i) != ' ') {
			return false;
		}
	}
	return true;
}
