#include "Ray.h"
#include "Face.h"
#include "Sphere.h"
#include "Material.h"

class Intersection{
    public:
        Intersection(Ray* point, Material* material, Face* face);
        Intersection(Ray* point, Material* material, Sphere* sphere);
        Intersection();
        Ray* getIntersectionPoint(){return intersectionPoint;};
        Face* getIntersectFace(){return intersectFace;}
        Sphere* getIntersectSphere(){return intersectSphere;}
        Material* getMaterial(){return intersectMaterial;}
        bool getIsSphere(){return isSphere;}
        bool getSuccessfulIntersect(){return successfulIntersect;}
        Intersection& operator=(const Intersection& A){return *this;}
        ~Intersection();
    private: 
        Ray* intersectionPoint;
        Face* intersectFace;
        Sphere* intersectSphere;
        Material* intersectMaterial;
        bool isSphere;
        bool successfulIntersect;
};