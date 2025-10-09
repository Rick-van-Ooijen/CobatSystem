#ifndef MODIFIER_H
#define MODIFIER_H

#include <godot_cpp/classes/sprite2d.hpp>

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace godot {

class numMod : public Object{
	GDCLASS(numMod, Object)
	public:

	std::string name = "";
    int modType = 0;
	int value = 0;
	numMod();
	void set(std::string iName, int iValue);
	~numMod();

	protected:
	static void _bind_methods();
};

class strMod : public Object{
	GDCLASS(strMod, Object)
	public:
	std::string name = "";
    int modType = 0;
	std::string value = "";
	strMod();
	void set(std::string iName, std::string iValue);
	~strMod();

	protected:
	static void _bind_methods();
};


class Modifier : public Sprite2D {
	GDCLASS(Modifier, Sprite2D)

private:


protected:
	static void _bind_methods();

public:
	Modifier();
	~Modifier();

    std::vector<numMod> numModifiers;
    std::vector<strMod> strModifiers;
	std::multimap<std::string, std::string> triggers;


	void _process(double delta);
};

}

#endif