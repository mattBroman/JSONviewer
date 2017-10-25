#include "InputSelector.h"

InputSelector::InputSelector(){
	this->input = "";
}

void InputSelector::setInput(std::string _input){
	this->input = _input;
}

void InputSelector::checkInput(){
	regex_search(input, SMATCH, normal);
	
}

std::string InputSelector::smatchAt(int i){
	return this->SMATCH[i];
}
