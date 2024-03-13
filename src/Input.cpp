#include "Input.h"

std::ifstream inputFile;


Input::Input(std::string filename){
    Input::filename = filename;
    std::string input;
    inputFile.open(filename);
    int inputCounter = 0;
    vertices.push_back(Ray());
    vertexNormals.push_back(Ray());
    int sphereCount = 0;
    while (!inputFile.eof() && inputFile.is_open()){
        inputFile >> input;
        // std::cout << "input: " << input << std::endl;
        if (input == "imsize"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    imageSize.push_back(stod(segment));
            
                }
            }

        }
        else if (input == "eye"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    viewOrigin.push_back(stod(segment));
            
                }
            }
            

        }
        else if (input == "viewdir"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    viewDir.push_back(stod(segment));
            
                }
            }

        }
        else if (input == "hfov"){
            inputFile>>input;
            hFOV = stoi(input);
            inputCounter++;

        }
        else if (input == "updir"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    upDir.push_back(stod(segment));
            
                }
            }
            
        }
        
        else if (input == "bkgcolor"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    backgroundColor.push_back(stod(segment));
            
                }
            }

        }
        else if (input == "mtlcolor"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    inputNums.push_back(stod(segment));
            
                }
            }
            materials.push_back(Material(inputNums));
        } else if (input == "sphere") {

            
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    inputNums.push_back(stod(segment));
            
                }
            }
                
            spheres.push_back(Sphere(Ray(inputNums[0],inputNums[1],inputNums[2]),inputNums[3]));
        } 
        else if (input == "light"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> lightInput;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    lightInput.push_back(stod(segment));
            
                }
            }
            Ray position(lightInput[0],lightInput[1],lightInput[2]);
            LightSource newLight(position, lightInput[3], lightInput[4]);
            lights.push_back(newLight);
        } else if (input == "attlight"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> lightInput;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    lightInput.push_back(stod(segment));
            
                }
            }
            Ray position(lightInput[0],lightInput[1],lightInput[2]);
            LightSource newLight(position, lightInput[3], lightInput[4],lightInput[5],lightInput[6],lightInput[7]);
            lights.push_back(newLight);
        } else if (input == "f") {
            std::getline(inputFile, input);
            int i,j,k;
            int a,b,c;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            /*if (sscanf(string, "%d/%d/%d %d/%d/%d %d/%d/%d" ) == 9) {
            } else*/ if (sscanf(string, " %d//%d %d//%d %d//%d\r", &i, &a, &j, &b, &k, &c) == 6) {
                faces.push_back(Face(vertices[i],vertices[j],vertices[k],vertexNormals[a],vertexNormals[b],vertexNormals[c]));
            // } else if (sscanf(string, "%d/%d %d/%d %d/%d") == 6) {
            } else if (sscanf(string, " %d %d %d\r", &i, &j, &k) == 3) {
                faces.push_back(Face(vertices[i],vertices[j],vertices[k]));
            } else {
                inputFile >> input;
            }
        } else if (input == "v"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    inputNums.push_back(stod(segment));
            
                }
            }
            Ray vertexInput(inputNums);
            vertices.push_back(vertexInput);
        } else if (input == "vn") {
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != " "){
                    inputNums.push_back(stod(segment));
            
                }
            }
            Ray vertexNormalInput(inputNums);
            vertexNormals.push_back(vertexNormalInput);
        }
        
        
    }

    inputFile.close();
    // if (inputCounter == 6 && (spheres.size() > 0 || faces.size()>0) && lights.size() > 0){
    //     isComplete = true;
    // } 
    isComplete = true;
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
    for (int i=0;i<materials.size();i++){
        std::cout << "mtlcolor ";
        printVector(materials.at(i).getMaterial());
    }
    for (int i=0;i<spheres.size();i++){
        spheres.at(i).getLocation().print("sphere ");
    }
    for (int i=0;i<lights.size();i++){
        lights.at(i).print("light ");
    }
    for (int i=1;i<vertices.size();i++){
        vertices.at(i).print("v: ");
    }
    for(int i=1;i<vertexNormals.size();i++){
        vertexNormals.at(i).print("vn: ");
    }   
    std::cout << "num faces: " << faces.size() << std::endl;
    
}

void Input::printVector(std::vector<double> input){
    for (int i=0;i<input.size();i++){
        std::cout << input.at(i) << " ";
    }
    std::cout << std::endl;
}
