#include <cstdlib>
#include <cstdint>
#include <print>
#include <ranges>
#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "numeric"
#include "color.h"

constexpr inline bool hit_sphere(const Vec3<real_type>& center, const real_type radius, const Ray<real_type>& ray);
constexpr inline Vec3<real_type> ray_color(const Ray<real_type>& ray);

int main(int argc, char** argv)
{
    constexpr real_type aspectRatio{16.0 / 9.0};
    Size<integer_type> image{400, 0};

    image.height = static_cast<integer_type>(image.width / aspectRatio);
    image.height = (image.height < 1)? 1 : image.height;

    constexpr real_type focalLength{1.0};
    Size<real_type> viewport{0.0, 2.0};
    viewport.width = viewport.height * (static_cast<real_type>(image.width) / image.height);
    Vec3<real_type> cameraCenter{0, 0, 0};

    Vec3<real_type> viewportU{viewport.width, 0, 0};
    Vec3<real_type> viewportV{0, -viewport.height, 0};

    Vec3<real_type> pixelDeltaU{viewportU / image.width};
    Vec3<real_type> pixelDeltaV{viewportV / image.height};

    Vec3<real_type> viewportUpperLeft{cameraCenter - Vec3<real_type>(0, 0, focalLength) 
                                    - viewportU / 2 - viewportV / 2};
    Vec3<real_type> pixel100Loc{viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV)};

    std::println(std::cout, "P3\n{} {}\n255", image.width, image.height);
    for(const auto h : std::views::iota(0, image.height))
    {
        //std::println(std::clog, "\rScanlines remaining: {}", image.height - h);
        for(const auto w : std::views::iota(0, image.width))
        {
            auto pixelCenter{pixel100Loc + w * pixelDeltaU + h * pixelDeltaV};
            auto rayDirection{pixelCenter - cameraCenter};
            Ray<real_type> ray{cameraCenter, rayDirection};
            auto pixelColor{ray_color(ray)};
            write_color(std::cout, pixelColor);
        }
    }
    std::println(std::clog, "\rDone.");
    return EXIT_SUCCESS;
}

constexpr bool hit_sphere(const Vec3<real_type>& center, const real_type radius, const Ray<real_type>& ray)
{
    auto oc{center - ray.origin()};
    const auto a{dot(ray.direction(), ray.direction())};
    const auto b{-2.0 * dot(ray.direction(), oc)};
    const auto c{dot(oc, oc) - radius * radius};
    const auto discriminant{b * b - 4.0 * a * c};
    return discriminant >= 0;
}

constexpr Vec3<real_type> ray_color(const Ray<real_type>& ray)
{
    constexpr Vec3<real_type> sphereColor{1.0, 0.0, 0.0};
    constexpr Vec3<real_type> sphereCenter{0.0, 0.0, -1.0};
    if(hit_sphere(sphereCenter, 0.5, ray))
    {
        std::println(std::clog, "Hit!");
        return sphereColor;
    }
    constexpr Vec3<real_type> startValue{1.0, 1.0, 1.0};
    constexpr Vec3<real_type> endValue{0.5, 0.7, 1.0};
    const auto unitDireaction{unit_vector(ray.direction())};
    const auto a{0.5 * (unitDireaction.y() + 1.0)};
    return (1.0 - a) * startValue + a * endValue;
}