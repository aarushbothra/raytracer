#include <vector>
#include "Ray.h"

class Sphere{
    public:
        Sphere(Ray newL, std::vector<double> newM, double r);
        Ray getLocation();
        std::vector<double> getMaterial();
        double getRadius();
    private:
        Ray location;
        std::vector<double> material;
        double radius;
};