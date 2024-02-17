#include "RayCast.h"

RayCast::RayCast(Input userInput, Output image){
    
    inputFromUser = &userInput;
    userImage = &image;
    std::cout << "calc image" << std::endl;
    calcViewingWindow();
    calcCorners();
    calcViewRays();
    
}

void RayCast::calcViewingWindow(){
    w = normalizeRay(inputFromUser->getViewDir())*-1;
    // w.print("w: ");
    // printVector(inputFromUser->getUpDir(), "upDir: ");
    u = normalizeRay(crossProduct(inputFromUser->getViewDir(), inputFromUser->getUpDir()));
    // u.print("u: ");
    v = normalizeRay(crossProduct(u, inputFromUser->getViewDir()));
    // v.print("v: ");

    viewWindowWidth = 2*viewingDistance*tan(degreesToRadians(0.5*inputFromUser->getHFOV()));
    // std::cout << "view window width: " << viewWindowWidth << std::endl;
    aspectRatio = inputFromUser->getImageSize()[0]/inputFromUser->getImageSize()[1];
    // std::cout << "aspectRatio: " << aspectRatio << std::endl;
    viewWindowHeight = viewWindowWidth*(1/aspectRatio);
    // std::cout << "view window height: " << viewWindowHeight << std::endl;
}

void RayCast::calcCorners(){
    Ray viewOrigin(inputFromUser->getViewOrigin());
    Ray viewDir(inputFromUser->getViewDir());
    viewDir = normalizeRay(viewDir);
    ll = viewOrigin + (viewDir*viewingDistance) - (u*(viewWindowWidth/2)) - (v*(viewWindowHeight/2));
    // ll.print("ll: ");
    ul = viewOrigin + (viewDir*viewingDistance) - (u*(viewWindowWidth/2)) + (v*(viewWindowHeight/2));
    // ul.print("ul: ");
    lr = viewOrigin + (viewDir*viewingDistance) + (u*(viewWindowWidth/2)) - (v*(viewWindowHeight/2));
    // lr.print("lr: ");
    ur = viewOrigin + (viewDir*viewingDistance) + (u*(viewWindowWidth/2)) + (v*(viewWindowHeight/2));
    // ur.print("ur: ");
}

void RayCast::calcViewRays(){
    double width = inputFromUser->getImageSize()[0];
    double height = inputFromUser->getImageSize()[1];
    Ray deltaH =(ur-ul)*(1/(width-1));
    // deltaH.print("deltaH: ");
    Ray deltaV =(ll-(ul)) * (1/(height-1));
    // deltaV.print("deltaV: ");
    // std::cout << "calculating rays" << std::endl;
    for(int j=0;j<height;j++){
        for (int i=0;i<width;i++){
            
            std::vector<double> pixelColor = checkSpheres(normalizeRay(ul + (deltaV*(j)) + (deltaH*(i))), inputFromUser->getViewOrigin());
            userImage->modPixel(pixelColor[0],pixelColor[1],pixelColor[2],i,j);

        }
    }
    
}

std::vector<double> RayCast::checkSpheres(Ray input, Ray viewOrigin){
    std::vector<double> pixelColor = inputFromUser->getBackgroundColor();
    std::vector<Sphere> spheres = inputFromUser->getSpheres();
    std::vector<double> distance;
    double error = 1.0e-10;
    for (int i=0;i<spheres.size();i++){
        //check if viewOrigin is on current sphere. if so, skip calculations
        if ((pow((viewOrigin[0]-spheres[i].getLocation()[0]),2) + pow((viewOrigin[1]-spheres[i].getLocation()[1]),2) + pow((viewOrigin[2]-spheres[i].getLocation()[2]),2)) == pow(spheres[i].getRadius(),2)){
            distance.push_back(-1);
            continue;
        }

        Ray aTemp = input;
        aTemp.square();

        double A = aTemp.sum();
        double B = (input*(viewOrigin+(spheres.at(i).getLocation()*-1))).sum()*2;

        Ray cTemp = (viewOrigin+(spheres.at(i).getLocation()*-1));
        cTemp.square();
        double C =  cTemp.sum() - pow(spheres.at(i).getRadius(),2);
        double minus = (-B-sqrt((B*B)-(4*C*A)))/(2*A);
        double plus = (-B+sqrt((B*B)-(4*C*A)))/(2*A);
        if(plus >= error && minus >= error){
            if (plus >= minus){
                distance.push_back(minus);
            } else {
                distance.push_back(plus);
            }
        } else if (plus >= error){
            distance.push_back(plus);
        } else if (minus >= error){
            distance.push_back(minus);
        } else {
            distance.push_back(-1);
        }
    }
    double least = -1;
    int leastIndex;
    for(int i=0;i<spheres.size();i++){
        if (distance.at(i) >= 0){
            if (distance.at(i) < least || least == -1){
                least = distance.at(i);
                leastIndex = i;

            }
        }
    }
    
    if (viewOrigin == inputFromUser->getViewOrigin()){
        if (least >= 0){
            pixelColor = spheres.at(leastIndex).getMaterial();
            if (pixelColor.size() > 3){
                //calc phong illumination
                Ray intersectPos = viewOrigin+(input*distance[leastIndex]);
                pixelColor = shadeRay(spheres.at(leastIndex), intersectPos);
            }
        }
    } else {
        if (least!=-1){
            pixelColor = {(distance[leastIndex])};
        }
    }
    
    return pixelColor;
}

