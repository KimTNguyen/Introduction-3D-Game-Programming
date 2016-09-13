// Excavator.h
// Aim: To encapsulates attributes and methods of the excavator
//
// Created: 30 Feb 2010
// Modified: 7 Mar 2010
// Author: Kim Nguyen - SCIS, Edith Cowan University.

#pragma once
#ifndef EXCAVATOR
#define EXCAVATOR

#include "Geometry.h"
#include "Entity.h"
#include "Vector3.h"
#include <vector>

using namespace std;

const double pi=3.1415927;

class Excavator: public Entity
{
public:
	// construction and destruction
	Excavator();
	Excavator(float locationX,float locationZ, float movementSpeed = 0.1, 
		float altitudeY = 0,float angleToZAxis=0, float turrentAngle=180,
		float upperArmAngle=315, float lowerArmAngle=90);
	~Excavator();

	// getter methods:
	const float getTurretAngle();
	const float getUpperArmAngle();
	const float getLowerArmAngle();

	// check what camera is using. Return true if the first person camera is in use, 
	// false if the third person camera is using.
	bool getFirstCamera();

	// control the movement and rotation of the excavator
	void processKeyboardInput();

private:
	float movementSpeed; // acceleration of the the excavator
	float currentSpeedX; // velocity of the excavator along X-axis
	float currentSpeedZ; // velocity of the excavator along Z-axis
	float turningSpeed; // turning acceleration of the the excavator
	float currentTurningSpeed; // turning velocity
	float friction; // the force that holds back the excavator's movement
	float turretAngle; // holds the current angle rotation of the turret
	float upperArmAngle; // pivot angle of the upper arm
	float lowerArmAngle; // pivot angle of the lower arm

	bool isFirstCamera; // a flag indicated a first person camera is used
};



#endif
