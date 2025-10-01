#include "charSheet.h"
#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <cstring>
#include <iostream>

using namespace godot;

num::num() {}
num::~num() {}
void num::_bind_methods() {}

void num::set(std::string iName, int iValue) {
	name=iName; value=iValue;
}

str::str() {}
str::~str() {}
void str::_bind_methods() {}

void str::set(std::string iName, std::string iValue) {
	name=iName; value=iValue;
}



void CharSheet::_bind_methods() {

	ClassDB::bind_method(D_METHOD("InitializeValues", "input"), &CharSheet::InitializeValues);
	ClassDB::bind_method(D_METHOD("PrintData"), &CharSheet::PrintData);

}

CharSheet::CharSheet() {
//	myNumber = num(std::string("abc"), 7);
//	std::cout << myNumber.name << ": " << myNumber.value;
//	UtilityFunctions::print(myNumber.name.data(), myNumber.value);

}

void CharSheet::InitializeValues(String arg) {

	CharString temp = ((String)arg).utf8().get_data();
	char* value = (char*)(temp.get_data());
	std::string input = std::string(value);

	int state = 0;
	/* 0=initial
	1=str (strings)
	2=int (integers)*/

	std::istringstream stream(input);

	std::string line;

	while (std::getline(stream, line)) {
		// process each line
		UtilityFunctions::print("Line: ", line.c_str());


		if (line == "str") {state = 1;}
		else if (line == "int") {state = 2;}
		else {
			size_t pos = line.find(", ");
			if (pos != std::string::npos) {
				std::string name = line.substr(0, pos); // seperate attribute name and value
				std::string value = line.substr(pos + 2);

				switch(state) {
					case 1:
					{
						str newStr = str();
						newStr.set(name, value);
						strVec.push_back(newStr);
					}
					UtilityFunctions::print("adding some things");
					break;
					case 2:
					{
						num newNum = num();
						newNum.set(name, std::stoi(value));
						numVec.push_back(newNum);
						
					}
					break;
					default:
					UtilityFunctions::print("Error: line which is not a valid attribute processed in character sheet initialization");
				}

			}
		
		}


	}

	strVec.shrink_to_fit();
	numVec.shrink_to_fit();

}

void CharSheet::ProcessModifiers() {

	std::vector<num> bufferNumVec = numVec;
	std::vector<str> bufferStrVec = strVec;

	for (size_t i = 0; i < modVec.size(); i++)
	{

	    std::vector<numMod> numMods = modVec[i].numModifiers;

		for (numMod currentMod : numMods)
		{
			num* modifiedNum = FindNum(numVec, currentMod.name);

			if(modifiedNum){

				switch(currentMod.modType){
					case 0:
						{
							(*modifiedNum).value += currentMod.value;
						}
					case 1:
						{
							(*modifiedNum).value -= currentMod.value;
						}
					case 2:
						{
							(*modifiedNum).value *= currentMod.value;
						}
					case 3:
						{
							(*modifiedNum).value /= currentMod.value;
						}
	
	
					default:
						{
							//
						}
				}
				

			}

		}

		
	    std::vector<strMod> strMods = modVec[i].strModifiers;
		
		for (strMod currentMod : strMods)
		{
			str* modifiedStr = FindStr(bufferStrVec, currentMod.name);

			(*modifiedStr).name.append(currentMod.value);
		}


	}
	
	numVec.clear();
	numVec.resize(bufferNumVec.size());
	for (size_t i = 0; i < bufferNumVec.size(); i++)
	{
		modifiedNumVec.push_back(bufferNumVec[i]);
	};

	strVec.clear();
	strVec.resize(bufferStrVec.size());
	for (size_t i = 0; i < bufferStrVec.size(); i++)
	{
		modifiedStrVec.push_back(bufferStrVec[i]);
	};



}

num* CharSheet::FindNum(std::vector<num>& vector, std::string name)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i].name == name)
		{
			return &vector[i];
		}
	}

	return nullptr;
}

str* CharSheet::FindStr(std::vector<str>& vector, std::string name)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (vector[i].name == name)
		{
			return &vector[i];
		}
	}

	return nullptr;
}


String CharSheet::PrintData() {
	
	std::string output = "";


	for (size_t i = 0; i < strVec.size(); i++)
	{
		str current = strVec.at(i);

		output.append(current.name + ": " + current.value + "\n");

		//UtilityFunctions::print((current.name).c_str(), ": ", (current.value).c_str());
	}

	for (size_t i = 0; i < numVec.size(); i++)
	{
		num current = numVec.at(i);

		output.append(current.name + ": " + std::to_string(current.value) + "\n");

		//UtilityFunctions::print((current.name).c_str(), ": ", (current.value));
	}
	


	return String(output.c_str());

}

CharSheet::~CharSheet() {
	// Add your cleanup here.
}

void CharSheet::_process(double delta) {
	
}