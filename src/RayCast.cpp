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
    w = normalizeRay(Ray(inputFromUser->getViewDir())*-1);
    // w.print("w: ");
    // printVector(inputFromUser->getUpDir(), "upDir: ");
    u = normalizeRay(crossProduct(inputFromUser->getViewDir(), Ray(inputFromUser->getUpDir())));
    // u.print("u: ");
    v = normalizeRay(crossProduct(u, inputFromUser->getViewDir()));
    // v.print("v: ");

    viewWindowWidth = 2*viewingDistance*tan(degreesToRadians(0.5*inputFromUser->getHFOV()));
    // std::cout << "view window width: " << viewWindowWidth << std::endl;
    // aspectRatio = inputFromUser->getImageSize()[0]/inputFromUser->getImageSize()[1];
    // std::cout << "aspectRatio: " << aspectRatio << std::endl;
    viewWindowHeight = viewWindowWidth*(inputFromUser->getImageSize()[1]/inputFromUser->getImageSize()[0]);
    // std::cout << "view window height: " << viewWindowHeight << std::endl;
}

void RayCast::calcCorners(){
    Ray viewOrigin(inputFromUser->getViewOrigin());
    Ray A = viewOrigin;
    Ray B = viewingDistance*normalizeRay(inputFromUser->getViewDir());
    Ray C = u*(viewWindowWidth/2);
    Ray D = v*(viewWindowHeight/2);

    ul = A + B - C + D;
    ur = A + B + C + D;
    ll = A + B - C - D;
    lr = A + B + C - D;
}

void RayCast::calcViewRays(){
    double width = inputFromUser->getImageSize()[0];
    double height = inputFromUser->getImageSize()[1];
    Ray deltaH =(ur-ul)*(1/(width-1));
    // deltaH.print("deltaH: ");
    Ray deltaV =(ll-ul) * (1/(height-1));
    // deltaV.print("deltaV: ");
    // std::cout << "calculating rays" << std::endl;
    for(int j=0;j<height;j++){
        for (int i=0;i<width;i++){
            if (i == 194 && j == 252){
                int g = 9;
            }
            Ray viewWindowLocation = ul + (deltaV*(j)) + (deltaH*(i));
            Ray viewOrigin = inputFromUser->getViewOrigin();
            Ray rayDir = normalizeRay(viewWindowLocation - viewOrigin);
            double bgWeirdN = inputFromUser->getBackgroundColor()[3];
            Ray pixelColor = getPixelColor(rayDir, viewOrigin, 0, {bgWeirdN});
            userImage->modPixel(pixelColor[0],pixelColor[1],pixelColor[2],i,j);

        }
    }
}

