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


#define rollCommand(data, numOutputs, strOutputs, values, manager) \
  {UtilityFunctions::print("they see me rolling");}


}
#endif