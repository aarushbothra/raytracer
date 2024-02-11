#include "LightSource.h"

void LightSource::print(std::string message){
    std::cout << message;
    for (int i=0;i<3;i++){
        std::cout << position[i] << " ";
    }
    std::cout << directional << " ";
    std::cout << intensity << " ";
    std::cout << "\n";
}