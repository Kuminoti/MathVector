#include"../include/mathVector.hpp"

using namespace Dvec;
// Helper functions:

#ifdef POLAR_IS_STANDARD
Vec2D::Vec2D(float radius, float angle){
    this->radius = radius;
    this->angle  =  angle;
    this->polarToCartesian();
    this->abs = calcAbs();
}

#endif

#ifdef CARTESIAN_IS_2D_STANDARD
Vec2D::Vec2D(float X, float Y) {
    this->X = X;
    this->Y = Y;
    this->cartesianToPolar();
    this->abs = calcAbs();
}
#endif 


// Pythagorean theorem for 2D vectors
float pyth2D(float x, float y){
    return std::sqrt((x*x)+(y*y));
}

// Pythagorean theorem for 3D vectors
float pyth3D(float x, float y, float z){
    return std::sqrt((x*x)+(y*y)+(z*z));
}

// Calculate cosine of the angle between two vectors
float cosAngle(float dotProduct, float absProduct) {
    return dotProduct / absProduct;
}

// Calculate angle in degrees from cosine value
float angleFromCos(float cosTheta) {
    return std::acos(cosTheta) * 180 / PI;
}

// Vec2D functions:




float Vec2D::polarSystemArea(){
    return PI * (this->radius * this->radius);
}

float Vec2D::polarSystemCircumfrance(){
    return TWOPI * this->radius;
}

void Vec2D::polarToCartesian(){
    this->X = radius * std::cos(this->phi);
    this->Y = radius * std::sin(this->phi);
}

void Vec2D::cartesianToPolar(){
    this->radius = calcAbs(); 
    this->phi = std::atan2(this->Y, this->X); 
}

void Vec2D::setX(float value){
    this->X = value;
    cartesianToPolar();
}

void Vec2D::setY(float value){
    this->Y = value;
    cartesianToPolar();
}

void Vec2D::setPhi(float value){
    this->phi = value;
    polarToCartesian();
}

void Vec2D::setRadius(float value){
    this->radius = value;
    polarToCartesian();
}

float Vec2D::calcAngle(Vec2D Mathvector){
    float product = this->dotProduct(Mathvector);
    float absProduct = this->getAbs() * Mathvector.getAbs();
    float cosTheta = cosAngle(product, absProduct);
    return angleFromCos(cosTheta);
}

float Vec2D::calcAbs() {
    return pyth2D(this->X, this->Y);
}

float Vec2D::lenght() { return this->calcAbs(); }



float Vec2D::dotProduct(Vec2D Mathvector) {
    return this->X * Mathvector.X + this->Y * Mathvector.Y;
}

Vec2D Vec2D::add(Vec2D Mathvector) {
    return Vec2D(this->X + Mathvector.X, this->Y + Mathvector.Y);
}

Vec2D Vec2D::subtract(Vec2D Mathvector) {
    return Vec2D(this->X - Mathvector.X, this->Y - Mathvector.Y);
}

Vec2D Vec2D::polarVector(float radius, float angle){
    float xValue = radius*std::cos(angle);
    float yValue = radius*std::sin(angle);
    return Vec2D(xValue,yValue);
}

// Vec3D functions:

float Vec3D::calcAngle(Vec3D Mathvector){
    float product = this->dotProduct(Mathvector);
    float absProduct = this->getAbs() * Mathvector.getAbs();
    float cosTheta = cosAngle(product, absProduct);
    return angleFromCos(cosTheta);
}

float Vec3D::calcAbs() {
    return pyth3D(this->X, this->Y, this->Z);
}

float Vec3D::dotProduct(Vec3D Mathvector) {
    return this->X * Mathvector.X + this->Y * Mathvector.Y +
           this->Z * Mathvector.Z;
}

Vec3D Vec3D::vecProduct(Vec3D Mathvector) {
    double resultX = this->Y * Mathvector.Z - this->Z * Mathvector.Y;
    double resultY = this->Z * Mathvector.X - this->X * Mathvector.Z;
    double resultZ = this->X * Mathvector.Y - this->Y * Mathvector.X;
    return Vec3D(resultX, resultY, resultZ);
}

