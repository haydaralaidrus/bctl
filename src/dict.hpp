#ifndef BCTL_DICT_HPP
#define BCTL_DICT_HPP

#include <string>
#include <unordered_map>
#include "expr.hpp"

namespace bctl {

using dict = std::unordered_map<std::string, expr>;

}

#endif
