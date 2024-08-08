#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <cstdint>
#include <limits>
#include <numbers>
#include <random>

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

template<Numeric Type>
inline Type random_number(const Type min = 0.0, const Type max = 0.999)
{
    std::random_device rd{};
    std::uniform_real_distribution<Type> urd{min, max};
    std::default_random_engine dre{rd()};
    return urd(dre);
}

#endif