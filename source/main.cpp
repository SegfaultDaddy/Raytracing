#include <cstdlib>
#include <cstdint>
#include <print>
#include <ranges>
#include <iostream>
#include <memory>
#include <chrono>
#include "hittable_list.h"
#include "vec3.h"
#include "ray.h"
#include "numeric"
#include "color.h"
#include "sphere.h"
#include "interval.h"
#include "camera.h"
#include "material.h"

int main(int argc, char** argv)
{
    auto start{std::chrono::steady_clock::now()};

    HittableList<real_type> world{};
    
    auto materialGround{std::make_shared<Lambertian<real_type>>(Vec3<real_type>(0.5, 0.5, 0.5))};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, -1000, 0}, 1000, materialGround));

    for(const auto a : std::views::iota(-11, 11))
    {
        for(const auto b : std::views::iota(-11, 11))
        {
            const auto chooseMaterial{random_number<real_type>()};
            Vec3<real_type> center{a + 0.9 * random_number<real_type>(), 0.2, b + 0.9 * random_number<real_type>()};
            if((center - point3_type(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material<real_type>> sphereMaterial{};
                if(chooseMaterial < 0.8)
                {
                    const auto albedo{color_type::random() * color_type::random()};
                    sphereMaterial = std::make_shared<Lambertian<real_type>>(albedo);
                }
                else if(chooseMaterial < 0.95)
                {
                    const auto albedo{color_type::random(0.5, 1)};
                    const auto fuzz{random_number<real_type>(0, 0.5)};
                    sphereMaterial = std::make_shared<Metal<real_type>>(albedo, fuzz);
                }
                else
                {
                    sphereMaterial = std::make_shared<Dielectric<real_type>>(1.5);
                }
                world.add(std::make_shared<Sphere<real_type>>(center, 0.2, sphereMaterial));
            }
        }
    }

    auto material1{std::make_shared<Dielectric<real_type>>(1.5)};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, 1, 0}, 1.0, material1));

    auto material2{std::make_shared<Lambertian<real_type>>(color_type(0.4, 0.2, 0.1))};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{-4, 1, 0}, 1.0, material2));

    auto material3{std::make_shared<Metal<real_type>>(color_type{0.7, 0.6, 0.5}, 0.0)};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{4, 1, 0}, 1.0, material3));

    Camera camera{};
    camera.render(world);

    const auto end{std::chrono::steady_clock::now()};
    const auto time{std::chrono::duration<double>(end - start)};
    const auto minutes{std::chrono::duration_cast<std::chrono::minutes>(time)};
    std::println(std::clog, "Overall time: {} {}", minutes, std::chrono::duration_cast<std::chrono::seconds>(time) - minutes);
    return EXIT_SUCCESS;
}