#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>
#include "utils.h"

template<Numeric Type>
class Vec3 
{
public:
    constexpr Vec3() : points{0, 0, 0}
    {
    }

    constexpr Vec3(const Type x, const Type y, const Type z) : points{x, y, z}
    {
    }

    constexpr Type x() const
    {
        return points[0];
    }

    constexpr Type y() const
    {
        return points[1];
    }

    constexpr Type z() const
    {
        return points[2];
    }
    
    constexpr Vec3 operator-() const
    {
        return Vec3{-points[0], -points[1], -points[2]};
    }
    
    constexpr Type& operator[](const std::size_t index)
    {
        return points[index];
    }

    constexpr Type operator[](const std::size_t index) const
    {
        return points[index];
    }

    constexpr Vec3& operator+=(const Vec3& that)
    {
        this->points[0] += that.points[0];
        this->points[1] += that.points[1];
        this->points[2] += that.points[2];
        return *this;
    }
    
    constexpr Vec3& operator*=(const Vec3& that)
    {
        this->points[0] *= that.points[0];
        this->points[1] *= that.points[1];
        this->points[2] *= that.points[2];
        return *this;
    }
    
    constexpr Vec3& operator*=(const Type constant)
    {
        this->points[0] *= constant;
        this->points[1] *= constant;
        this->points[2] *= constant;
        return *this;
    }
    
    constexpr Vec3& operator/=(const Type constant)
    {
        return *this *= 1 / constant;
    }

    constexpr Type length() const
    {
        return std::sqrt(length_squared());
    }
    
    constexpr Type length_squared() const
    {
        return points[0] * points[0] + points[1] * points[1] + points[2] * points[2];
    }

    constexpr Vec3 operator+(const Vec3& that) const
    {
        return Vec3{*this} += that;
    }

    constexpr Vec3 operator-(const Vec3& that) const
    {
        return Vec3{*this} += -that;
    }
    
    constexpr Vec3 operator*(const Vec3& that) const
    {
        return Vec3{*this} *= that;
    }
    
    constexpr Vec3 operator*(const Type constant) const
    {
        return Vec3{*this} *= constant;
    }

    constexpr inline friend Vec3 operator*(const Type constant, Vec3 vec)
    {
        return vec *= constant;
    }

    constexpr Vec3 operator/(const Type constant) const
    {
        return Vec3{*this} /= constant;
    }
    
    inline friend std::ostream& operator<<(std::ostream& out, const Vec3& vec)
    {
        return out << vec.points[0] << ' ' << vec.points[1] << ' ' << vec.points[2];
    }

    constexpr inline friend Type dot(const Vec3& first, const Vec3& second)
    {
        return first.points[0] * second.points[0]
             + first.points[1] * second.points[1]
             + first.points[2] * second.points[2];
    }

    constexpr inline friend Vec3<Type> cross(const Vec3<Type>& first, const Vec3<Type>& second)
    {
        return Vec3<Type>{first.points[1] * second.points[2] - first.points[2] * second.points[1],
                          first.points[2] * second.points[0] - first.points[0] * second.points[2],
                          first.points[0] * second.points[1] - first.points[1] * second.points[0]};
    }

    constexpr inline friend Vec3<Type> unit_vector(const Vec3<Type>& vec)
    {
        return vec / vec.length();
    }
private:
    std::array<Type, 3> points;
};

using point3_type = Vec3<real_type>;
using color_type = Vec3<real_type>;

#endif