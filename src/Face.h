#include "Ray.h"

class Face {
    public:
        Face(Ray v1_, Ray v2_, Ray v3_);
        Face(Ray v1_, Ray v2_, Ray v3_, Ray vn1_, Ray vn2_, Ray vn3_);
        Ray getVertex(int i);
        Ray getNormal(int i);
        bool hasNormals(){return bhasNormals;}
    private:
        Ray v1,v2,v3;
        Ray vn1,vn2,vn3;
        bool bhasNormals = false;
};