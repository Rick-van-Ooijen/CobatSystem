#ifndef CHARSHEAT_H
#define CHARSHEAT_H

#include <godot_cpp/classes/Node.hpp>
//#include <godot_cpp/classes/Object.hpp>
#include <string>
#include <sstream>
#include <vector>

namespace godot {

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

class CharSheat : public Node {
	GDCLASS(CharSheat, Node)

private:

	std::vector<str> strVec;
	std::vector<num> numVec;
	

protected:
	static void _bind_methods();

public:
	CharSheat();
	~CharSheat();

	void InitializeValues(String arg);
	void PrintData();

	void _process(double delta);
};

}

#endif