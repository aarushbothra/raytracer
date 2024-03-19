#include "Input.h"
#include <string>
#include <vector>
#include <iostream>
#include "Output.h"
#include "Ray.h"
#include <math.h>
#include "Intersection.h"

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
        Intersection* checkIntersections(Ray ray, Ray viewOrigin);//returns closest intersection point
        Ray crossProduct(Ray a, Ray b);
        double viewWindowWidth;
        double viewWindowHeight;
        const double viewingDistance = 2;
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
        std::vector<LightSource> shadeRay(Ray intersectPos);//checks if pixel is in shadow
        double dotProduct(Ray a, Ray b);
        double min(double minimum, double input);//checks if input is below minumum. if true, return minimum, otherwise return input
        double distance(Ray a, Ray b);
        std::vector<double> checkFaceIntersection(Ray input, Ray viewOrigin);//returns a distance for each face in the path of ray input. if a face is not in the path, returns -1
        std::vector<double> checkSphereIntersection(Ray input, Ray viewOrigin);
        Ray castLightSphere(Sphere sphereAtRay, Ray intersectPos, Material matAtRay, std::vector<LightSource> lights);
        Ray castLightFace(Face faceAtRay, Ray intersectPos, Material matAtRay, std::vector<LightSource> lights);
        Ray getPixelColor(Ray ray, Ray viewOrigin, int recursionDepth);//returns color at pixel
        std::vector<double> matrixSolver(double a, double b, double e, double c, double d, double f);
        std::vector<double> checkPointOnFace(Ray p, Ray e1, Ray e2, Ray p0, double error);
        Ray specularReflectionRay(Ray surfaceNormal, Ray rayIn);
        double fresnelCoefficient(Ray surfaceNormal, Ray rayIn, double f0);
        const int recursionDepthLimit = 10;
};

