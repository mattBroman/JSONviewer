#include "Database.h"
using namespace std;

const char* KeyNotFound::what() const throw(){
	return "Given key was not found";
}

const char* AttributeNotFound::what() const throw() {
	return "The given attribute was not found";
}

const char* AlreadyDefined::what() const throw() {
	return "This key has already been defined";
}

const char* InvalidRecord::what() const throw() {
	return "Record and Table have mismatched attributes";
}

const char* InvalidJoin::what() const throw() {
	return "Tables cannot be joined";
}

const char* NullKey::what() const throw() {
	return "Cannot object with a null key";
}

const char* BadSelectInput::what() const throw() {
	return "Cannot run a query on these selected attributes";
}

const char* NotAnOperator::what() const throw() {
	return "Attempt to evaluate non operator token as an operator";
}

const char* UnableToCreateTree::what() const throw() {
	return "Input for where is bad, there are not enough or too many operands for the given operators is";
}

const char* UnbalancedParenthese::what() const throw() {
	return "the input for what has a different number of open and close parenthese"; 
}



