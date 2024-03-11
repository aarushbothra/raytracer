#include "Input.h"
#include <string>
#include <vector>
#include <iostream>
#include "Output.h"
#include "Ray.h"
#include <math.h>

class RayCast{
    public:
        RayCast(Input userInput, Output image);
    private:
        Input* inputFromUser;
        Ray w;//-viewDir normalized
        Ray u;
        Ray v;
        Ray normalizeRay(Ray input);
        void printVector(std::vector<double> input, std::string message);
        std::vector<double> checkSpheres(Ray ray, Ray viewOrigin);//checks if ray intersects with sphere
        Ray crossProduct(Ray a, Ray b);
        double viewWindowWidth;
        double viewWindowHeight;
        double viewingDistance = 2;
        double vFOV;
        double degreesToRadians(double degrees);
        double radiansToDegrees(double radians);
        Ray ll;//lower left corner of viewing window
        Ray ul;//upper left corner of viewing window
        Ray lr;//lower right corner of viewing window
        Ray ur;//upper right corner of viewing window
        double aspectRatio;
        void calcViewRays();//calculate rays through the viewing window
        void calcCorners();//calculate corners of viewing window
        void calcViewingWindow();//calculate vectors that define viewing window, as well as its size
        Ray testRay; 
        Output* userImage;
        std::vector<double> shadeRay(Sphere sphereAtRay, Ray intersectPos, Material matAtRay);//calculates shadows from direct light interaction as well as objects
        double dotProduct(Ray a, Ray b);
        double min(double minimum, double input);//checks if input is below minumum. if true, return minimum, otherwise return input
        double distance(Ray a, Ray b);
};

