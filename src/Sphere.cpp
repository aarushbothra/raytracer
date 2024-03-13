#include "Sphere.h"

Sphere::Sphere(Ray newL, double r){
    location = newL;
    radius = r;
}
Ray Sphere::getLocation(){
    return location;
}
double Sphere::getRadius(){
    return radius;
}

//Odr Odg Odb Osr Osg Osb ka kd ks n
