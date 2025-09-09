#ifndef CHARSHEAT_H
#define CHARSHEAT_H

#include <godot_cpp/classes/Node.hpp>
//#include <godot_cpp/classes/Object.hpp>
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
	

protected:
	static void _bind_methods();

public:
	CharSheet();
	~CharSheet();

	void InitializeValues(String arg);
	void PrintData();

	void _process(double delta);
};

}

#endif