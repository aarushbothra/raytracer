#include "Sphere.h"

Sphere::Sphere(Ray newL, std::vector<double> newM, double r){
    location = newL;
    material = newM;
    radius = r;
}
Ray Sphere::getLocation(){
    return location;
}
std::vector<double> Sphere::getMaterial(){
    return material;
}
double Sphere::getRadius(){
    return radius;
}