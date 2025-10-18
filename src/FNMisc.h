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




}
#endif