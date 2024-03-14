#include "Ray.h"
#include "Texture.h"
#pragma once

class Face {
    public:
        Face(Ray v1_, Ray v2_, Ray v3_);
        Face(Ray v1_, Ray v2_, Ray v3_, Ray vn1_, Ray vn2_, Ray vn3_);
        Face(Ray v1_, Ray v2_, Ray v3_, Ray vn1_, Ray vn2_, Ray vn3_, double* vt1_, double* vt2_, double* vt3_, Texture* texture_);
        Face(Ray v1_, Ray v2_, Ray v3_, double* vt1_, double* vt2_, double* vt3_, Texture* texture_);
        Ray getVertex(int i);
        Ray getNormal(int i);
        double* getTextureCoords(int i);
        Texture* getTexture(){return texture;}
        bool hasNormals(){return bhasNormals;}
        bool hasTexture(){return textured;}
    private:
        Ray v1,v2,v3;
        Ray vn1,vn2,vn3;
        double* vt1;
        double* vt2;
        double* vt3;
        Texture* texture;
        bool bhasNormals = false;
        bool textured = false;
};