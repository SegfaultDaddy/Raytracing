#include <cstdlib>
#include <cstdint>
#include <print>
#include <ranges>
#include <iostream>
#include <chrono>
#include "hittable_list.h"
#include "vec3.h"
#include "ray.h"
#include "numeric"
#include "color.h"
#include "sphere.h"
#include "interval.h"
#include "camera.h"

int main(int argc, char** argv)
{
    auto start{std::chrono::steady_clock::now()};
    HittableList<real_type> world{};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, -100.5, -1}, 100));
    Camera camera{};
    camera.render(world);
    auto end{std::chrono::steady_clock::now()};
    auto time{std::chrono::duration<double>(end - start)};
    std::println(std::clog, "Overall time: {}, {}", std::chrono::duration_cast<std::chrono::minutes>(time), std::chrono::duration_cast<std::chrono::seconds>(time));
    return EXIT_SUCCESS;
}