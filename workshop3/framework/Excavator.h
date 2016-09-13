// Excavator.h
// Aim: To encapsulates attributes and methods of the excavator
//
// Created: 30 Feb 2010
// Author: Kim Nguyen - SCIS, Edith Cowan University.

#include "Entity.h"

#ifndef EXCAVATOR

#define EXCAVATOR


const double pi=3.1415927;

class Excavator: public Entity
{
public:
	// construction and destruction
	Excavator();
	Excavator(float locationX,float locationZ, float movementSpeed = 0.1, 
		float altitudeY = 0,float angleToZAxis=0, float turrentAngle=180,
		float upperArmAngle=315, float lowerArmAngle=90, float scoopAngle=70);
	~Excavator();

	// getter methods:
	const float getTurretAngle();
	const float getUpperArmAngle();
	const float getLowerArmAngle();
	const float getScoopAngle();

	// control the movement and rotation of the excavator
	void processKeyboardInput();
private:
	float movementSpeed; // how fast the excavator can run
	float turretAngle; // holds the current angle rotation of the turret
	float upperArmAngle; // pivot angle of the upper arm
	float lowerArmAngle; // pivot angle of the lower arm
	float scoopAngle; // holds the current angle of the the scoop
};



#endif
