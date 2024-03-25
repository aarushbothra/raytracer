#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Sphere.h"
#include "LightSource.h"
#include "Face.h"
#include "Material.h"
#include <sstream>
#pragma once


class Input{
    public:
        Input(std::string filename);
        std::vector<double> getViewOrigin();//all dir std::vectors return x,y,z
        std::vector<double> getViewDir();
        std::vector<double> getUpDir();
        double getHFOV();
        std::vector<double> getImageSize();//returns width,height
        std::vector<double> getBackgroundColor();//all colors return RGB
        std::vector<Sphere> getSpheres();//returns the sphere's location and radius in a sphere object
        std::vector<LightSource> getLights(){return lights;}
        void printInput();
        std::string getFilename();
        bool getIsComplete(){return isComplete;}//checks if all necessary inputs have been given
        std::vector<Material> getMaterials(){return materials;}
        std::vector<Face> getFaces(){return faces;}
        std::vector<Ray> getVertices(){return vertices;}
        ~Input();
    private:
        std::vector<LightSource> lights;
        std::string filename;
        std::vector<double> viewOrigin;
        std::vector<double> viewDir;
        std::vector<double> upDir;
        double hFOV;
        std::vector<double> imageSize;
        std::vector<double> backgroundColor;
        std::vector<Sphere> spheres;
        int fileCurrPos = 0;
        void printVector(std::vector<double> input);    
        bool isComplete = false;
        std::vector<Ray> vertices;
        std::vector<Ray> vertexNormals;
        std::vector<Face> faces;
        std::vector<Material> materials;
        std::vector<Texture*> textures;
        std::vector<std::vector<double>> textureCoords;

};