#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class Texture{
    public:
        Texture(std::string filename_);
        std::vector<double> getPixel(int i, int j);
        int getWidth(){return width;}
        int getHeight(){return height;}
        std::string getFilename(){return filename;}
    private:
        std::string filename;
        double** imageArr;
        int width,height;
        void ingestTexture();
};