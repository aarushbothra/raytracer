#include "Output.h"

Output::Output(Input userInput){
    filename = stripExtension(userInput.getFilename()) + ".ppm";

    width = userInput.getImageSize()[0];
    height = userInput.getImageSize()[1];
    
    const int w = width;
    const int h = height;
    
    imageArr = new double*[w*h];

    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            imageArr[i*width+j] = new double[3];
            for (int k=0;k<3;k++){
                imageArr[i*width+j][k] = -1;
            }
        }
    }
    // generateImage();

}

void Output::modPixel(double red, double green, double blue, int posX, int posY){
    imageArr[posY*width+posX][0] = red;
    imageArr[posY*width+posX][1] = green;
    imageArr[posY*width+posX][2] = blue;

    // generateImage(); 
}

std::vector<double> Output::getPixel(int posX, int posY){
    std::vector<double> output;
    output.push_back(imageArr[posY*width+posX][0]);
    output.push_back(imageArr[posY*width+posX][1]);
    output.push_back(imageArr[posY*width+posX][2]);

    return output;
    // generateImage(); 
}

void Output::generateImage(){
    std::fstream image;
    int linePos = 0;

    
    image.open(filename, std::ios::out);
    image << "P3" << std::endl;//magic number
    image << width << " " << height << std::endl;//give ppm file width and height
    image << "255" << std::endl;//max value for each sub pixel

    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            // printArray(imageArr[i*height+j], 3);
            image << max(255,imageArr[i*width+j][0]*255) << " " << max(255,imageArr[i*width+j][1]*255) << " " << max(255,imageArr[i*width+j][2]*255) << " ";
            linePos++;
            if (linePos == 70) {
                image << std::endl;
                linePos = 0;
            } 
        }
    }
    
    image.close();
}

std::string Output::stripExtension(std::string currFilename){
    return currFilename.substr(0, currFilename.find('.'));
}

void Output::printArray(double array[], int size){
    for (int i=0;i<size; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;   
}

double Output::max(double maxNum, double input){
    if (input > maxNum){
        return maxNum;
    }
    return input;
}