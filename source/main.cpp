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
#include "camera.h"

int main(int argc, char** argv)
{
    HittableList<real_type> world{};
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, 0, -1}, 0.5));
    world.add(std::make_shared<Sphere<real_type>>(point3_type{0, -100.5, -1}, 100));
    Camera camera{};
    camera.render(world);
    return EXIT_SUCCESS;
}