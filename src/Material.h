#include "Ray.h"
#pragma once

class Material{
    public:
        Material(std::vector<double> newMat);
        std::vector<double> getMaterial(){return material;}
        Ray KaOdLam;
        Ray KdOdLam;
        Ray KsOsLam;
        double n;
        void calcTextureCoefficients(Ray Od);
    private:
        std::vector<double> material;
        void calcPhongCoefficients();

        
};