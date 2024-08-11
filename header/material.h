#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"
#include "hittable.h"
#include "ray.h"

template<Numeric Type>
class HitRecord;

template<Numeric Type>
class Material
{
public:
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
        scattered = Ray<Type>{record.point, scatterDirection};
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

template<Numeric Type>
class Dielectric : public Material<Type>
{
public:
    Dielectric(const Type refractionIndex)
        : refractionIndex{refractionIndex}
    {
    }

    bool scatter(const Ray<Type>& rayIn, const HitRecord<Type>& record, Vec3<Type>& attenuation, Ray<Type>& scattered) const override
    {
        attenuation = Vec3<Type>{1.0, 1.0, 1.0};
        const Type ri{record.frontFace ? 1.0 / refractionIndex : refractionIndex};
        const auto unitDirection{unit_vector(rayIn.direction())};
        const Type cosTheta{std::fmin(dot(-unitDirection, record.normal), 1.0)};
        const Type sinTheta{std::sqrt(1.0 - cosTheta * cosTheta)};
        const bool cannotRefract{ri * sinTheta > 1.0};
        Vec3<Type> direction{};
        if(cannotRefract || reflectance(cosTheta, ri) > random_number<Type>())
        {
            direction = reflect(unitDirection, record.normal);
        }
        else
        {
            direction = refract(unitDirection, record.normal, ri);
        }
        scattered = Ray<Type>{record.point, direction};
        return true;
    }
private:
    static Type reflectance(const Type cosine, const Type refractionIndex)
    {
        auto r0{(1 - refractionIndex) / (1 + refractionIndex)};   
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

    Type refractionIndex;
};

#endif