Ray RayCast::getPixelColor(Ray input, Ray viewOrigin, int recursionDepth, std::vector<double> weirdNStack){
    Ray pixelColor = inputFromUser->getBackgroundColor();

    Intersection rayIntersection = *checkIntersections(input, viewOrigin);
    if (rayIntersection.getSuccessfulIntersect()){
        Material intersectMaterial = *rayIntersection.getMaterial();
        Ray intersectionPoint = *rayIntersection.getIntersectionPoint();
        double k0 = 0;
        double ks = intersectMaterial.getMaterial()[8];         
        if(intersectMaterial.getMaterial().size()>3){
            std::vector<LightSource> visibleLights = shadeRay(intersectionPoint);
            if (rayIntersection.getIsSphere()){
                Sphere interesectSphere = *rayIntersection.getIntersectSphere();
                
                if (intersectMaterial.getMaterial().size()>10 && recursionDepth <= recursionDepthLimit){
                    recursionDepth = recursionDepth + 1;
                    
                    Ray nVec = (normalizeRay((intersectionPoint-interesectSphere.getLocation())));
                    double alpha = intersectMaterial.getMaterial()[10];
                    bool exitingMaterial = false;
                    double inputAngle = acos(dotProduct(nVec, input*-1));
                    Ray tVec;
                    if (radiansToDegrees(inputAngle) > (90)){
                        nVec = nVec*-1;
                        exitingMaterial = true;
                        tVec = gettVec(nVec, input*-1, weirdNStack.back(), weirdNStack.at(weirdNStack.size()-2));
                        // std::cout<< "is exiting\n";
                    } else {
                        weirdNStack.push_back(intersectMaterial.getMaterial()[11]);
                        tVec = gettVec(nVec, input*-1, weirdNStack.at(weirdNStack.size()-2), weirdNStack.back());
                        // std::cout<<"is entering\n";
                    }

                    Ray specRay = specularReflectionRay(nVec,input*-1);
                    double k0 = pow((weirdNStack.back()-1)/(weirdNStack.back() + 1), 2);
                    double reflectanceFr = fresnelCoefficient(nVec, input*-1, k0);
                    
                    // if (sin(inputAngle) > (weirdNStack.back()/weirdNStack.at(weirdNStack.size()-2))){
                    if (isnan(tVec[0])){
                        // std::cout << "total internal reflection\n";
                        Ray specularReflection = (reflectanceFr*getPixelColor(specRay, intersectionPoint, recursionDepth, weirdNStack));
                        pixelColor = castLightSphere(interesectSphere, intersectionPoint, intersectMaterial, visibleLights) + specularReflection;

                    } else {
                        double refractionFr = fresnelCoefficient(nVec, input*-1, pow((weirdNStack.back()-weirdNStack.at(weirdNStack.size()-2))/(weirdNStack.back()+weirdNStack.at(weirdNStack.size()-2)),2));
                        
                        Ray specularReflection = (reflectanceFr*getPixelColor(specRay, intersectionPoint, recursionDepth, weirdNStack));
                        if (exitingMaterial){
                            weirdNStack.pop_back();
                        }
                        Ray refraction = ((1-refractionFr)*(1-alpha)*getPixelColor(tVec, intersectionPoint, recursionDepth, weirdNStack));
                        pixelColor = castLightSphere(interesectSphere, intersectionPoint, intersectMaterial, visibleLights) + specularReflection + refraction;

                    }
                     
                    
                } else {
                    pixelColor = castLightSphere(interesectSphere, intersectionPoint, intersectMaterial, visibleLights);
                }

            } else {
                Face intersectFace = *rayIntersection.getIntersectFace();
                if (intersectMaterial.getMaterial().size()>10 && recursionDepth <= recursionDepthLimit && ks > 0){
                    k0 = pow((weirdNStack.back()-1)/(weirdNStack.back() + 1), 2);
                    Ray p0 = intersectFace.getVertex(0);
                    Ray p1 = intersectFace.getVertex(1);
                    Ray p2 = intersectFace.getVertex(2);
                    Ray e1 = p1-p0;
                    Ray e2 = p2-p0;
                    Ray nVec = normalizeRay(crossProduct(e1,e2));
                    double fCoeff = fresnelCoefficient(nVec, input*-1, k0);
                    double k0;
                    if (intersectMaterial.getMaterial()[8] == 0){
                        k0 = 0;
                    }
                    recursionDepth = recursionDepth + 1;
                    pixelColor = castLightFace(intersectFace, intersectionPoint, intersectMaterial, visibleLights) + (fCoeff*getPixelColor(specularReflectionRay(nVec,input*-1), intersectionPoint, recursionDepth, weirdNStack));
                } else {
                    pixelColor = castLightFace(intersectFace, intersectionPoint, intersectMaterial, visibleLights);
                }

            }
        } else {
            pixelColor = {intersectMaterial.getMaterial()[0], intersectMaterial.getMaterial()[1], intersectMaterial.getMaterial()[2]};
        }
    }
    
    return pixelColor;

}



