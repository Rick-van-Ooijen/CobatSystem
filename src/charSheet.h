#ifndef CHARSHEAT_H
#define CHARSHEAT_H

#include <godot_cpp/classes/Node.hpp>
//#include <godot_cpp/classes/Object.hpp>
#include "modifier.h"
#include <string>
#include <sstream>
#include <vector>

namespace godot {

class num : public Object{
	GDCLASS(num, Object)
public:
	std::string name = "";
	int value = 0;
	num();
	void set(std::string iName, int iValue);
	~num();

protected:
	static void _bind_methods();
};

class str : public Object{
	GDCLASS(str, Object)
public:
	std::string name = "";
	std::string value = "";
	str();
	void set(std::string iName, std::string iValue);
	~str();

protected:
	static void _bind_methods();
};

class CharSheet : public Node {
	GDCLASS(CharSheet, Node)

private:


std::vector<str> strVec;
std::vector<num> numVec;


std::vector<str> modifiedStrVec;
std::vector<num> modifiedNumVec;
int side = 0;
bool activated = false;

protected:
static void _bind_methods();

public:
	CharSheet();
	~CharSheet();

	std::string name = "Player";
	std::vector<Modifier> modVec;
	
	void InitializeValues(String arg);
	void ProcessModifiers();
	String PrintData();
	num* FindNum(std::vector<num>& vector, std::string name);
	str* FindStr(std::vector<str>& vector, std::string name);

	void _process(double delta);
};

}

#endif