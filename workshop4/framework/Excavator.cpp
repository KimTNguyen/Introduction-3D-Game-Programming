// inplementation of Entity class
//
// Created: 30 Feb 2010
// Modified: 7 Mar 2010
// Author: Kim Nguyen - SCIS, Edith Cowan University.

#include "Excavator.h"
#include <windows.h>
#include <math.h>					

Excavator::Excavator() : Entity()
{
}

// Constructor: takes the excavator's position, its acceleration and angles, as arguments
// and set to the class variables. This constructor also sets default values 
// to some other variables, such as velocity, friction and the camera to be used.
Excavator::Excavator(float locationX,float locationZ, float movementSpeed, 
		float altitudeY,float angleToZAxis, float turretAngle,
		float upperArmAngle, float lowerArmAngle) 
               : Entity(locationX,locationZ,altitudeY,angleToZAxis)
{
	this->movementSpeed = movementSpeed;
	this->turretAngle = turretAngle;
	this->upperArmAngle = upperArmAngle;
	this->lowerArmAngle = lowerArmAngle;

	friction = 0.95f;
	turningSpeed = movementSpeed;
	currentTurningSpeed = 0;
	currentSpeedX = 0;
	currentSpeedZ = 0;
	isFirstCamera = false;
}

Excavator::~Excavator()
{
}

// get the angle of rotation around Y-axis of the turret
const float Excavator::getTurretAngle()
{
	return turretAngle;
}

// get the pivot angle of the excavator's upper arm
const float Excavator::getUpperArmAngle()
{
	return upperArmAngle;
}

// get the pivot angle of the excavator's lower arm
const float Excavator::getLowerArmAngle()
{
	return lowerArmAngle;
}

// check what camera is using. Return true if the first person camera is in use, 
// false if the third person camera is using.
bool Excavator::getFirstCamera()
{
	return isFirstCamera;
}

// control the movement and rotation of the excavator. 
void Excavator::processKeyboardInput()
{	
	// left and right turn the Excavator
	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		currentTurningSpeed += 2*turningSpeed;
	}
	else 
	{
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			currentTurningSpeed -= 2*turningSpeed;			
		}
	}
	angleToZAxisInDegrees += currentTurningSpeed;
	currentTurningSpeed *= friction;
	if (angleToZAxisInDegrees>=360)
	{
		angleToZAxisInDegrees -=360;
	}
	if (angleToZAxisInDegrees<=0)
	{
		angleToZAxisInDegrees += 360;
	}

	// up and down are for moving backwards/forwards
	bool moved = FALSE;
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		currentSpeedX -= movementSpeed*(float)sin(pi*(angleToZAxisInDegrees/180.0));
		currentSpeedZ -= movementSpeed*(float)cos(pi*(angleToZAxisInDegrees/180.0));

		moved = TRUE;
	}
	else 
	{
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{

			currentSpeedX += movementSpeed*(float)sin(pi*(float(angleToZAxisInDegrees)/180.0));
			currentSpeedZ += movementSpeed*(float)cos(pi*(float(angleToZAxisInDegrees)/180.0));

			moved = TRUE;
		}
	}

	locationX += currentSpeedX;
	locationZ += currentSpeedZ;
	
	currentSpeedX *= friction;
	currentSpeedZ *= friction;
	
	if (moved)
	{
		return;
	}


	// rotate the Excavator turret arround the base
	if (GetAsyncKeyState('Q') < 0)
	{
		--turretAngle;
		if (turretAngle<=0)
		{
			turretAngle = 360;
		}
	}
	else 
	{
		if (GetAsyncKeyState('A') < 0)
		{
			++turretAngle;
			if (turretAngle>=360)
			{
				turretAngle = 0;
			}
		}
	}

	// move upper arm, limit movement between 
	if (GetAsyncKeyState('W') < 0)
	{
		--upperArmAngle;
		if (upperArmAngle<0)
		{
			upperArmAngle = 360;
		}
	}
	else 
	{
		if (GetAsyncKeyState('S') < 0)
		{
			++upperArmAngle;
			if (upperArmAngle>360)
			{
				upperArmAngle = 0;
			}
		}
	}

	// move lower arm
	if (GetAsyncKeyState('E') < 0)
	{
		--lowerArmAngle;
		if (lowerArmAngle<0)
		{
			lowerArmAngle = 0;
		}
	}
	else 
	{
		if (GetAsyncKeyState('D') < 0)
		{
			++lowerArmAngle;
			if (lowerArmAngle>360)
			{
				lowerArmAngle = 360;
			}
		}
	}

	// TAB is pressed
	if (GetAsyncKeyState(VK_TAB) < 0)
	{
		isFirstCamera = !isFirstCamera;
	}

	return;

}