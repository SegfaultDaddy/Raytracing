#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "interval.h"
#include "hittable.h"
#include "utils.h"

template<Numeric Type>
class HittableList : public Hittable<Type>
{
public:
    HittableList() = default;

    HittableList(std::shared_ptr<Hittable<Type>> obj) 
        : objects{obj}
    {
    }
    
    void add(std::shared_ptr<Hittable<Type>> obj)
    {
        objects.push_back(obj);
    }

    void clear()
    {
        objects.clear();
    }

    bool hit(const Ray<Type>& ray, Interval<Type> interval, HitRecord<Type>& record) const override
    {
        HitRecord<Type> temp{};
        bool hitSomething{false};
        auto closest{interval.max};
        for(const auto& obj : objects)
        {
            if(obj->hit(ray, Interval<Type>(interval.min, closest), temp))
            {
                hitSomething = true;
                closest = temp.t;
                record = temp;
            }
        }
        return hitSomething;
    }
private:
    std::vector<std::shared_ptr<Hittable<Type>>> objects;
};

#endif