#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <print>
#include "vec3.h"
#include "utils.h"

template<Numeric Type>
void write_color(std::ostream& out, const Vec3<Type> pixelColor)
{
    auto r{pixelColor.x()};
    auto g{pixelColor.y()};
    auto b{pixelColor.z()};

    constexpr double colorConst{255.999};
    std::int32_t rbyte{static_cast<std::int32_t>(colorConst * r)};
    std::int32_t gbyte{static_cast<std::int32_t>(colorConst * g)};
    std::int32_t bbyte{static_cast<std::int32_t>(colorConst * b)};
    std::println(out, "{} {} {}", rbyte, gbyte, bbyte);
}

#endif