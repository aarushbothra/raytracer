#include "Sphere.h"

Sphere::Sphere(Ray newL, std::vector<double> newM, double r){
    location = newL;
    material = newM;
    radius = r;
    if (material.size()>3){
        calcPhongCoefficients();
        n = material[9];
    }
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

//Odr Odg Odb Osr Osg Osb ka kd ks n
void Sphere::calcPhongCoefficients(){
    Ray Od(material[0], material[1], material[2]);
    Ray Os(material[3], material[4], material[5]);
    double Ka = material[6];
    double Kd = material[7];
    double Ks = material[8];

    KaOdLam = Od*Ka;
    KdOdLam = Od*Kd;
    KsOsLam = Os*Ks;
}