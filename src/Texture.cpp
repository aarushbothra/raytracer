#include "Texture.h"

Texture::Texture(std::string filename_){
    filename = filename_;
    if (filename[filename.size()-1] == '\r'){
        filename = filename.substr(0, filename.size()-1);
    }
    ingestTexture();
}

std::vector<double> Texture::getPixel(double i, double j){
    std::vector<double> output;
    int u = i*(width-1);
    int v = j*(height-1);
    output.push_back(imageArr[v*width+u][0]);
    output.push_back(imageArr[v*width+u][1]);
    output.push_back(imageArr[v*width+u][2]);

    return output;

}

void Texture::ingestTexture(){
    std::cout << "ingesting texture " << filename << "\n";
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
    int* loopSegArr = new int[3];
    int x = 0;
    while (!file.eof() && file.is_open()){
        

        std::getline(file, input);
        std::stringstream loopInput(input);
        std::string loopSegment;
        // std::vector<int> segments1;
        
        while(std::getline(loopInput, loopSegment, ' ')){
            // if (i == 0 && j == 1){
            //     int b = 8;
            // }
            if(loopSegment == ""){
                
            } else if(loopSegment == "\r"){
                // break;
            } else {
                // std::cout << "segment1: " << segment1 << std::endl;

                loopSegArr[x] = stoi(loopSegment);
                x++;
            }
            if (x == 3){
                imageArr[j*width+i] = new double[3];
                imageArr[j*width+i][0] = loopSegArr[0];
                imageArr[j*width+i][1] = loopSegArr[1];
                imageArr[j*width+i][2] = loopSegArr[2];

                i++;
                if (i==width){
                    j++;
                    i=0;
                }
                if (j==height){
                    break;
                }
                x=0;
            }
            // std::cout << "  i: " << i << " j: " << j << std::endl;
        }
        
    }
    
    // imageArr[j*width+i] = new double[3];
    // imageArr[j*width+i][0] = loopSegArr[0];
    // imageArr[j*width+i][1] = loopSegArr[1];
    // imageArr[j*width+i][2] = loopSegArr[2];

    file.close();
}