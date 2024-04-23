#include"../include/VectorCurve.hpp"



//2D curves



std::vector<Dmath::Vec2D> Dmath::VectorCurve2D::createVectorialCurve(){
    std::vector<Dmath::Vec2D> output;
    int iterations = 0;
    for(float i = this->systemStart; i<systemStopp; i+=resolution){
        if(i == this->systemStart){
            output.push_back(Dmath::Vec2D(this->xFunc(i),this->yFunc(i),0,0));
            iterations++;
        } else {

            output.push_back(Dmath::Vec2D(this->xFunc(i),this->yFunc(i),output[iterations-1].getX(),output[iterations-1].getY()));
            iterations++;
        }
    }
    return output;
}



Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc)
    : VectorAnalysis2D(xFunc,yFunc) {
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve2D::VectorCurve2D(std::function<float(float)> xFunc,std::function<float(float)> yFunc, float start, float stopp, float res)
    : VectorAnalysis2D(xFunc,yFunc,resolution,systemStart,systemStopp){
    this->mainCurve = this->createVectorialCurve();
    
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY ){
    return Dmath::VectorCurve2D(funcX,funcY);
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,float start,float stopp,float res ){
    return Dmath::VectorCurve2D(funcX,funcY,start,stopp,res);
}


Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromPoint(float point){
    if(point > this->systemStart || point < this->systemStopp){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
            return Dmath::Vec2D::zeroVector();
        }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec2D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}

Dmath::Vec2D Dmath::VectorCurve2D::getVectorFromFunction(float vecX, float vecY){
    float xValue = this->xFunc(vecX);
    float yValue = this->yFunc(vecY);
    Dmath::Vec2D outputVector(xValue, yValue);
    return outputVector;
}


Dmath::Vec2D Dmath::VectorCurve2D::tangentVector(float t){
    float h = 0.000001; 
    float x_t_plus_h = this->xFunc(t + h);
    float x_t_minus_h = this->xFunc(t - h);
    float y_t_plus_h = this->yFunc(t + h);
    float y_t_minus_h = this->yFunc(t - h);

    float dx = (x_t_plus_h - x_t_minus_h) / (2 * h); 
    float dy = (y_t_plus_h - y_t_minus_h) / (2 * h); 

    return Dmath::Vec2D(dx, dy); 
}

float Dmath::VectorCurve2D::curveLenght(){
        float lenght = 0;
        for(int i = 0; i<this->mainCurve.size(); i++){
            std::cout << this->mainCurve[i].getAbs() <<std::endl;
            lenght += this->mainCurve[i].getAbs();
        }
        lenght = lenght*resolution;
        return lenght;
    }

float Dmath::VectorCurve2D::maximumY(){
    float maxY = 0;
    for(size_t i = 0; i<this->mainCurve.size(); i++){
        if(this->mainCurve[i].getY() > maxY){
            maxY = this->mainCurve[i].getY();
        } else {
            continue;
        }
    }
    return maxY;
}


float Dmath::VectorCurve2D::minimumY(){
      float minY = 9999999;
      for(int i = 0; i<this->mainCurve.size(); i++){
        if(this->mainCurve[i].getY() < minY){
          minY = this->mainCurve[i].getY();
        } else {
          continue;
        }
      }
      return minY;
    }

float Dmath::VectorCurve2D::MaximumX(){
    float maxX = 0;
    for(size_t i = 0 ; i<this->mainCurve.size(); i++){
        if(this->mainCurve[i].getX() > maxX){
            maxX = this->mainCurve[i].getX();
        } else {
            continue;
        }
    }
    return maxX;
}

float Dmath::VectorCurve2D::calculateSlopeOnPoint(float t){
    Dmath::Vec2D vec = this->tangentVector(t);
    float result = 0;
    if(vec.getY() != 0){
        result = vec.getX() / vec.getY();
    } else {
        return 0;
    }
    return result; 
}




float Dmath::VectorCurve2D::dotProductVectorCurve(Dmath::VectorCurve2D vec){
    float curveOneStart = this->getStart();
    float curveTwoStart = vec.getStart();
    float curveOneEnd   = this->getEnd();
    float curveTwoEnd   = vec.getEnd();
    float dotProduct    = 0;

    size_t startIdx = 0;
    size_t endIdx = std::min(this->mainCurve.size(), vec.mainCurve.size());

    // Bestimme den Startindex basierend auf den Startpunkten der Kurven
    if (curveOneStart >= curveTwoStart) {
        startIdx = curveOneStart;
    } else {
        startIdx = curveTwoStart;
    }
    // Bestimme den Endindex basierend auf den Endpunkten der Kurven
    if (curveOneEnd <= curveTwoEnd) {
        endIdx = curveOneEnd;
    } else {
        endIdx = curveTwoEnd;
    }
    // Berechne das Skalarprodukt für den relevanten Bereich der Kurven
    for (size_t i = startIdx; i < endIdx; i++) {
        dotProduct += this->mainCurve[i].dotProduct(vec.mainCurve[i]);
    }
    return dotProduct;
}

float Dmath::VectorCurve2D::minimumX(){
    float minX = 9999999;
    for(int i = 0; i<this->mainCurve.size(); i++){
        if(this->mainCurve[i].getX() < minX){
            minX = this->mainCurve[i].getX();
        } else {
            continue;
        }
    }
    return minX;
}

Dmath::VectorCurve2D Dmath::VectorCurve2D::addCurve(Dmath::VectorCurve2D curve){
    float mainCurveEnd  = this->getEnd();
    float otherCurveEnd = this->getEnd();
    float newCurveEnd   = TWOPI;

    float mainCurveStart  = this->getStart();
    float otherCurveStart = this->getStart();
    float newCurveStart   = 0;

    if( mainCurveEnd >= otherCurveEnd ){
    newCurveEnd = otherCurveEnd;
    } 
    if(mainCurveStart >= otherCurveStart){
    newCurveStart = mainCurveStart;
    }

    auto newX = [this,&curve](float t) -> float { return this->xFunc(t) + curve.xFunc(t); };
    auto newY = [this,&curve](float t) -> float { return this->yFunc(t) + curve.yFunc(t); };

    return VectorCurve2D(newX,newY,mainCurveStart,mainCurveEnd,0.1);
}


//3D curves

float Dmath::VectorCurve3D::dotProductVectorCurve(Dmath::VectorCurve3D vec) {

    float curveOneStart = this->getStart();
    float curveTwoStart = vec.getStart();
    float curveOneEnd   = this->getEnd();
    float curveTwoEnd   = vec.getEnd();
    float dotProduct    = 0;

    size_t startIdx = 0;
    size_t endIdx = std::min(this->mainCurve.size(), vec.mainCurve.size());

    // Bestimme den Startindex basierend auf den Startpunkten der Kurven
    if (curveOneStart >= curveTwoStart) {
        startIdx = curveOneStart;
    } else {
        startIdx = curveTwoStart;
    }
    // Bestimme den Endindex basierend auf den Endpunkten der Kurven
    if (curveOneEnd <= curveTwoEnd) {
        endIdx = curveOneEnd;
    } else {
        endIdx = curveTwoEnd;
    }
    // Berechne das Skalarprodukt für den relevanten Bereich der Kurven
    for (size_t i = startIdx; i < endIdx; i++) {
        dotProduct += this->mainCurve[i].dotProduct(vec.mainCurve[i]);
    }
    return dotProduct;
}

std::vector<Dmath::Vec3D> Dmath::VectorCurve3D::createVectorialCurve(){
    std::vector<Dmath::Vec3D> output;
    int iterations = 0;
    for(float i = this->systemStart; i<systemStopp; i+=resolution){
        if(i == this->systemStart){
            output.push_back(Dmath::Vec3D(this->xFunc(i),this->yFunc(i), this->zFunc(i),0,0,0));
            iterations++;
        } else {
            output.push_back(Dmath::Vec3D(this->xFunc(i),this->yFunc(i),this->zFunc(i),output[iterations-1].getX(),output[iterations-1].getY(),output[iterations-1].getZ()));
            iterations++;
        }
    }
    return output;
}



Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc)
: VectorAnalysis3D(xFunc,yFunc,zFunc){


    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve3D::VectorCurve3D(std::function<float(float)> xFunc,std::function<float(float)> yFunc,std::function<float(float)> zFunc, float start, float stopp, float res)
: VectorAnalysis3D(xFunc,yFunc,zFunc,systemStart,systemStopp,resolution){
    
    this->mainCurve = this->createVectorialCurve();
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createStandardCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc);
}

