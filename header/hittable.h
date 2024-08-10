#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include "utils.h"
#include "interval.h"
#include "ray.h"

template<Numeric Type>
class Material;

template<Numeric Type>
struct HitRecord
{
    constexpr void set_face_normal(const Ray<Type>& ray, const Vec3<Type>& outwardNormal)
    {
        frontFace = dot(ray.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }

    Vec3<Type> point;
    Vec3<Type> normal;
    Type t;
    std::shared_ptr<Material<Type>> material;
    bool frontFace;
};

template<Numeric Type>
class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray<Type>& ray, Interval<Type> interval, HitRecord<Type>& record) const = 0;
};

#endif