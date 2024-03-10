#include <vector>
#include <string>
#include <iostream>
#pragma once

class Ray{
    public:
        Ray(double i, double j, double k);
        Ray(std::vector<double> input);
        Ray();
        friend Ray operator+(Ray ray1, Ray ray2){
            return Ray(ray1[0]+ray2[0],ray1[1]+ray2[1],ray1[2]+ray2[2]);
        }
        friend Ray operator-(Ray ray1, Ray ray2){
            return Ray(ray1[0]-ray2[0],ray1[1]-ray2[1],ray1[2]-ray2[2]);
        }
        double operator[](int i);
        friend Ray operator*(Ray ray1, double scalar){
            return Ray(ray1[0]*scalar,ray1[1]*scalar,ray1[2]*scalar);
        }
        friend Ray operator*( double scalar, Ray ray1){
            return Ray(ray1[0]*scalar,ray1[1]*scalar,ray1[2]*scalar);
        }
        friend Ray operator*(Ray ray1, Ray ray2){//dot product
            return Ray(ray1[0]*ray2[0],ray1[1]*ray2[1],ray1[2]*ray2[2]);
        }
        void print(std::string message);
        int size();
        double sum();
        void square();
        friend bool operator==(const Ray &a, const Ray &b){
            return (a.a == b.a && a.b == b.b && a.c == b.c);
        }
    private:
        double a,b,c;
    
};