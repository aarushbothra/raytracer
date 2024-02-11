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
            std::vector<double> temp;
            for (int i=0;i<3;i++){
                temp.push_back(ray1[i]+ray2[i]);
            }
            return Ray(temp);
        }
        friend Ray operator-(Ray ray1, Ray ray2){
            std::vector<double> temp;
            for (int i=0;i<3;i++){
                temp.push_back(ray1[i]-ray2[i]);
            }
            return Ray(temp);
        }
        double operator[](int i);
        friend Ray operator*(Ray ray1, double scalar){
            std::vector<double> temp;
            for (int i=0;i<3;i++){
                temp.push_back(ray1[i]*scalar);
            }
            return Ray(temp);
        }
        friend Ray operator*(Ray ray1, Ray ray2){
            std::vector<double> temp;
            for (int i=0;i<3;i++){
                temp.push_back(ray1[i]*ray2[i]);
            }
            return Ray(temp);
        }
        void print(std::string message);
        int size();
        double sum();
        void square();
        friend bool operator==(const Ray &a, const Ray &b){
            return a.rayStorage == b.rayStorage;
        }
    private:
        std::vector<double> rayStorage;
    
};