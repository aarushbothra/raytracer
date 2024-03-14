#include <string>
#include <vector>

class Texture{
    public:
        Texture(std::string filename_){filename = filename_;}
        std::vector<double> getPixel(int i, int j); 
    private:
        std::string filename;
        double** imageArr;
        int width,height;
};