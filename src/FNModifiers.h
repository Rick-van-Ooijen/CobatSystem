#ifndef FNMODIFIERS_H
#define FNMODIFIERS_H

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

#define makeModifierCommand(data, numOutputs, strOutputs, values, manager) \
	std::vector<int> numbers; \
	std::vector<std::string> strings; \
	ReadValues(numbers, strings, values); \
	if(strings.size() >= 1){\
	\
	std::string targetName = strings[0]; \
	Modifier newModifier; \
	for (size_t i = 1; i < strings.size(); i++) \
		{ /*<type-name-modType-value*/ \
			bool foundEnd = false; \
			std::string modifierData[4]; \
			strings[i].erase(0,1); \
			for (size_t j = 0; j < 4; j++) \
			{ \
				size_t pos = strings[i].find("-"); \
				if (pos == std::string::npos){ \
					foundEnd = true; \
				} \
				modifierData[j] = strings[i].substr(0, pos); \
				strings[i] = strings[i].substr(pos + 1); \
			} \
			std::string dataType = modifierData[0]; \
			std::string targetName = modifierData[1]; \
			int modType = ReadInt(modifierData[2]); \
			switch(dataType[0]){ \
				case 'i': \
				{ \
					numMod newNumMod; \
					newNumMod.name = targetName; \
					newNumMod.modType = modType; \
					newNumMod.value = ReadInt(modifierData[3]); \
					/*UtilityFunctions::print("adding modifier:"); \
					UtilityFunctions::print("-datatype: ", dataType.c_str()); \
					UtilityFunctions::print("-targetName: ", targetName.c_str()); \
					UtilityFunctions::print("-modType: ", modifierData[2].c_str()); \
					UtilityFunctions::print("-value: ", modifierData[3].c_str());*/ \
					newModifier.numModifiers.push_back(newNumMod); \
					break; \
				} \
				case 's': \
				{ \
					strMod newStrMod; \
					newStrMod.name = targetName; \
					newStrMod.modType = modType; \
					newStrMod.value = ReadString(modifierData[3]); \
					/*UtilityFunctions::print("adding modifier:"); \
					UtilityFunctions::print("-datatype: ", dataType.c_str()); \
					UtilityFunctions::print("-targetName: ", targetName.c_str()); \
					UtilityFunctions::print("-modType: ", modifierData[2].c_str()); \
					UtilityFunctions::print("-value: ", modifierData[3].c_str());*/ \
					newModifier.strModifiers.push_back(newStrMod); \
					break; \
				} \
			} \
		} \
	for(size_t i = 0; i < (*manager).units.size(); i++) \
	{ \
		CharSheet* currentUnit = (*manager).units[i]; \
		if((*currentUnit).name == targetName) \
		{ \
			(*currentUnit).modVec.push_back(newModifier); \
			(*currentUnit).ProcessModifiers(); \
			return; \
		} \
		else{ \
			UtilityFunctions::print("invalid unit"); \
			UtilityFunctions::print((*currentUnit).name.c_str()); \
			UtilityFunctions::print(targetName.c_str()); \
		} \
	}\
	}\
	else{\
		UtilityFunctions::print("ERROR: not enough inputs for function makeModifier"); \
	}




}
#endif