#include "cobatManager.h"
#include <godot_cpp/core/class_db.hpp>
#include <vector>

#include <fstream>

using namespace godot;

ActionData::ActionData() {}
ActionData::~ActionData() {}

void CobatManager::_bind_methods() {

	ClassDB::bind_method(D_METHOD("RunSequence", "input"), &CobatManager::RunSequence);

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

	while (std::getline(stream, line)) {
		// process each line

			size_t pos = line.find(": ");
			if (pos != std::string::npos) {
				std::string command = line.substr(0, pos); // seperate attribute name and value
				std::string values = line.substr(pos + 2);


			// use the command from the map
			auto func = commands.find(command);
			if (func != commands.end()) {
				func->second(data, values);
			}
			
			}
	}


}