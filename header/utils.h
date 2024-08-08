#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <cstdint>

template<typename Type>
concept Numeric = std::is_arithmetic_v<Type>;

template<Numeric Type>
struct Size
{
    Type width;
    Type height;
};

using real_type = double;
using integer_type = std::int32_t;

#endif