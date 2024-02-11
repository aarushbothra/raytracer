#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Sphere.h"
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
        std::vector<Sphere> getSpheres();//x,y,z location and radius
        void printInput();
        std::string getFilename();
        bool getIsComplete(){return isComplete;}//checks if all necessary inputs have been given
    private:
        std::string filename;
        std::vector<double> viewOrigin;
        std::vector<double> viewDir;
        std::vector<double> upDir;
        double hFOV;
        std::vector<double> imageSize;
        std::vector<double> backgroundColor;
        std::vector<Sphere> spheres;
        std::vector<double> getInputs();//read from file. reads until newline, then returns vector of inputs
        int fileCurrPos = 0;
        void printVector(std::vector<double> input);    
        bool isComplete = false;

};