#include "Material.h"

Material::Material(std::vector<double> newMat){
    material = newMat;
    if (material.size()>3){
        calcPhongCoefficients();
        n = material[9];
    }
}

void Material::calcPhongCoefficients(){
    Ray Od(material[0], material[1], material[2]);
    Ray Os(material[3], material[4], material[5]);
    double Ka = material[6];
    double Kd = material[7];
    double Ks = material[8];

    KaOdLam = Od*Ka;
    KdOdLam = Od*Kd;
    KsOsLam = Os*Ks;
}