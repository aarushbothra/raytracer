#include "Ray.h"

Ray::Ray(double i, double j, double k){
    rayStorage = std::vector<double>{i,j,k};
}

Ray::Ray(std::vector<double> input){
    rayStorage = std::vector<double>(3);
    for (int i=0;i<3;i++){
        rayStorage.at(i) = (input.at(i));
    }
}

Ray::Ray(){
    std::vector<double> temp(3);
    rayStorage = temp;
}


double Ray::operator[](int i){
    // std::cout << "\n    "<< i << ": " << rayStorage.at(i) << std::endl;
    return rayStorage.at(i);
}


int Ray::size(){
    return 3;
}

void Ray::print(std::string message){

    std::cout << message;
    for (int i=0;i<3;i++){
        std::cout << rayStorage.at(i) << " ";
    }
    std::cout << std::endl;

}

double Ray::sum(){
    double sum = 0;
    for (int i=0;i<3;i++){
        sum += rayStorage.at(i);
    }
    return sum;
}

void Ray::square(){
    for (int i=0;i<3;i++){
        rayStorage.at(i) = rayStorage.at(i)*rayStorage.at(i);
    }
}