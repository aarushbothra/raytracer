#include "Ray.h"

class LightSource{
    private:
        Ray position;
        bool directional;
        double intensity;
    public:
        LightSource(Ray position_, bool directional_, double intensity_){
            position = position_;
            directional = directional_;
            intensity = intensity;
        }
        Ray getPosition(){
            return position;
        }
        bool getDirectionality(){
            return directional;
        }
        double intensitity(){
            return intensity;
        }
};