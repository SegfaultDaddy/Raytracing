#ifndef RAY_H
#define RAY_H

#include "utils.h"
#include "vec3.h"

template<Numeric Type>
class Ray
{
public:
    constexpr Ray() = default;

    constexpr Ray(const Vec3<Type>& origin, const Vec3<Type>& direction)
        : start{origin}, angle{direction}
    {
    }
    
    constexpr Ray& operator=(const Ray& that) = default;

    constexpr Ray& operator=(Ray&& that) = default;

    constexpr const Vec3<Type>& origin() const
    {
        return start;
    }
    
    constexpr const Vec3<Type>& direction() const
    {
        return angle;
    }

    constexpr Vec3<Type> at(const Type t) const
    {
        return origin() + t * direction();
    }
private:
    Vec3<Type> start;
    Vec3<Type> angle;
};

#endif