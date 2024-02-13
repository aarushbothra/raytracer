#include "Input.h"

std::ifstream inputFile;


Input::Input(std::string filename){
    Input::filename = filename;
    std::string input;
    inputFile.open(filename);
    int inputCounter = 0;
    while (!inputFile.eof() && inputFile.is_open()){
        inputFile >> input;
        // std::cout << "input: " << input << std::endl;
        if (input == "imsize"){
            
            imageSize = Input::getInputs();
            inputCounter++;
        }
        else if (input == "eye"){
            
            viewOrigin = Input::getInputs();
            inputCounter++;

        }
        else if (input == "viewdir"){
            
            viewDir = Input::getInputs();
            inputCounter++;

        }
        else if (input == "hfov"){
            inputFile>>input;
            hFOV = stoi(input);
            inputCounter++;

        }
        else if (input == "updir"){
            
            upDir = Input::getInputs();
            inputCounter++;

        }
        
        else if (input == "bkgcolor"){
            // std::cout << "bkgcolor: " << std::endl;
            
            backgroundColor = Input::getInputs();
            inputCounter++;

        }
        else if (input == "mtlcolor"){
            std::vector<double> materialColor;
            std::vector<double> sphereLocationAndRadius;       
            materialColor = getInputs();
            int holdPosition = inputFile.tellg();
            inputFile >> input;
            bool foundSphere = false;
            while (!foundSphere && !inputFile.eof()){
                if (input == "sphere"){
                    sphereLocationAndRadius = getInputs();
                    Ray sphereLocation(sphereLocationAndRadius[0],sphereLocationAndRadius[1],sphereLocationAndRadius[2]);
                    spheres.push_back(Sphere(sphereLocation,materialColor,sphereLocationAndRadius.at(3)));
                    foundSphere = true;
                    break;
                } else {
                    inputFile >> input;
                }
            }

            if (!foundSphere){
                break;
            }

            inputFile.seekg(holdPosition);

        } else if (input == "light"){
            std::vector<double> lightInput = getInputs();
            Ray position(lightInput[0],lightInput[1],lightInput[2]);
            LightSource newLight(position, lightInput[3], lightInput[4]);
            lights.push_back(newLight);
        }
        std::cout << input << "\n";
        
    }

    inputFile.close();
    if (inputCounter == 6 && spheres.size() > 0 && lights.size() > 0){
        isComplete = true;
    }
}

std::string Input::getFilename(){
    return filename;
}

std::vector<double> Input::getImageSize(){
    return imageSize;
}

std::vector<double> Input::getViewOrigin(){
    return viewOrigin;
}

std::vector<double> Input::getViewDir(){
    return viewDir;
}

double Input::getHFOV(){
    return hFOV;
}

std::vector<double> Input::getUpDir(){
    return upDir;
}

std::vector<double> Input::getBackgroundColor(){
    return backgroundColor;
}

std::vector<Sphere> Input::getSpheres(){
    return spheres;
}

void Input::printInput(){
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "imsize ";
    printVector(imageSize);
    std::cout << "eye ";
    printVector(viewOrigin);
    std::cout<<"viewdir ";
    printVector(viewDir);
    std::cout<<"hfov " << hFOV << std::endl;
    std::cout << "updir ";
    printVector(upDir);
    std::cout<<"bkgcolor ";
    printVector(backgroundColor);
    for (int i=0;i<spheres.size();i++){
        std::cout << "mtlcolor ";
        printVector(spheres.at(i).getMaterial());
        spheres.at(i).getLocation().print("sphere ");
    }
    for (int i=0;i<lights.size();i++){
        lights.at(i).print("light ");
    }
    
}

std::vector<double> Input::getInputs(){
    
    std::vector<double> output;
    double input;

    while (inputFile.peek() != '\n' && !inputFile.eof()){
        inputFile >> input;
        // std::cout << "   " << input;
        output.push_back(input);
    }
    // std::cout << std::endl;
    
    return output;
} 

void Input::printVector(std::vector<double> input){
    for (int i=0;i<input.size();i++){
        std::cout << input.at(i) << " ";
    }
    std::cout << std::endl;
}
