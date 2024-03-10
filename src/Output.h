#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <istream>
#pragma once
#include "Input.h"
#include <iomanip>

class Output{
    public:
        Output(Input userInput);
        void modPixel(double red, double green, double blue, int posX, int posY);//modifies a single pixel
        std::vector<double> getPixel(int posX, int posY);
        void generateImage();//generates a ppm image by writing the contents of imageArr to a file of the same name as filename
    private:
        std::string filename;
        std::string stripExtension(std::string currFilename);//strips the file extension so a .ppm extension can be added
        double** imageArr;//array in which each pixel of the image is stored. Default image uses the color given by bkgcolor
        int width;
        int height;
        void printArray(double array[], int size);
        int max(int maxNum, double input);
};