#include <regex>

class InputSelector{
	private:
		//regex patterns
		std::regex normal { "SELECT\\s(.+)\\sFROM\\s(.+)\\sWHERE\\s(.*)" };
		std::string input;
		std::smatch SMATCH;
		
	public:
		InputSelector();
		void setInput(std::string _input);
		void checkInput();
		std::string smatchAt(int i);
};
