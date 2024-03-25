#include "Input.h"
#include <iostream>
#include "Output.h"
#include "RayCast.h"



int main(int argc, char *argv[]){
    //handling incorrect number of arguments
    if (argc<2){
        std::cout << "Not enough arguments. Please enter a file name to read from." << std::endl;
        return -1;
    } else if (argc > 2){
        std::cout << "Too many arguments! Please only enter a file name to read from." << std::endl;
        return -1;
    }

    Input userInput(argv[1]);

    if (!userInput.getIsComplete()){
        std::cout << "Invalid input file. Please make sure all components of a scene are defined." << std::endl;
        return -1;
    }
    userInput.printInput();

    Output image(userInput);
    RayCast rayCaster(userInput, image);

    image.generateImage();
    std::cout << "done\n";
    userInput.~Input();
    // image.~Output();
    rayCaster.~RayCast();
    return 0;
}

