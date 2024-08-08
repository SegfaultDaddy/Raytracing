#ifndef UTILS_H
#define UTILS_H

#include <type_traits>

template<typename Type>
concept Numeric = std::is_arithmetic_v<Type>;

template<Numeric Type>
struct Size
{
    Type width;
    Type height;
};

#endif