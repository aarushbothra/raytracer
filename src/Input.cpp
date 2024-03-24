#include "Input.h"

std::ifstream inputFile;


Input::Input(std::string filename){
    Input::filename = filename;
    std::string input;
    inputFile.open(filename);
    int inputCounter = 0;
    vertices.push_back(Ray());
    vertexNormals.push_back(Ray());
    textureCoords.push_back(new double);
    int sphereCount = 0;
    while (!inputFile.eof() && inputFile.is_open()){
        inputFile >> input;
        // std::cout << "input: " << input << std::endl;
        if (input == "imsize"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
                    imageSize.push_back(stod(segment));
            
                }
            }
            inputCounter++;
        }
        else if (input == "eye"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
                    viewOrigin.push_back(stod(segment));
            
                }
            }
            inputCounter++;

        }
        else if (input == "viewdir"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
                    viewDir.push_back(stod(segment));
            
                }
            }
            inputCounter++;
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
                
                if(segment != ""){
                    upDir.push_back(stod(segment));
            
                }
            }
            inputCounter++;
        }
        
        else if (input == "bkgcolor"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
                    backgroundColor.push_back(stod(segment));
            
                }
            }
            inputCounter++;
        }
        else if (input == "mtlcolor"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
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
                
                if(segment != ""){
                    inputNums.push_back(stod(segment));
            
                }
            }
            if (textures.empty()){
                spheres.push_back(Sphere(Ray(inputNums[0],inputNums[1],inputNums[2]),inputNums[3]));
            } else {
                spheres.push_back(Sphere(Ray(inputNums[0],inputNums[1],inputNums[2]),inputNums[3], textures.at(textures.size()-1)));
            }
            
        } 
        else if (input == "light"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> lightInput;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
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
                
                if(segment != ""){
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
            int x,y,z;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, "%d/%d/%d %d/%d/%d %d/%d/%d",  &i, &a, &x, &j, &b, &y, &k, &c, &z) == 9) {
                faces.push_back(Face(vertices[i],vertices[j],vertices[k],vertexNormals[a],vertexNormals[b],vertexNormals[c], textureCoords[x], textureCoords[y], textureCoords[z], textures.at(textures.size()-1)));
            } else if (sscanf(string, " %d//%d %d//%d %d//%d\r", &i, &a, &j, &b, &k, &c) == 6) {
                faces.push_back(Face(vertices[i],vertices[j],vertices[k],vertexNormals[a],vertexNormals[b],vertexNormals[c]));
            } else if (sscanf(string, "%d/%d %d/%d %d/%d", &i, &x, &j, &y, &k, &z) == 6) {
                faces.push_back(Face(vertices[i],vertices[j],vertices[k],textureCoords[x], textureCoords[y], textureCoords[z], textures.at(textures.size()-1)));
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
                
                if(segment != ""){
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
                
                if(segment != ""){
                    inputNums.push_back(stod(segment));
            
                }
            }
            Ray vertexNormalInput(inputNums);
            vertexNormals.push_back(vertexNormalInput);
        } else if (input == "texture"){
            std::getline(inputFile, input);
            textures.push_back(new Texture("texture/" + input.substr(1)));
        } else if (input == "vt"){
            std::getline(inputFile, input);
            std::stringstream inputString(input.substr(1));
            std::string segment;
            std::vector<double> inputNums;
            while(std::getline(inputString, segment, ' ')){
                
                if(segment != ""){
                    inputNums.push_back(stod(segment));
            
                }
            }
            double* vt = new double[2];
            vt[0] = inputNums[0];
            vt[1] = inputNums[1];
            textureCoords.push_back(vt);
        }
        
        
    }

    inputFile.close();
    if (inputCounter == 6 && (spheres.size() > 0 || faces.size()>0) && lights.size() > 0 && materials.size()>0){
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
    for (int i=0;i<materials.size();i++){
        std::cout << "mtlcolor ";
        printVector(materials.at(i).getMaterial());
    }
    for (int i=0;i<spheres.size();i++){
        if (spheres[i].hasTexture()){
            spheres.at(i).getLocation().print("sphere ");
            std::cout << "  texture " << spheres[i].getTexture()->getFilename() << std::endl;
        } else {
            spheres.at(i).getLocation().print("sphere ");
        }
        
    }
    for (int i=0;i<lights.size();i++){
        lights.at(i).print("light ");
    }
    for (int i=1;i<vertices.size();i++){
        vertices.at(i).print("v ");
    }
    for(int i=1;i<vertexNormals.size();i++){
        vertexNormals.at(i).print("vn ");
    }
    for(int i=1;i<textureCoords.size();i++){
        std::cout << "vt " << textureCoords[i][0] << " " << textureCoords[i][1] << std::endl;
    } 
    for (auto texture:textures){
        std::cout << "texture " << texture->getFilename() << std::endl;
    }
    
}

void Input::printVector(std::vector<double> input){
    for (int i=0;i<input.size();i++){
        std::cout << input.at(i) << " ";
    }
    std::cout << std::endl;
}

Input::~Input(){
    for (auto texture: textures){
        delete texture;
    }
    for (auto coord: textureCoords){
        delete coord;
    }
    
}