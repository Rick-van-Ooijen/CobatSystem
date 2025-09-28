#ifndef COBATMANAGER_H
#define COBATMANAGER_H

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

class ActionData : public Object{
	GDCLASS(ActionData, Object)
	public:
	
	ActionData();
	~ActionData();

	std::vector<str> strVec;
	std::vector<num> numVec;

	protected:
	static void _bind_methods();
};

class CobatManager : public Node {
	GDCLASS(CobatManager, Node)

private:

	static void ReadValues(std::vector<int>& numbers, std::vector<std::string>& strings, std::string values);

	

protected:
	static void _bind_methods();

public:
	CobatManager();
	~CobatManager();

	void RunSequence(String arg);

	// RunTurn. checks which sides turn it is, and returns the active unit/side

	void _process(double delta);

private:

	std::vector<CharSheet> units;



	// find a way to have this not in the header. preferably its own file
	std::unordered_map<std::string, std::function<void(ActionData&, std::vector<num>&, std::vector<str>&, std::string)>> commands = {
		{"roll", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values) {
			
			
			//UtilityFunctions::print("roll function activated");
			//UtilityFunctions::print((values).c_str());
			size_t pos = values.find(", ");
			int min = 0;
			if (!(min = stoi(values.substr(0, pos))))
			{
				min = 2;
				//look for var
			}
		
			int max = stoi(values.substr(pos + 2));
			int result = min + (rand() % (max - min));

			bool found = false;
			for (size_t i = 0; i < data.numVec.size(); i++)
			{
				if (data.numVec[i].name == "fOut")
				{
					data.numVec[i].value = result;
				}
			}
			if (!found)
			{
				num newNum = num();
				newNum.set("fOut", result);
				data.numVec.push_back(newNum);
			}
			
		}},
		{"changevar", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values) {
			

		}},
		{"add", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values) {
			

			//get numbers from values
			int x = 0;
			int y = 0;

			int z = x + y;

			num newNum = num();
			newNum.set("Out", z);

			data.numVec.push_back(newNum);

		}},
		{"subtract", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values) {
			

		}},
		{"readOut", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values) {
			std::vector<int> numbers;
			std::vector<std::string> strings;

			ReadValues(numbers, strings, values);

			for (int currentNumber : numbers){
				UtilityFunctions::print(currentNumber);
			}
			for (std::string currentString : strings){
				UtilityFunctions::print(currentString.c_str());
			}

			num newNum = num();
			newNum.set(strings[0], numbers[0]);
			numOutputs.push_back(newNum);


			UtilityFunctions::print("numOutputs");

			for (num currentNum : numOutputs){
				UtilityFunctions::print("<-entry->");
				UtilityFunctions::print(currentNum.name.c_str());
				UtilityFunctions::print(currentNum.value);
				UtilityFunctions::print("<-->");

			}



		}}





	};

};
}

#endif