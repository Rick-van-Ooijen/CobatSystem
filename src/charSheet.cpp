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
	ClassDB::bind_method(D_METHOD("SetName", "input"), &CharSheet::SetName);
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

void CharSheet::SetName(String arg) {
	CharString temp = ((String)arg).utf8().get_data();
	char* value = (char*)(temp.get_data());
	name = std::string(value);
}

void CharSheet::ProcessModifiers() {

	std::vector<num> bufferNumVec = numVec;
	std::vector<str> bufferStrVec = strVec;

	for (size_t i = 0; i < modVec.size(); i++)
	{

	    std::vector<numMod> numMods = modVec[i].numModifiers;

		for (numMod currentMod : numMods)
		{
			int modifiedNumIndex = FindNum(bufferNumVec, currentMod.name);

			if(modifiedNumIndex !=99999){

				switch(currentMod.modType){
					case 0:
						{
							bufferNumVec[modifiedNumIndex].value += currentMod.value;
							break;
						}
					case 1:
						{
							bufferNumVec[modifiedNumIndex].value -= currentMod.value;
							break;
						}
					case 2:
						{
							bufferNumVec[modifiedNumIndex].value *= currentMod.value;
							break;
						}
					case 3:
						{
							bufferNumVec[modifiedNumIndex].value /= currentMod.value;
							break;
						}
	
	
					default:
						{
							break;
						}
				}
				

			}

		}

		
	    std::vector<strMod> strMods = modVec[i].strModifiers;
		
		for (strMod currentMod : strMods)
		{
			int modifiedStrIndex = FindStr(bufferStrVec, currentMod.name);

			bufferStrVec[modifiedStrIndex].value.append(currentMod.value.substr(1));
		}


	}
	

	modifiedNumVec.clear();
	for (size_t i = 0; i < bufferNumVec.size(); i++)
	{
		modifiedNumVec.push_back(bufferNumVec[i]);
	};

	modifiedStrVec.clear();
	for (size_t i = 0; i < bufferStrVec.size(); i++)
	{
		modifiedStrVec.push_back(bufferStrVec[i]);
	};



}

int CharSheet::FindNum(std::vector<num>& vector, std::string name)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i].name == name)
		{
			return i;
		}
	}

	return 99999;
}

int CharSheet::FindStr(std::vector<str>& vector, std::string name)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i].name == name)
		{
			return i;
		}
	}

	return 99999;
}


String CharSheet::PrintData() {
	
	std::string output = "";


	for (size_t i = 0; i < modifiedStrVec.size(); i++)
	{
		str current = modifiedStrVec.at(i);

		output.append(current.name + ": " + current.value + "\n");

		//UtilityFunctions::print((current.name).c_str(), ": ", (current.value).c_str());
	}

	for (size_t i = 0; i < modifiedNumVec.size(); i++)
	{
		num current = modifiedNumVec.at(i);

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