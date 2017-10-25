#include "PrintTableBtn.h"
using namespace std;

PrintTableBtn::PrintTableBtn(int x, int y, int length, int height, const char* title) : Fl_Button(x, y, length, height, title){
	tableName = title;
}