Vec3D Vec3D::add(Vec3D Mathvector) {
    return Vec3D(this->X + Mathvector.X, this->Y + Mathvector.Y, this->Z + Mathvector.Z);
}

Vec3D Vec3D::subtract(Vec3D Mathvector) {
    return Vec3D(this->X - Mathvector.X, this->Y - Mathvector.Y, this->Z - Mathvector.Z);
}

void Vec3D::cartesianToSphere() {
    this->radius = pyth3D(this->X, this->Y, this->Z);
    this->phi = std::atan2(this->Y, this->X);
    this->theta = std::acos(this->Z / this->radius);
}

void Vec3D::cartesianToCylinder() {
    this->radius = pyth3D(this->X, this->Y, this->Z);
    this->phi = std::atan2(this->Y, this->X);
    this->height = this->Z;
}

void Vec3D::sphereToCatesian(){
    this->X = this->radius * std::sin(this->theta) * std::cos(this->phi);
    this->Y = this->radius * std::sin(this->theta) * std::sin(this->phi);
    this->Z = this->radius * std::cos(this->theta);
}

void Vec3D::sphereToCylinder() {
    this->radius = this->radius * std::sin(this->theta);
    //this->phi = this->phi;
    this->height = this->radius * std::cos(this->theta);
}

void Vec3D::cylinderToCartesian(){
    this->X = this->radius * std::cos(phi);
    this->Y = this->radius * std::sin(phi);
    this->Z = this->height;
}

void Vec3D::cylinderToSphere(){
    this->radius = pyth2D(this->radius,this->height);
    //this->phi = this->phi;
    this->theta = std::atan2(this->radius, this->height);
}

void Vec3D::setX(float X) {
    this->X = X;
    this->cartesianToCylinder();
    this->cartesianToSphere();  
}

void Vec3D::setY(float Y) {
    this->Y = Y;
    this->cartesianToCylinder();
    this->cartesianToSphere();  
}

void Vec3D::setZ(float Z){
    this->Z = Z;
    this->cartesianToCylinder();
    this->cartesianToSphere();
}

void Vec3D::setHeight(float height){
    this->height = height;
    this->cylinderToCartesian();
    this->cylinderToSphere();
}

void Vec3D::setPhi(float phi){
    this->phi = phi;
    this->cylinderToCartesian();
    this->cylinderToSphere();
    this->sphereToCatesian();
}

void Vec3D::setTheta(float theta){
    this->theta = theta;
    this->cylinderToCartesian();
    this->cylinderToSphere();
}

Vec3D Vec3D::sphereVector(float radius, float angleOne, float angleTwo){
    float Xvalue = radius * std::sin(angleTwo) * std::cos(angleOne);
    float Yvalue = radius * std::sin(angleTwo) * std::sin(angleOne);
    float Zvalue = radius * std::cos(angleTwo);
    return Vec3D(Xvalue,Yvalue,Zvalue);
}

Vec3D Vec3D::cylinderVector(float radius, float angleOne, float height){
    float Xvalue = radius * std::cos(angleOne);
    float Yvalue = radius *std::sin(angleOne);
    float Zvalue = height;
    return Vec3D(Xvalue,Yvalue,Zvalue);
}

float Vec3D::sphereSystemVolume(){
    return ((4/3)*PI*(this->radius * this->radius * this->radius));
}
float Vec3D::sphereSystemSurface(){
    return 4*PI*(this->radius * this->radius);
}

float Vec3D::cylinderSystemVolume(){
    float baseSide = PI * (this->radius * this->radius);
    return baseSide * height;
}

float Vec3D::cylinderSystemSurface(){
    float baseSide = PI  * (this->radius * this->radius);
    float mantel = TWOPI * radius * height;
    return 2 * baseSide  * mantel;
}