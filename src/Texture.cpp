#include "Texture.h"

Texture::Texture(std::string filename_){
    filename = filename_;
    ingestTexture();
    int i = 3;
}

std::vector<double> Texture::getPixel(int i, int j){
    std::vector<double> output;
    output.push_back(imageArr[j*width+i][0]);
    output.push_back(imageArr[j*width+i][1]);
    output.push_back(imageArr[j*width+i][2]);

    return output;

}

void Texture::ingestTexture(){
    std::fstream file(filename);
    std::string input;

    std::getline(file, input);
    std::stringstream inputString(input);
    std::string segment;
    std::vector<std::string> segments;
    while(std::getline(inputString, segment, ' ')){
        if(segment != " "){
            segments.push_back(segment);
        }
    }
    width = stoi(segments[1]);
    height = stoi(segments[2]);
    const int w = width;
    const int h = height;
    imageArr = new double*[w*h];

    int i = 0;
    int j = 0;
    while (!file.eof() && file.is_open()){
        

        std::getline(file, input);
        std::stringstream inputString1(input);
        std::string segment1;
        std::vector<int> segments1;
        while(std::getline(inputString1, segment1, ' ')){
            // if (i == 0 && j == 1){
            //     int b = 8;
            // }
            if(segment1 == ""){
                imageArr[j*width+i] = new double[3];
                imageArr[j*width+i][0] = segments1[0];
                imageArr[j*width+i][1] = segments1[1];
                imageArr[j*width+i][2] = segments1[2];

                i++;
                if (i==width){
                    j++;
                    i=0;
                }
                if (j==height){
                    break;
                }
                segments1.clear();
            } else if(segment1 == "\r"){
                break;
            } else {
                // std::cout << "segment1: " << segment1 << std::endl;
                segments1.push_back(stoi(segment1));
                
            }
            // std::cout << "  i: " << i << " j: " << j << std::endl;
        }
        
    }

    file.close();
}