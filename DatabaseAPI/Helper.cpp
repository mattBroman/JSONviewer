#include "Database.h"
using namespace std;

bool Helper::stringIsNumeric(string input) {
	try {
		stoi(input);
	}
	catch(...) {
		return false; //if the conversion fails
	}
	return true;
}

bool Helper::stringContainsPoint(string input) {
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '.') {
			return true;
		}
	}
	return false;
}
