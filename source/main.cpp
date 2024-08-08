#include <cstdlib>
#include <cstdint>
#include <print>
#include <ranges>
#include <iostream>
#include "hittable_list.h"
#include "vec3.h"
#include "ray.h"
#include "numeric"
#include "color.h"
#include "sphere.h"
#include "interval.h"

Vec3<real_type> ray_color(const Ray<real_type>& ray, const Hittable<real_type>& world);

int main(int argc, char** argv)
{
    constexpr real_type aspectRatio{16.0 / 9.0};
    Size<integer_type> image{400, 0};

    image.height = static_cast<integer_type>(image.width / aspectRatio);
    image.height = (image.height < 1)? 1 : image.height;

    HittableList<real_type> world{};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, -100.5, -1}, 100));

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
        std::println(std::clog, "\rScanlines remaining: {}", image.height - h);
        for(const auto w : std::views::iota(0, image.width))
        {
            auto pixelCenter{pixel100Loc + w * pixelDeltaU + h * pixelDeltaV};
            auto rayDirection{pixelCenter - cameraCenter};
            Ray<real_type> ray{cameraCenter, rayDirection};
            auto pixelColor{ray_color(ray, world)};
            write_color(std::cout, pixelColor);
        }
    }
    std::println(std::clog, "\rDone.");
    return EXIT_SUCCESS;
}

Vec3<real_type> ray_color(const Ray<real_type>& ray, const Hittable<real_type>& world)
{
    HitRecord<real_type> record{};
    if(world.hit(ray, Interval<real_type>(0.0, infinity), record))
    {
        constexpr color_type color{1.0, 1.0, 1.0};
        return 0.5 * color_type{record.normal + color};
    }
    constexpr Vec3<real_type> startValue{1.0, 1.0, 1.0};
    constexpr Vec3<real_type> endValue{0.5, 0.7, 1.0};
    const auto unitDireaction{unit_vector(ray.direction())};
    const auto a{0.5 * (unitDireaction.y() + 1.0)};
    return (1.0 - a) * startValue + a * endValue;
}