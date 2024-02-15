#include "Ray.h"

class LightSource{
    private:
        Ray position;
        bool directional;
        double intensity;
        bool attenuatable = false;
        double c1,c2,c3;
    public:
        LightSource(Ray position_, bool directional_, double intensity_){
            position = position_;
            directional = !directional_;
            intensity = intensity_;
        }
        LightSource(Ray position_, bool directional_, double intensity_, double c1_, double c2_, double c3_){
            position = position_;
            directional = !directional_;
            intensity = intensity_;
            c1 = c1_;
            c2 = c2_;
            c3 = c3_;
            attenuatable = true;
        }
        Ray getPosition(){
            return position;
        }
        bool isDirectional(){
            return directional;
        }
        double getIntensity(){
            return intensity;
        }
        double getAttenFactor(double d){
            if (attenuatable){
                return 1/(c1 + c2*d + c3*d*d);
            } else {
                return 1;
            }
        }
        void print(std::string message);
};