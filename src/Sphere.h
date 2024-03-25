#include <vector>
#include "Ray.h"
#include "Texture.h"
#pragma once

class Sphere{
    public:
        Sphere(Ray newL, double r);
        Sphere(Ray newL, double r, Texture* texture_);
        Ray getLocation();
        double getRadius();
        bool hasTexture(){return textured;}
        Texture* getTexture(){return texture;}
        ~Sphere(){}
    private:
        Ray location;
        double radius;
        bool textured = false;
        Texture* texture;
};