Dmath::VectorCurve3D Dmath::VectorCurve3D::createCustomCurve(std::function<float(float)> funcX,std::function<float(float)> funcY,std::function<float(float)> zFunc, float start,float stopp,float res ){
    return Dmath::VectorCurve3D(funcX,funcY,zFunc,start,stopp,res);
}

Dmath::Vec3D  Dmath::VectorCurve3D::getVectorFromFunction(float xValue, float yValue, float zValue) {
    float vecX = this->xFunc(xValue);
    float vecY = this->yFunc(yValue);
    float vecZ = this->zFunc(zValue);
    Dmath::Vec3D outputVector(vecX,vecY,vecZ);
    return outputVector;
}

Dmath::Vec3D Dmath::VectorCurve3D::getVectorFromPoint(float point)  {
    if(point > this->systemStart || point < this->systemStopp){
        std::cerr << "Error index out of limit! \n Returning a null vector \n" ;
        return Dmath::Vec3D::zeroVector();
    }
    int foundPoint = static_cast<int> (point/this->resolution);
    Dmath::Vec3D outputVector = this->mainCurve[foundPoint];
    return outputVector;
}


Dmath::Vec3D  Dmath::VectorCurve3D::tangentVector(float t){
    float h = 0.00000001; // Kleine Schrittweite
    float x_t_plus_h = this->xFunc(t + h);
    float x_t_minus_h = this->xFunc(t - h);
    float y_t_plus_h = this->yFunc(t + h);
    float y_t_minus_h = this->yFunc(t - h);
    float z_t_plus_h = this->zFunc(t + h);
    float z_t_minus_h = this->zFunc(t - h);

    // Überprüfung, ob die Funktionswerte positiv oder negativ sind
    bool x_positive = (x_t_plus_h >= 0) && (x_t_minus_h >= 0);
    bool y_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);
    bool z_positive = (y_t_plus_h >= 0) && (y_t_minus_h >= 0);

    // Berechnung des Tangentialvektors
    float dx = (x_t_plus_h - x_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von x nach t
    float dy = (y_t_plus_h - y_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von y nach t
    float dz = (z_t_plus_h - z_t_minus_h) / (2 * h); // Zentrale Differenz für die Ableitung von y nach t
    // Wenn die Funktionswerte negativ sind, invertiere den Tangentialvektor
    if (!x_positive) dx = -dx;
    if (!y_positive) dy = -dy;

    return Dmath::Vec3D(dx, dy,dz); // Tangentialvektor
}


float Dmath::VectorCurve3D::curveLenght(){
    float lenght = 0;
    for(int i = 0; i<this->mainCurve.size(); i++){
        lenght += this->mainCurve[i].getAbs();
    }
    return lenght;
}

float Dmath::VectorCurve3D::calculateSlopeXOnPoint(float t){
    Dmath::Vec3D vec = this->tangentVector(t);
    float result = 0;
    if(vec.getX() != 0){
        result = vec.getZ() /vec.getX() ;
    } else {
        return 0;
    }
    return result; 
}


float Dmath::VectorCurve3D::calculateSlopeYOnPoint(float t){
    Dmath::Vec3D vec = this->tangentVector(t);
    float result = 0;
    if(vec.getY() != 0){
        result = vec.getZ() /vec.getY();
    } else {
        return 0;
    }
    return result; 
}