#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <string>
#include "Database.h"
#include "Table.h"

class PrintTableBtn : public Fl_Button {
	public: 
		const char* tableName;
		PrintTableBtn(int x, int y, int length, int height, const char * title);
};
