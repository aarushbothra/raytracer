#include "LightSource.h"

void LightSource::print(std::string message){
    if (attenuatable){
        std::cout << "att";
    }
    std::cout << message;
    for (int i=0;i<3;i++){
        std::cout << position[i] << " ";
    }
    std::cout << !directional << " ";
    std::cout << intensity << " ";
    if (attenuatable){
        std::cout << c1 << " " << c2 << " " << c3 << " " << std::endl;
    } else {
        std::cout << std::endl;
    }
}

LightSource::~LightSource(){}