std::vector<double> RayCast::shadeRay(Sphere sphereAtRay, Ray intersectPos){
    std::vector<double> output(3);
    Ray colorSum;
    std::vector<LightSource> lights = inputFromUser->getLights();

    for (auto light:lights){
        Ray lVec;
        if(light.isDirectional()){
            lVec = (normalizeRay(light.getPosition()*-1));
        } else {
            lVec = (normalizeRay(light.getPosition()-intersectPos));
        }
        std::vector<double> nearestSphere = checkSpheres(lVec, intersectPos);
        if (nearestSphere.size()==1){
            if (nearestSphere[0] < distance(light.getPosition(), intersectPos) && !light.isDirectional()){
                continue;
            } else if (light.isDirectional()){
                continue;
            }
        } 

        Ray nVec = (normalizeRay((intersectPos-sphereAtRay.getLocation())*(1/sphereAtRay.getRadius())));
        Ray vVec = normalizeRay(inputFromUser->getViewOrigin()-intersectPos);
        Ray hVec = normalizeRay((lVec+vVec));
        
        colorSum = colorSum + (((sphereAtRay.KdOdLam*min(0,dotProduct(nVec,lVec))) + (sphereAtRay.KsOsLam*pow(min(0,dotProduct(nVec,hVec)),sphereAtRay.n)))*light.getIntensity()*light.getAttenFactor(distance(light.getPosition(),intersectPos)));
    }

    colorSum = colorSum + sphereAtRay.KaOdLam;
    output[0] = colorSum[0];
    output[1] = colorSum[1];
    output[2] = colorSum[2];

    return output;
}

Ray RayCast::normalizeRay(Ray input){
    Ray temp = input;
    temp.square();
    double norm = sqrt(temp.sum());
    
    return (input * (1/norm));
}

Ray RayCast::crossProduct(Ray a, Ray b){
    // std::cout << "  a: ";
    // printRay(a);
    // std::cout << "  b: ";
    // printRay(b);
    std::vector<double> output(3);
    // std::cout << "  cross product: ";
    output[0] = (a[1]*b[2])-(a[2]*b[1]);
    // std::cout << output[0] << " ";
    output[1] = -(a[2]*b[0])-(a[0]*b[2]);
    // std::cout << output[1] << " ";
    output[2] = (a[0]*b[1])-(a[1]*b[0]);
    // std::cout << output[2] << " " << std::endl;
    return Ray(output);
}

void RayCast::printVector(std::vector<double> input, std::string message){
    std::cout << message;
    for (int i=0;i<input.size();i++){
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;
}

double RayCast::degreesToRadians(double degrees){
    return degrees*(M_PI/180);
}
        
double RayCast::radiansToDegrees(double radians){
    return radians*(180/M_PI);
}

double RayCast::dotProduct(Ray a, Ray b){
    double sum = 0;
    for (int i=0;i<3;i++){
        sum += a[i]*b[i];
    }
    return sum;
}

double RayCast::min(double minimum, double input){
    if (input < minimum){
        return minimum;
    } else {
        return input;
    }
}

double RayCast::distance(Ray a, Ray b){
    double output;
    for (int i=0;i<3;i++){
        output = output + pow(a[i]-b[i],2);
    }
    return sqrt(output);
}