Ray RayCast::gettVec(Ray nVec, Ray input, double currWeridN, double newWeirdN){
    double nRatio = currWeridN/newWeirdN;
    double nDotI = dotProduct(nVec, input);
    double squareRoot = sqrt(1-(nRatio*nRatio)*(1-(nDotI*nDotI)));
    // if (isnan(squareRoot)){
    //     std::cout << "not a number\n";
    // }
    return normalizeRay((nVec*-1)*squareRoot+nRatio*((nDotI*nVec - input)));
}

Intersection* RayCast::checkIntersections(Ray input, Ray viewOrigin){
    std::vector<Material> materials = inputFromUser->getMaterials();
    Intersection* output;
    std::vector<double> distance = checkSphereIntersection(input, viewOrigin);
    std::vector<double> faceDistance = checkFaceIntersection(input, viewOrigin);
    distance.insert(distance.end(), faceDistance.begin(), faceDistance.end());

    double least = -1;
    int leastIndex;
    for(int i=0;i<distance.size();i++){
        if (distance.at(i) >= 0){
            if (distance.at(i) < least || least == -1){
                least = distance.at(i);
                leastIndex = i;
                
            }
        }
    }

    if (least == -1){
        return new Intersection();
        
    } else {
        Ray intersectPoint = viewOrigin + (normalizeRay(input)*least);
        int spheresSize = inputFromUser->getSpheres().size();
        if (leastIndex > (spheresSize)-1){//face
            std::vector<double> outMaterial = materials[materials.size()-1].getMaterial();
            Material* outputMaterial = new Material(outMaterial);
            Face* outputFace = new Face(inputFromUser->getFaces()[leastIndex - (spheresSize)]);
            Ray* outputRay = new Ray(intersectPoint);
            return new Intersection( outputRay, outputMaterial,outputFace);
        } else {//sphere
            std::vector<double> outMaterial = materials[leastIndex].getMaterial();
            Material* outputMaterial = new Material(outMaterial);
            Sphere* outputSphere = new Sphere(inputFromUser->getSpheres()[leastIndex]);
            Ray* outputRay = new Ray(intersectPoint);
            return new Intersection( outputRay, outputMaterial, outputSphere);
        }
    }
}

std::vector<double> RayCast::checkFaceIntersection(Ray ray, Ray viewOrigin){
    std::vector<Face> faces = inputFromUser->getFaces();
    std::vector<Ray> vertices = inputFromUser->getVertices();
    std::vector<double> distances;
    double error = 1.0e-10;
    for (auto face:faces){

        //define triangle plane
        Ray p0 = face.getVertex(0);
        Ray p1 = face.getVertex(1);
        Ray p2 = face.getVertex(2);
        Ray e1 = p1-p0;
        Ray e2 = p2-p0;
        Ray n = normalizeRay(crossProduct(e1,e2));
        double A = n[0];
        double B = n[1];
        double C = n[2];
        double D = 0-((A*p0[0]) + (B*p0[1]) + (C*p0[2]));

        Ray xd = ray;
        Ray x0 = viewOrigin;
        double t;
        double denominator = A*xd[0] + B*xd[1] + C*xd[2];
        if (fabs(denominator) < error){
            distances.push_back(-1);
            continue;
        } else {
            t = -(A*x0[0] + B*x0[1] + C*x0[2] + D)/(denominator);
        }

        Ray p = x0 + xd*t;

        if(checkPointOnFace(viewOrigin, e1, e2, p0, error).empty()){//if viewOrigin is on current face
            if (!checkPointOnFace(p, e1, e2, p0, error).empty()){
                distances.push_back(distance(viewOrigin, p));
            } else {
                distances.push_back(-1);
            }
        } else {
            distances.push_back(-1);
        }
        
        // if(baryCoords[0] < error || baryCoords[1] < error || baryCoords [0] > 1 || baryCoords[1] > 1){
        //     distances.push_back(-1);
        // } else {
            
        // }

    }
    return distances;
}

