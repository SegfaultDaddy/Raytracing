#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"
#include "hittable.h"
#include "ray.h"

template<Numeric Type>
struct HitRecord;

template<Numeric Type>
struct Material
{
    virtual ~Material() = default;

    virtual bool scatter(const Ray<Type>& rayIn, const HitRecord<Type>& record, Vec3<Type>& attenuation, Ray<Type>& scattered) const
    {
        return false;
    }
};

template<Numeric Type>
class Lambertian : public Material<Type>
{
public:
    Lambertian(const Vec3<Type>& albedo) 
        : albedo{albedo}
    {
    }

    bool scatter(const Ray<Type>& rayIn, const HitRecord<Type>& record, Vec3<Type>& attenuation, Ray<Type>& scattered) const override
    {
        Vec3<Type> scatterDirection{record.normal + random_unit_vector<Type>()};
        if(scatterDirection.near_zero())
        {
            scatterDirection = record.normal;
        }
        const auto ray{Ray<Type>{record.point, scatterDirection}};
        scattered = ray;
        attenuation = albedo;
        return true;
    }
private:
    Vec3<Type> albedo;
};

template<Numeric Type>
class Metal : public Material<Type>
{
public:
    Metal(const Vec3<Type>& albedo, Type fuzz) 
        : albedo{albedo}, fuzz{fuzz < 1 ? fuzz : 1}
    {
    }

    bool scatter(const Ray<Type>& rayIn, const HitRecord<Type>& record, Vec3<Type>& attenuation, Ray<Type>& scattered) const override
    {
        auto reflected{reflect(rayIn.direction(), record.normal)};
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector<Type>());
        scattered = Ray<Type>(record.point, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), record.normal) > 0;
    }
private:
    Vec3<Type> albedo;
    Type fuzz;
};

#endif