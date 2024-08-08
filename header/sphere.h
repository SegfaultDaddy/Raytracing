#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

template<Numeric Type>
class Sphere : public Hittable<Type>
{
public:
    Sphere(const Vec3<Type>& center, const Type radius)
        : center{center}, radius{std::fmax(0, radius)}
    {
    }

    bool hit(const Ray<Type>& ray, Interval<Type> interval, HitRecord<Type>& record) const override
    {   
        const auto oc{center - ray.origin()};
        const auto a{ray.direction().length_squared()};
        const auto h{dot(ray.direction(), oc)};
        const auto c{oc.length_squared() - radius * radius};
        const auto discriminant{h * h - a * c};
        if(discriminant < 0)
        {
            return false;
        }
        const auto sqrtD{std::sqrt(discriminant)};
        auto root{(h - sqrtD) / a};
        if(!interval.surrounds(root))
        {
            root = (h + sqrtD) / a;
            if(!interval.surrounds(root))
            {
                return false;
            }
        }
        record.t = root;
        record.point = ray.at(record.t);
        const auto outwardNormal{(record.point - center) / radius};
        record.set_face_normal(ray, outwardNormal);
        record.normal = (record.point - center) / radius;
        return true;
    }
private:
    Vec3<Type> center;
    Type radius;
};

#endif