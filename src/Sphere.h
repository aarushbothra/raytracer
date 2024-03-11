#include <vector>
#include "Ray.h"

class Sphere{
    public:
        Sphere(Ray newL, double r);
        Ray getLocation();
        double getRadius();
        
    private:
        Ray location;
        double radius;
};