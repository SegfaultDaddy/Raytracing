#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "hittable.h"
#include "material.h"

class Camera
{
public:
    void render(const Hittable<real_type>& world)
    {  
        initialize(); 
        std::println(std::cout, "P3\n{} {}\n255", image.width, image.height);
        for(const auto h : std::views::iota(0, image.height))
        {
            std::println(std::clog, "\rScanlines remaining: {}", image.height - h);
            for(const auto w : std::views::iota(0, image.width))
            {
                color_type pixelColor{0, 0, 0};
                for(const auto sample : std::views::iota(0, samplesPerPixel))
                {
                    const auto ray{get_ray(w, h)};
                    pixelColor += ray_color(ray, maxDepth, world);
                }
                write_color(std::cout, pixelsSampleScale * pixelColor);
            }
        }
        std::println(std::clog, "\rDone.");
    }

private:
    void initialize()
    {
        image.height = static_cast<integer_type>(image.width / aspectRatio);
        image.height = (image.height < 1)? 1 : image.height;

        pixelsSampleScale = 1.0 / samplesPerPixel;

        center = lookfrom;

        const auto theta{radians(vfov)};
        const auto h{std::tan(theta / 2)};
        Size<real_type> viewport{0.0, 2 * h * focusDist};
        viewport.width = viewport.height * (static_cast<real_type>(image.width) / image.height);

        basis.w = unit_vector(lookfrom - lookat);
        basis.u = unit_vector(cross(vup, basis.w));
        basis.v = cross(basis.w, basis.u);

        Vec3<real_type> viewportU{viewport.width * basis.u};
        Vec3<real_type> viewportV{viewport.height * -basis.v};

        pixelDeltaU = Vec3<real_type>{viewportU / image.width};
        pixelDeltaV = Vec3<real_type>{viewportV / image.height};

        Vec3<real_type> viewportUpperLeft{center - focusDist * basis.w -
                                          viewportU / 2 - viewportV / 2};
        pixel100Loc = Vec3<real_type>{viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV)};

        const auto defocusRadius{focusDist * std::tan(radians(defocusAngle / 2))};
        defocusDiskU = basis.u * defocusRadius;
        defocusDiskV = basis.v * defocusRadius;
    }

    Vec3<real_type> ray_color(const Ray<real_type>& ray, const integer_type depth, const Hittable<real_type>& world) const 
    {   
        if(depth <= 0)
        {
            return Vec3<real_type>{0, 0, 0};
        }
        HitRecord<real_type> record{};
        if(world.hit(ray, Interval<real_type>(0.001, infinity), record))
        {
            Vec3<real_type> attenuation{};
            Ray<real_type> scattered{};
            if(record.material->scatter(ray, record, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, depth - 1, world);
            }
            return Vec3<real_type>{0, 0, 0};
        }
        constexpr Vec3<real_type> startValue{1.0, 1.0, 1.0};
        constexpr Vec3<real_type> endValue{0.5, 0.7, 1.0};
        const auto unitDireaction{unit_vector(ray.direction())};
        const auto a{0.5 * (unitDireaction.y() + 1.0)};
        return (1.0 - a) * startValue + a * endValue;
    }

    Ray<real_type> get_ray(const integer_type i, const integer_type j) const
    {
        const auto offset{sample_square()};
        const auto pixelSample{pixel100Loc + (i + offset.x()) * pixelDeltaU + (j + offset.y()) * pixelDeltaV};
        const auto rayOrigin{defocusAngle <= 0 ? center : defocus_disk_sample()};
        const auto rayDirection{pixelSample - center};
        return Ray<real_type>{rayOrigin, rayDirection};
    }

    Vec3<real_type> sample_square() const
    {
        return Vec3<real_type>{random_number<real_type>() - 0.5, random_number<real_type>() - 0.5, 0};
    }

    Vec3<real_type> defocus_disk_sample() const
    {
        const auto p{random_in_unit_disk<real_type>()};
        return center + (p[0] * defocusDiskU) + (p[1] * defocusDiskV);
    }

    constexpr static real_type aspectRatio{16.0 / 9.0};
    constexpr static integer_type samplesPerPixel{500};
    constexpr static integer_type maxDepth{50};
    constexpr static real_type vfov{20};
    constexpr static Vec3<real_type> lookfrom{13, 2, 3};
    constexpr static Vec3<real_type> lookat{0, 0, 0};
    constexpr static Vec3<real_type> vup{0, 1, 0};
    constexpr static real_type defocusAngle{0.6};
    constexpr static real_type focusDist{10.0};
    Size<integer_type> image{1200, 0};
    Vec3<real_type> center;
    Vec3<real_type> pixel100Loc;
    Vec3<real_type> pixelDeltaU;
    Vec3<real_type> pixelDeltaV;
    real_type pixelsSampleScale;
    struct 
    {
        Vec3<real_type> u;
        Vec3<real_type> v;
        Vec3<real_type> w;
    } basis;
    Vec3<real_type> defocusDiskU;
    Vec3<real_type> defocusDiskV;
};

#endif