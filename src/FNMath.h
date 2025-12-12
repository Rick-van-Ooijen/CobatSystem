#ifndef FNMATH_H
#define FNMATH_H

#include <godot_cpp/classes/Node.hpp>
//#include <godot_cpp/classes/Object.hpp>
#include <string>
#include <sstream>
#include <vector>

#include <functional>
#include <unordered_map>
#include <godot_cpp/variant/utility_functions.hpp>

#include "charSheet.h"

namespace godot {


#define rollCommand(data, numOutputs, strOutputs, values, manager) \
	/*UtilityFunctions::print("roll function activated");*/ \
	/*UtilityFunctions::print((values).c_str());*/ \
	size_t pos = values.find(", "); \
	int min = 0; \
	if (!(min = stoi(values.substr(0, pos)))) \
	{ \
		min = 2; \
		} \
		\
		int max = stoi(values.substr(pos + 2)); \
		int result = min + (rand() % (max - min)); \
		\
		bool found = false; \
		for (size_t i = 0; i < data.numVec.size(); i++) \
	{ \
		if (data.numVec[i].name == "fOut") \
		{ \
			data.numVec[i].value = result; \
		} \
	} \
	if (!found) \
	{ \
		num newNum = num(); \
		newNum.set("fOut", result); \
		data.numVec.push_back(newNum); \
	}

#define changevarCommand(data, numOutputs, strOutputs, values, manager) \
    UtilityFunctions::print("changevar function activated");


#define addCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 1){\
	\
    int result = numbers[0] + numbers[1]; \
	\
    num newNum = num(); \
    newNum.set(strings[0], result); \
    data.numVec.push_back(newNum);\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function add"); \
	}



#define subtractCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 1){\
	\
    int result = numbers[0] - numbers[1]; \
	\
    num newNum = num(); \
    newNum.set(strings[0], result); \
    data.numVec.push_back(newNum);\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function subtract"); \
	}

#define multiplyCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 1){\
	\
    int result = numbers[0] * numbers[1]; \
	\
    num newNum = num(); \
    newNum.set(strings[0], result); \
    data.numVec.push_back(newNum);\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function multiply"); \
	}


#define divideCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 1){\
	\
    int result = numbers[0] / numbers[1]; \
	\
    num newNum = num(); \
    newNum.set(strings[0], result); \
    data.numVec.push_back(newNum);\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function divide"); \
	}


#define addSetCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 2){\
	\
    int result = numbers[0] + numbers[1]; \
	\
	for (size_t i = 0; i < manager->units.size(); i++)\
	{\
		if (manager->units[i]->name == strings[0])\
		{\
			for (size_t j = 0; j < manager->units[i]->numVec.size(); j++)\
			{\
				if (manager->units[i]->numVec[j].name == strings[1])\
				{\
					manager->units[i]->numVec[j].value = result;\
					manager->units[i]->ProcessModifiers();\
				}\
			}\
		}\
	}\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function addSet"); \
	}


#define subtractSetCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 2){\
	\
    int result = numbers[0] - numbers[1]; \
	\
	\
	for (size_t i = 0; i < manager->units.size(); i++)\
	{\
		if (manager->units[i]->name == strings[0])\
		{\
			for (size_t j = 0; j < manager->units[i]->numVec.size(); j++)\
			{\
				if (manager->units[i]->numVec[j].name == strings[1])\
				{\
					manager->units[i]->numVec[j].value = result;\
					manager->units[i]->ProcessModifiers();\
				}\
			}\
		}\
	}\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function subtractSet"); \
	}


#define multiplySetCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 2){\
	\
    int result = numbers[0] * numbers[1]; \
	\
	\
	for (size_t i = 0; i < manager->units.size(); i++)\
	{\
		if (manager->units[i]->name == strings[0])\
		{\
			for (size_t j = 0; j < manager->units[i]->numVec.size(); j++)\
			{\
				if (manager->units[i]->numVec[j].name == strings[1])\
				{\
					manager->units[i]->numVec[j].value = result;\
					manager->units[i]->ProcessModifiers();\
				}\
			}\
		}\
	}\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function multiplySet"); \
	}


#define divideSetCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(numbers.size() >= 2 && strings.size() >= 2){\
	\
    int result = numbers[0] / numbers[1]; \
	\
	\
	for (size_t i = 0; i < manager->units.size(); i++)\
	{\
		if (manager->units[i]->name == strings[0])\
		{\
			for (size_t j = 0; j < manager->units[i]->numVec.size(); j++)\
			{\
				if (manager->units[i]->numVec[j].name == strings[1])\
				{\
					manager->units[i]->numVec[j].value = result;\
					manager->units[i]->ProcessModifiers();\
				}\
			}\
		}\
	}\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function divideSet"); \
	}










}
#endif