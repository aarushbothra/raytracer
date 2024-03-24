#include "Face.h"

Face::Face(Ray v1_, Ray v2_, Ray v3_){
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
}

Face::Face(Ray v1_, Ray v2_, Ray v3_, Ray vn1_, Ray vn2_, Ray vn3_){
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
    vn1 = vn1_;
    vn2 = vn2_;
    vn3 = vn3_;
    bhasNormals = true;
}

Face::Face(Ray v1_, Ray v2_, Ray v3_, Ray vn1_, Ray vn2_, Ray vn3_, double* vt1_, double* vt2_, double* vt3_, Texture* texture_){
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
    vn1 = vn1_;
    vn2 = vn2_;
    vn3 = vn3_;
    vt1 = vt1_;
    vt2 = vt2_;
    vt3 = vt3_;
    texture = texture_;
    bhasNormals = true;
    textured = true;
}

Face::Face(Ray v1_, Ray v2_, Ray v3_, double* vt1_, double* vt2_, double* vt3_, Texture* texture_){
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
    vt1 = vt1_;
    vt2 = vt2_;
    vt3 = vt3_;
    texture = texture_;
    textured = true;
}

Ray Face::getVertex(int i){
    switch (i)
    {
    case 0:
        return v1;
    
    case 1:
        return v2;
    case 2:
        return v3;
    default:
        throw std::out_of_range ("Index out of bounds");
    }
}

Ray Face::getNormal(int i){
    switch (i)
    {
    case 0:
        return vn1;
    
    case 1:
        return vn2;
    case 2:
        return vn3;
    default:
        throw std::out_of_range ("Index out of bounds");
    }
}

double* Face::getTextureCoords(int i){
    switch (i)
    {
    case 0:
        return vt1;
    
    case 1:
        return vt2;
    case 2:
        return vt3;
    default:
        throw std::out_of_range ("Index out of bounds");
    }
}

Face::~Face(){
    delete vt1;
    delete vt2;
    delete vt3;
    delete texture;
}