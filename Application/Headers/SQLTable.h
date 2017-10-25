#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Table.H>
#include <FL/fl_draw.H>
#include "Table.h"

class SQLTable : public Fl_Table_Row {
	private:
		Table* renderTable;		//the SQL table we are rendering 
		vector<vector<std::string>> tableData;  //map the table's data to 2d vector for table printing
		
		//override FLTK's draw_cell function
		void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0,
					   int Y = 0, int W = 0, int H = 0);
		void drawData(std::string s, int X, int Y, int W, int H);
		void drawHeader(std::string s, int X, int Y, int W, int H);
		
	public:
		SQLTable(int X, int Y, int W, int H, const char* L = 0, Table* renderTable = nullptr);
		const char* name;
		~SQLTable();
};
