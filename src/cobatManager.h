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
#include "FNMisc.h"
#include "FNMath.h"
#include "FNModifiers.h"

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
	
	
	
	protected:
	static void _bind_methods();
	
	public:
	static void ReadValues(std::vector<int>& numbers, std::vector<std::string>& strings, std::string values);
	static std::string ReadString(std::string value);
	static int ReadInt(std::string value);
	
	CobatManager();
	~CobatManager();
	
	void RunSequence(String arg);
	void AddUnit(CharSheet* unit);
	
	
	void _process(double delta);
	
	std::vector<CharSheet*> units;
	private:
	
	

	std::unordered_map<std::string, std::function<void(ActionData&, std::vector<num>&, std::vector<str>&, std::string, CobatManager*)>> commands = {
		{"roll", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			rollCommand(data, numOutputs, strOutputs, values, manager);}},

		{"changevar", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			changevarCommand(data, numOutputs, strOutputs, values, manager);}},

		{"add", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			addCommand(data, numOutputs, strOutputs, values, manager);}},

		{"subtract", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			subtractCommand(data, numOutputs, strOutputs, values, manager);}},

		{"readOut", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			readOutCommand(data, numOutputs, strOutputs, values, manager);}},

		{"makeModifier", [](ActionData& data, std::vector<num>& numOutputs, std::vector<str>& strOutputs, std::string values, CobatManager* manager) {
			makeModifierCommand(data, numOutputs, strOutputs, values, manager);}}





	};

};
}

#endif