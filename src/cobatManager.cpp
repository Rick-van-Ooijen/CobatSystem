#include "cobatManager.h"
#include <godot_cpp/core/class_db.hpp>
#include <vector>

#include <fstream>

using namespace godot;

ActionData::ActionData() {}
ActionData::~ActionData() {}

void CobatManager::_bind_methods() {

	ClassDB::bind_method(D_METHOD("RunSequence", "input"), &CobatManager::RunSequence);
	ClassDB::bind_method(D_METHOD("AddUnit", "input"), &CobatManager::AddUnit);

}

CobatManager::CobatManager() {
	// Initialize any variables here.
}

CobatManager::~CobatManager() {
	// Add your cleanup here.
}

void CobatManager::_process(double delta) {
	//
}


void CobatManager::RunSequence(String arg)
{
	CharString temp = ((String)arg).utf8().get_data();
	char* value = (char*)(temp.get_data());
	std::string input = std::string(value);

//input is one line
	std::istringstream stream(input);

	std::string line;

	ActionData data;
	std::vector<num> numOutputs;
	std::vector<str> strOutputs;

	while (std::getline(stream, line)) {
		// process each line

			size_t pos = line.find(": ");
			if (pos != std::string::npos) {
				std::string command = line.substr(0, pos); // seperate attribute name and value
				std::string values = line.substr(pos + 2);


			// use the command from the map
			auto func = commands.find(command);
			if (func != commands.end()) {
				func->second(data, numOutputs, strOutputs, values, this);
			}
			
			}
	}


}

void CobatManager::AddUnit(CharSheet* unit)
{
	units.push_back(unit);
}

// wip syntax
// first char of an arg is type
// i for integer
// s for string
// r for reference to exisitng variable

void CobatManager::ReadValues(std::vector<int>& numbers, std::vector<std::string>& strings, std::string values)
{
	
	bool foundEnd = false;

	while (!foundEnd)
	{


		size_t pos = values.find(", ");
		if (pos == std::string::npos){
			foundEnd = true;
		}
		
		std::string newValue = values.substr(0, pos); // seperate attribute name and value
		
		//make switch statement

		if (newValue[0] == 'i'){
			
			numbers.push_back(stoi(newValue.substr(1)));

			//UtilityFunctions::print("reading an integer");
		}
		else if (newValue[0] == 's'){
			strings.push_back(newValue.substr(1));

			//UtilityFunctions::print("reading a string");
		}
		else if (newValue[0] == 'r'){
			
			UtilityFunctions::print("reading a reference");
		}
		
		values = values.substr(pos + 2);
	}


}

std::string CobatManager::ReadString(std::string value)
{
	switch(value[0])
	{
		case 's':
		{
			return value;
			break;
		}
		case 'r':
		{
			UtilityFunctions::print("reading a reference");
			break;
		}
		default:
		{
			UtilityFunctions::print("error: readStr encounterd invalid input");
			break;
		}
	}
	return 0;
}



int CobatManager::ReadInt(std::string value)
{
	switch(value[0])
	{
		case 'i':
		{
			return stoi(value.substr(1));
			break;
		}
		case 'r':
		{
			UtilityFunctions::print("reading a reference");
			break;
		}
		default:
		{
			UtilityFunctions::print("error: readInt encounterd invalid input");
			break;
		}
	}
	return 0;

}





