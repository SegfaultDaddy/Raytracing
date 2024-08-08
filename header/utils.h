#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <cstdint>
#include <limits>
#include <numbers>

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

constexpr inline real_type infinity{std::numeric_limits<real_type>::infinity()};
constexpr inline auto pi{std::numbers::pi};

template<Numeric Type>
constexpr inline Type radians(const Type degrees)
{
    return degrees * pi / 180.0;
}
#endif