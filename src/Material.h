#include "Ray.h"

class Material{
    public:
        Material(std::vector<double> newMat);
        std::vector<double> getMaterial(){return material;}
        Ray KaOdLam;
        Ray KdOdLam;
        Ray KsOsLam;
        double n;
    private:
        std::vector<double> material;
        void calcPhongCoefficients();

        
};