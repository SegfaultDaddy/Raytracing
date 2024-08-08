#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

template<Numeric Type>
struct Interval
{
    constexpr Interval() 
        : min(+infinity), max(-infinity)
    {
    }

    constexpr Interval(const Type min, const Type max) 
        : min(min), max(max)
    {
    }

    constexpr Type size() const noexcept
    {
        return max - min;
    }

    constexpr Type clamp(const Type x) const noexcept
    {
        if(x < min)
        {
            return min;
        }
        if(x > max)
        {
            return max;
        }
        return x;
    }
    
    constexpr bool containts(const Type x) const noexcept
    {
        return x >= min && x <= max;
    }
    
    constexpr bool surrounds(const Type x) const noexcept
    {
        return x > min && x < max;
    }

    Type min; 
    Type max;
};

constexpr inline Interval<real_type> empty{+infinity, -infinity};
constexpr inline Interval<real_type> univers{-infinity, +infinity};
#endif