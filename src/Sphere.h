#include <vector>
#include "Ray.h"
#pragma once

class Sphere{
    public:
        Sphere(Ray newL, double r);
        Ray getLocation();
        double getRadius();
        
    private:
        Ray location;
        double radius;
};