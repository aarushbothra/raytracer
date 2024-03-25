#include "Intersection.h"

Intersection::Intersection(Ray* point, Material* material, Face* face) {
    intersectionPoint = point;
    intersectMaterial = material;
    intersectFace = face;
    isSphere = false;
    successfulIntersect = true;
}

Intersection::Intersection(Ray* point, Material* material, Sphere* sphere){
    intersectionPoint = point;
    intersectMaterial = material;
    intersectSphere = sphere;
    isSphere = true;
    successfulIntersect = true;
}

Intersection::Intersection(){
    successfulIntersect = false;
}

Intersection::~Intersection(){
    if (successfulIntersect){
        delete intersectionPoint;
        delete intersectMaterial;
        if (isSphere){
            delete intersectSphere;
        } else {
            delete intersectFace;
        }
    }
}