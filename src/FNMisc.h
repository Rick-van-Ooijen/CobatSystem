#ifndef FNMISC_H
#define FNMISC_H

#include <godot_cpp/classes/Node.hpp>
//#include <godot_cpp/classes/Object.hpp>
#include <string>
#include <sstream>
#include <vector>

#include <functional>
#include <unordered_map>
#include <map>
#include <godot_cpp/variant/utility_functions.hpp>

#include "charSheet.h"

namespace godot {

#define readOutCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
    for (int currentNumber : numbers){ \
		UtilityFunctions::print(currentNumber); \
	} \
	for (std::string currentString : strings){ \
		UtilityFunctions::print(currentString.c_str()); \
	} \
	num newNum = num(); \
	newNum.set(strings[0], numbers[0]); \
	numOutputs.push_back(newNum); \
	UtilityFunctions::print("numOutputs"); \
	for (num currentNum : numOutputs){ \
		UtilityFunctions::print("<-entry->"); \
		UtilityFunctions::print(currentNum.name.c_str()); \
		UtilityFunctions::print(currentNum.value); \
		UtilityFunctions::print("<-->"); \
	}

#define triggerCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
\
	for (size_t i = 0; i < manager->units.size(); i++) \
	{\
		std::multimap<std::string, std::string> unitTriggers = (manager->units[i]->triggers); \
		auto it = unitTriggers.begin(); \
		std::string key = strings[0]; \
		while (it != unitTriggers.end() && it->first == key) { \
			manager->actionQue.push_back(it->second); \
			it++; \
		} \
\
\
\
		/*for (size_t j = 0; j < units[i]->modVec.size(); j++)*/ \
		/*{*/\
			/*std::multimap<std::string, std::string> modTriggers = (units[i]->modVec[j].triggers)*/\
			/*(*units[i]).modVec;*/\
\
		/*}*/\
	}\


	//check trigger list
	//if find, add to manager.actionQue

	//loop throug modifiers
	//check that trigger list
	//if find, add to manager.actionQue

//loop through units and modifiers
//find triggers (new var)
//runt txt file, add to que for manager, so it can run next.
//file io in here if needed, or tie in function needed on script gd side


}
#endif