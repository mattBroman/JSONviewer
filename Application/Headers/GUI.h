#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu.H>
#include <FL/fl_draw.H>
#include "PrintTableBtn.h"
#include "Database.h"
#include "SQLTable.h"
#include "InputSelector.h"
/* the GUI class is a graphical frontend to our database;
 * it handles basic user input as well as rendering of tables */

class GUI : public Fl_Double_Window {
	public:
		GUI(Database* database);
		int buttonX;
		int buttonY;

		int numCrossJoins;
		int numNaturalJoins;
		
		//void commandHandler();
		vector<Fl_Button*> printBtns;
		
		Fl_Input* selectInputBox;  //text box for user commands/queries
		Fl_Input* whereInputBox;
		Fl_Input* joinInputBox;
		Fl_Button* submitInputBtn;  //button to submit commands
		
		Fl_Menu_Button* naturalJoinBtn;  //drop-down buttons for table joins
		Fl_Menu_Button* crossJoinBtn;
		
		void makeButton(const char* label);
		SQLTable* displayTable;		//FLTK table for displaying queries
		Database* database;			//need database access to render tables
		InputSelector* selector;	//To parse the user input
				
};

struct submitCallbackArgs {
	Fl_Input* userInputBox;
	Database* database;
};

void submitButtonCallback(Fl_Widget* w, void* v);
void printTable(Table* table, GUI* window, const char* name);
void printBtnCallback(Fl_Widget* w, void* v);
void tableJoinCallback(Fl_Widget* w, void* v);
void handle_menu(Fl_Widget *w, void *v);
bool stringIsWhiteSpace(string data);
