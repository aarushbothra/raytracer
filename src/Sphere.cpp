#include "Sphere.h"

Sphere::Sphere(Ray newL, double r){
    location = newL;
    radius = r;
}

Sphere::Sphere(Ray newL, double r, Texture* texture_){
    location = newL;
    radius = r;
    texture = texture_;
    textured = true;
}

Ray Sphere::getLocation(){
    return location;
}
double Sphere::getRadius(){
    return radius;
}

//Odr Odg Odb Osr Osg Osb ka kd ks n
