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
            std::string input;
            std::getline(inputFile, input);
            int width,height;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, " %d %d\r", &width, &height) == 2) {
                inputCounter++;
                imageSize.push_back(width);
                imageSize.push_back(height);
            } else {
                std::cout << "not found\n"; 
            }
            delete[] string;
        }
        else if (input == "eye"){
            std::string input;
            std::getline(inputFile, input);
            float i,j,k;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, " %f %f %f\r", &i, &j, &k) == 3) {
                inputCounter++;
                viewOrigin.push_back(i);
                viewOrigin.push_back(j);
                viewOrigin.push_back(k);
            } else {
                std::cout << "not found\n"; 
            }
            delete[] string;
            // viewOrigin = Input::getInputs();
            // inputCounter++;

        }
        else if (input == "viewdir"){
            std::string input;
            std::getline(inputFile, input);
            float i,j,k;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, " %f %f %f\r", &i, &j, &k) == 3) {
                inputCounter++;
                viewDir.push_back(i);
                viewDir.push_back(j);
                viewDir.push_back(k);
            } else {
                std::cout << "not found\n"; 
            }
            delete[] string;
            // viewDir = Input::getInputs();
            // inputCounter++;

        }
        else if (input == "hfov"){
            inputFile>>input;
            hFOV = stoi(input);
            inputCounter++;

        }
        else if (input == "updir"){
            std::string input;
            std::getline(inputFile, input);
            float i,j,k;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, " %f %f %f\r", &i, &j, &k) == 3) {
                inputCounter++;
                upDir.push_back(i);
                upDir.push_back(j);
                upDir.push_back(k);
            } else {
                std::cout << "not found\n"; 
            }
            delete[] string;
            // upDir = Input::getInputs();
            // inputCounter++;

        }
        
        else if (input == "bkgcolor"){
            // std::cout << "bkgcolor: " << std::endl;
            std::string input;
            std::getline(inputFile, input);
            float i,j,k;
            const int length = input.length();
            char* string = new char[length+1];
            strcpy(string,input.c_str());
            if (sscanf(string, " %f %f %f\r", &i, &j, &k) == 3) {
                inputCounter++;
                backgroundColor.push_back(i);
                backgroundColor.push_back(j);
                backgroundColor.push_back(k);
            } else {
                std::cout << "not found\n"; 
            }
            delete[] string;
            // backgroundColor = Input::getInputs();
            // inputCounter++;

        }
        else if (input == "mtlcolor"){
            std::vector<double> materialColor;
            materialColor = getInputs();
            materials.push_back(Material(materialColor));
        } else if (input == "sphere") {

            
            std::getline(inputFile, input);
            std::stringstream sphere(input.substr(1));
            std::string segment;
            std::vector<double> sphereNums;
            while(std::getline(sphere, segment, ' ')){
                
                if(segment != " "){
                    sphereNums.push_back(stod(segment));
            
                }
            }
                
            spheres.push_back(Sphere(Ray(sphereNums[0],sphereNums[1],sphereNums[2]),sphereNums[3]));
        } 
        else if (input == "light"){
            std::vector<double> lightInput = getInputs();
            if (lightInput.size() > 5){
                Ray position(lightInput[0],lightInput[1],lightInput[2]);
                LightSource newLight(position, lightInput[3], lightInput[4]);
                lights.push_back(newLight);
            }
        } else if (input == "attlight"){
            std::vector<double> lightInput = getInputs();
            if (lightInput.size() > 5){
                Ray position(lightInput[0],lightInput[1],lightInput[2]);
                LightSource newLight(position, lightInput[3], lightInput[4],lightInput[5],lightInput[6],lightInput[7]);
                lights.push_back(newLight);
            }
        } else if (input == "f") {
            std::string input;
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
            Ray vertexInput = getInputs();
            vertices.push_back(vertexInput);
        } else if (input == "vn") {
            Ray vertexNormalInput = getInputs();
            vertexNormals.push_back(vertexNormalInput);
        }
        
        // std::cout << input << "\n";
        
    }

    inputFile.close();
    if (inputCounter == 6 && (spheres.size() > 0 || faces.size()>0) && lights.size() > 0){
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
    
}

std::vector<double> Input::getInputs(){
    
    std::vector<double> output;
    std::string input;
    while (inputFile.peek() != '\n' && !inputFile.eof()){
        int holdPosition = inputFile.tellg();
        inputFile >> input;
        // std::cout << "   " << input;
        double doubleInput;
        
        try {
            doubleInput = stod(input);
            
        } catch (const std::invalid_argument&) {
            std::cout << "not a double\n";
            inputFile.seekg(holdPosition);
            break;
        } catch (const std::out_of_range&) {
            std::cout << "value out of range\n";
            inputFile.seekg(holdPosition);
            break;
        }
        output.push_back(doubleInput);
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
