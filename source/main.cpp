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
    
    auto materialGround{std::make_shared<Lambertian<real_type>>(Vec3<real_type>(0.8, 0.8, 0.0))};
    auto materialCenter{std::make_shared<Lambertian<real_type>>(Vec3<real_type>(0.1, 0.2, 0.5))};
    auto materialLeft{std::make_shared<Metal<real_type>>(Vec3<real_type>(0.8, 0.8, 0.8), 0.3)};
    auto materialRight{std::make_shared<Metal<real_type>>(Vec3<real_type>(0.8, 0.6, 0.2), 1.0)};

    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, -100.5, -1}, 100, materialGround));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, 0, -1.2}, 0.5, materialCenter));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{-1, 0, -1.0}, 0.5, materialLeft));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{1, 0, -1.0}, 0.5, materialRight));

    Camera camera{};
    camera.render(world);

    const auto end{std::chrono::steady_clock::now()};
    const auto time{std::chrono::duration<double>(end - start)};
    const auto minutes{std::chrono::duration_cast<std::chrono::minutes>(time)};
    std::println(std::clog, "Overall time: {} {}", minutes, std::chrono::duration_cast<std::chrono::seconds>(time) - minutes);
    return EXIT_SUCCESS;
}