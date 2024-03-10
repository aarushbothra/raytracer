#include "Ray.h"

Ray::Ray(double i, double j, double k){
    a = i;
    b = j;
    c = k;
}

Ray::Ray(std::vector<double> input){
    a = input[0];
    b = input[1];
    c = input[2];
}

Ray::Ray(){
    a = 0;
    b = 0;
    c = 0;
}


double Ray::operator[](int i){
    switch (i){
        case 0:
            return a;
        case 1:
            return b;
        case 2:
            return c;
        default:
            throw std::out_of_range ("Index out of bounds");
    }
}


int Ray::size(){
    return 3;
}

void Ray::print(std::string message){

    std::cout << message << " " << a << " " << b << " " << c;
    std::cout << std::endl;

}

double Ray::sum(){
    return a + b + c;
    
}

void Ray::square(){
    a = a*a;
    b = b*b;
    c = c*c;
}