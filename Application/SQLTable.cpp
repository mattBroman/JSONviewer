#include "SQLTable.h"
using namespace std;

SQLTable::SQLTable(int X, int Y, int W, int H, const char* L, Table* renderTable) : Fl_Table_Row(X, Y, W, H, L) {
	this->renderTable = renderTable;
	this->name = L;

	int numCols = renderTable->get_attributes().size();
	int numRows = renderTable->get_size();

	//build the 2d vector for cell data
	for (int i = 0; i < numRows; i++) {
		Record* tempRecord = renderTable->get_record(i);
		vector<string> tempRecordVals;
		for (int j = 0; j < tempRecord->get_size(); j++) {
			tempRecordVals.push_back(tempRecord->get_entry(j));
		}
		tableData.push_back(tempRecordVals);
	}

	//define row count/row attributes
	rows(numRows);
	row_header(1);	//enable row headers
	row_height_all(25);
	row_resize(1);	//allow resizing

	//deffine column count/column attributes
	cols(numCols);
	col_header(1);
	col_width_all(160);
	col_resize(1);
	end();
}

SQLTable::~SQLTable() {}

void SQLTable::drawHeader(string s, int X, int Y, int W, int H) {
	fl_push_clip(X, Y, W, H);

	fl_draw_box(FL_EMBOSSED_BOX, X, Y, W, H, row_header_color());
	fl_color(FL_BLACK);
	fl_draw(s.c_str(), X, Y, W, H, FL_ALIGN_CENTER);

	fl_pop_clip();
}

void SQLTable::drawData(string s, int X, int Y, int W, int H) {
	fl_push_clip(X, Y, W, H);

	fl_color(FL_WHITE);
	fl_rectf(X,Y,W,H);

	fl_color(FL_GRAY0);
	fl_draw(s.c_str(), X,Y,W,H, FL_ALIGN_CENTER);

	fl_color(color()); fl_rect(X,Y,W,H);
	
	fl_pop_clip();
}

void SQLTable::draw_cell(TableContext context, int ROW, int COL, int X,
					   int Y, int W, int H) {
	string data = "";
	switch (context) {
		case CONTEXT_STARTPAGE:
			fl_font(FL_COURIER, 16);
			return;

		case CONTEXT_COL_HEADER:
			fl_font(FL_COURIER, 16);
			data = renderTable->get_attributes().at(COL);
			drawHeader(data, X, Y, W, H);
			return;

		case CONTEXT_CELL:
			fl_font(FL_COURIER, 12);
			data = tableData.at(ROW).at(COL);
			drawData(data, X, Y, W, H);
			return;
		default:
			return;
	}
}