std::vector<double> RayCast::checkPointOnFace(Ray p, Ray e1, Ray e2, Ray p0, double error){
    Ray ep = p - p0;
    double d11 = dotProduct(e1,e1);
    double d22 = dotProduct(e2,e2);
    double d12 = dotProduct(e1,e2);
    double d1p = dotProduct(e1,ep);
    double d2p = dotProduct(e2,ep);

    std::vector<double> baryCoords = matrixSolver(d11,d12,d1p,d12,d22,d2p);
    baryCoords.push_back(1 - (baryCoords[0]+baryCoords[1]));
    
    for (auto coord: baryCoords){
        if (coord > (1-error) || coord < error){
            std::vector<double> empty;
            return empty;
        }
    }
    return baryCoords;
}

std::vector<double> RayCast::checkSphereIntersection(Ray input, Ray viewOrigin){
    std::vector<Sphere> spheres = inputFromUser->getSpheres();
    // std::vector<double> viewOrigin = inputFromUser->getViewOrigin();
    std::vector<double> distance;
    double error = 1.0e-10;
    for (int i=0;i<spheres.size();i++){

        //check if viewOrigin is on current sphere. if so, skip calculations
        // if (fabs((pow((viewOrigin[0]-spheres[i].getLocation()[0]),2) + pow((viewOrigin[1]-spheres[i].getLocation()[1]),2) + pow((viewOrigin[2]-spheres[i].getLocation()[2]),2)) - pow(spheres[i].getRadius(),2)) < error){
        //     distance.push_back(-1);
        //     continue;
        // }

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

    return distance;
}

Ray RayCast::castLightSphere(Sphere sphereAtRay, Ray intersectPos, Material matAtRay, std::vector<LightSource> lights){
    Ray colorSum;
    Ray nVec = (normalizeRay((intersectPos-sphereAtRay.getLocation())*(1/sphereAtRay.getRadius())));

    if (sphereAtRay.hasTexture()){
        double phi = acos((intersectPos[2]-sphereAtRay.getLocation()[2])/sphereAtRay.getRadius());
        double theta = atan2((intersectPos[1] - sphereAtRay.getLocation()[1]), (intersectPos[0]-sphereAtRay.getLocation()[0]));
        double v = phi/M_PI;
        if (theta < 0){
            theta = theta + (2*M_PI);
        } 
        double u = theta/(2*M_PI);
        // std::cout << "u: " << u << " v: " << v << std::endl;
        // printVector(sphereAtRay.getTexture()->getPixel(u,v), "  texture color: ");
        matAtRay.calcTextureCoefficients(Ray(sphereAtRay.getTexture()->getPixel(u,v))*(1.0/255.0));
    } 

    for (auto light:lights){
        Ray lVec;
        if(light.isDirectional()){
            lVec = (normalizeRay(light.getPosition()*-1));
        } else {
            lVec = (normalizeRay(light.getPosition()-intersectPos));
        }
        
        Ray vVec = normalizeRay(inputFromUser->getViewOrigin()-intersectPos);
        Ray hVec = normalizeRay((lVec+vVec));
        
            
        colorSum = colorSum + (((matAtRay.KdOdLam*min(0,dotProduct(nVec,lVec))) + (matAtRay.KsOsLam*pow(min(0,dotProduct(nVec,hVec)),matAtRay.n)))*light.getIntensity()*light.getAttenFactor(distance(light.getPosition(),intersectPos)));
        
    }
    colorSum = colorSum + matAtRay.KaOdLam;
    return colorSum;
}

Ray RayCast::castLightFace(Face faceAtRay, Ray intersectPos, Material matAtRay, std::vector<LightSource> lights){
    
    Ray p0 = faceAtRay.getVertex(0);
    Ray p1 = faceAtRay.getVertex(1);
    Ray p2 = faceAtRay.getVertex(2);
    Ray e1 = p1-p0;
    Ray e2 = p2-p0;
    Ray nVec = normalizeRay(crossProduct(e1,e2));

    if (faceAtRay.hasNormals() || faceAtRay.hasTexture()){
        std::vector<double> baryCoords = checkPointOnFace(intersectPos, e1, e2, p0, 1e-10);
        if (faceAtRay.hasNormals()){
            nVec = normalizeRay(faceAtRay.getNormal(0)*baryCoords[2] + faceAtRay.getNormal(1)*baryCoords[0] + faceAtRay.getNormal(2)*baryCoords[1]);
        }
        if (faceAtRay.hasTexture()){
            std::vector<double*> textureCoords = {faceAtRay.getTextureCoords(0), faceAtRay.getTextureCoords(1), faceAtRay.getTextureCoords(2)};
            double u = baryCoords[2]*textureCoords[0][0] + baryCoords[0]*textureCoords[1][0] + baryCoords[1]*textureCoords[2][0];
            double v = baryCoords[2]*textureCoords[0][1] + baryCoords[0]*textureCoords[1][1] + baryCoords[1]*textureCoords[2][1];
            matAtRay.calcTextureCoefficients(Ray(faceAtRay.getTexture()->getPixel(u,v))*(1.0/255.0));
        }  
    }
    
    std::vector<double> output = inputFromUser->getBackgroundColor();
    Ray colorSum;
    for (auto light:lights){
        Ray lVec;
        if(light.isDirectional()){
            lVec = (normalizeRay(light.getPosition()*-1));
        } else {
            lVec = (normalizeRay(light.getPosition()-intersectPos));
        }
        
        Ray vVec = normalizeRay(inputFromUser->getViewOrigin()-intersectPos);
        Ray hVec = normalizeRay((lVec+vVec));
        
        colorSum = colorSum + (((matAtRay.KdOdLam*min(0,dotProduct(nVec,lVec))) + (matAtRay.KsOsLam*pow(min(0,dotProduct(nVec,hVec)),matAtRay.n)))*light.getIntensity()*light.getAttenFactor(distance(light.getPosition(),intersectPos)));
    }
    
    colorSum = colorSum + matAtRay.KaOdLam;
    return colorSum;
}

Ray RayCast::specularReflectionRay(Ray surfaceNormal, Ray rayIn){
    return normalizeRay((2*dotProduct(rayIn, surfaceNormal)*surfaceNormal) - rayIn);
}

double RayCast::fresnelCoefficient(Ray surfaceNormal, Ray rayIn, double f0){
    return f0 + (1 - f0)*pow(1-dotProduct(surfaceNormal, rayIn),5);
}

std::vector<LightSource> RayCast::shadeRay(Ray intersectPos){
    // std::vector<double> output(3);
    // Ray colorSum;
    std::vector<LightSource> visibleLights;
    std::vector<LightSource> lights = inputFromUser->getLights();
    // return lights;
    for (auto light:lights) {
        Ray lVec;
        if(light.isDirectional()){
            lVec = (normalizeRay(light.getPosition()*-1));
        } else {
            lVec = (normalizeRay(light.getPosition()-intersectPos));
        }
        if (light.isDirectional()){
            visibleLights.push_back(light);
        } else {
            Intersection* nearestObject = checkIntersections(lVec, intersectPos);
            if (nearestObject->getSuccessfulIntersect()){
                double pointToObject = distance(*(*nearestObject).getIntersectionPoint(),intersectPos);

                if (distance(*(*nearestObject).getIntersectionPoint(),intersectPos) > distance(light.getPosition(), intersectPos)){
                    visibleLights.push_back(light);
                }
            } else {
                visibleLights.push_back(light);
            }
        }
    }

    return visibleLights;

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
    output[0] = a[1] * b[2] - a[2] * b[1];
    output[1] = -(a[0] * b[2] - a[2] * b[0]);
    output[2] = a[0] * b[1] - a[1] * b[0];

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

std::vector<double> RayCast::matrixSolver(double a, double b, double e, double c, double d, double f){
    double determinant = a*d - b*c;
    if(determinant != 0) {
        double x = (e*d - b*f)/determinant;
        double y = (a*f - e*c)/determinant;
        return {x,y};
    } else {
        return {-1, -1}; 
    }

}