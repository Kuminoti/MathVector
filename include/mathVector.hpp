#pragma once

#ifndef VECTORMATH
#define VECTORMATH

#include<cmath>

#define TWOPI 2*PI
#define PI 3.14159265358979323846    
#define NAMESPACESTART namespace Dvec {
#define NAMESPACEEND }


//uncomment to choose your standard koordinate system
#define CARTESIAN_IS_3D_STANDARD 
#define CARTESIAN_IS_2D_STANDARD
//#define POLAR_IS_STANDARD
//#define SPHERE_IS_STANDARD 
//#define CYLINDER_IS_STANDARD 

#if (defined(SPHERE_IS_STANDARD) || defined(CYLINDER_IS_STANDARD)) && defined(CARTESIAN_IS_3D_STANDARD)
    #warning "Warning: More than one system is defined!"
    #undef CARTESIAN_IS_STANDARD
    #ifdef SPHERE_IS_STANDARD
        #undef CYLINDER_IS_STANDARD
        #warning "Sphere system will be standart!"
    #endif
    #warning "Cylinder system will be standart!"
#endif

#ifdef POLAR_IS_STANDARD 
    #ifdef CARTESIAN_IS_2D_STANDARD
        #undef CARTESIAN_IS_2D_STANDARD
        #warning "Warning: You defined polar coordinates as standard and cartesian as 2D standard. Polar will be standard."
    #endif
#endif




NAMESPACESTART
class Vec2D {
   protected: //Protected data
    float phi;
    float radius; 
    float abs;
    float X;
    float Y;

  protected: //Protected methods
    virtual float calcAbs();
    
    void polarToCartesian();
    void cartesianToPolar();

   public:
    /* 
     * When you call the constructor the class will automaticly calculate the values
     * for the polar coordinates  
     */

#ifdef CARTESIAN_IS_2D_STANDARD
    Vec2D(float X, float Y);
#endif

#ifdef POLAR_IS_STANDARD
    Vec2D(float radius float angle);
#endif
    //Math with scalar results
    float lenght(); // Calculates the length of a vector
    float dotProduct(Vec2D Mathvector); //Scalar or dot product
    float calcAngle(Vec2D Mathvector); //Calculates the angle between 2 vectors

    //Getters
    float getX() { return this->X; } 
    float getY() { return this->Y; }
    float getAbs(){ return this->abs; }
    float getPhi() { return this->phi; }
    float getRadius() { return this->radius; }
    float polarSystemArea();          //calculates the circle of a polar system
    float polarSystemCircumfrance(); //calculates the circumfrance of a polar system

    //Setters
    /* 
     * If data is set/changed it will automaticly change the values for other
     * koordinate types as well.
     * for example when you call .setX() the cartesian to polar method is called
     * as well and the polar values are updated.
     */
    virtual void setX(float value);
    virtual void setY(float value);
    virtual void setPhi(float value);
    virtual void setRadius(float radius);
   
    Vec2D add(Vec2D Mathvector); //Adding 2 vectors
    Vec2D subtract(Vec2D Mathvector); //Subtract 2 vectors


    static Vec2D polarVector(float radius, float angle);
    
};



class Vec3D : public Vec2D {
   private: //Private data
    float Z;
    float height;
    float theta;
    float phi;
    

  private: //Private methods
    
    //Calculating the Values for different systems
    void cartesianToSphere();
    void cartesianToCylinder();

    void sphereToCatesian();
    void sphereToCylinder();

    void cylinderToCartesian();
    void cylinderToSphere();

    float calcAbs() final;

   public:
  
#ifdef CARTESIAN_IS_3D_STANDARD
    Vec3D(float X, float Y, float Z) : Vec2D(X, Y), Z(Z) {this->abs = this->calcAbs();}   
#endif

#ifdef SPHERE_IS_STANDARD
    Vec3D(float radius, float phi, float theta) : Vec2D(radius, phi), theta(theta){this->abs = this->calcAbs();}
#endif

#ifdef CYLINDER_IS_STANDARD
    Vec3D(float radius, float phi, float height) : Vec2D(radius, phi), height(height){this->abs = this->calcAbs();}
#endif

    //Setters
    void setX(float X) override;
    void setY(float Y) override;
    void setPhi(float value) override;      // For spheresystems (radius, angle Phi, angle Theta)
    void setZ(float value) ;               //
    void setHeight(float value);          // For cylinder systems (radius, angle, height);
    void setTheta(float value);          // For spheresystems (radius, angle Phi, angle Theta);

    //Getters
    float getZ() {return this->Z;}
    float getHeight() {return this->height;}
    float getTheta() {return this->theta;}
    float getPhi() {return this->phi;}

    //Calculations that return a scalar value
    float dotProduct(Vec3D Mathvector);
    float calcAngle(Vec3D Mathvector);

    //Calculations that return a vector
    Vec3D vecProduct(Vec3D Mathvector);
    Vec3D add(Vec3D Mathvector);
    Vec3D subtract(Vec3D Mathvector);
    Vec3D sphereVector(float radius, float angleOne, float angleTwo);
    Vec3D cylinderVector(float radius, float angle, float height);

    // Volumes and surfaces of sphere and cylinder systems
    float cylinderSystemVolume();
    float cylinderSystemSurface();
    float sphereSystemVolume();
    float sphereSystemSurface();
};
NAMESPACEEND 

#endif