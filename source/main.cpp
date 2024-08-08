#include <cstdlib>
#include <cstdint>
#include <print>
#include <ranges>
#include <iostream>
#include "vec3.h"
#include "numeric"
#include "color.h"

int main(int argc, char** argv)
{
    constexpr Size image{256, 256};

    std::println(std::cout, "P3\n{} {}\n255", image.width, image.height);
    for(const auto h : std::views::iota(0, image.height))
    {
        std::println(std::clog, "\rScanlines remaining: {}", image.height - h);
        for(const auto w : std::views::iota(0, image.width))
        {
            Vec3 vec{static_cast<double>(w) / (image.width - 1), 
                     static_cast<double>(h) / (image.height - 1), 
                     0.0};
            write_color(std::cout, vec);
        }
    }
    std::println(std::clog, "\rDone.");
    Vec3 v{1.0, 2.0, 3.0};
    return EXIT_SUCCESS;
}
