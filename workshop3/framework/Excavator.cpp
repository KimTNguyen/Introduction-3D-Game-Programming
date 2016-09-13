// inplementation of Entity class
//
// Created: 30 Feb 2010
// Author: Kim Nguyen - SCIS, Edith Cowan University.

#include "Excavator.h"
#include <windows.h>
#include <math.h>

Excavator::Excavator() : Entity()
{
}

// Constructor: takes the excavator's position, its speed and angles, as arguments
// and set to the class variables.
Excavator::Excavator(float locationX,float locationZ, float movementSpeed, 
		float altitudeY,float angleToZAxis, float turretAngle,
		float upperArmAngle, float lowerArmAngle, float scoopAngle) 
               : Entity(locationX,locationZ,altitudeY,angleToZAxis)
{
	this->movementSpeed = movementSpeed;
	this->turretAngle = turretAngle;
	this->upperArmAngle = upperArmAngle;
	this->lowerArmAngle = lowerArmAngle;
	this->scoopAngle = scoopAngle;
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

// get the current angle of the excavator's scoop
const float Excavator::getScoopAngle()
{
	return scoopAngle;
}

// control the movement and rotation of the excavator
void Excavator::processKeyboardInput()
{
	// left and right turn the Excavator
	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		++angleToZAxisInDegrees;
		if (angleToZAxisInDegrees>=360)
			{
				angleToZAxisInDegrees = 0;
			}
	}
	else 
	{
		if (GetAsyncKeyState(VK_RIGHT) < 0)
		{
			--angleToZAxisInDegrees;
			if (angleToZAxisInDegrees<=0)
			{
				angleToZAxisInDegrees = 360;
			}
			
		}
	}


	// up and down are for moving backwards/forwards
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		locationX -= movementSpeed*sin(pi*(angleToZAxisInDegrees/180.0));
		locationZ -= movementSpeed*cos(pi*(angleToZAxisInDegrees/180.0));
	}
	else 
	{
		if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			locationX += movementSpeed*sin(pi*(float(angleToZAxisInDegrees)/180.0));
			locationZ += movementSpeed*cos(pi*(float(angleToZAxisInDegrees)/180.0));
		}
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
		if (upperArmAngle<270)
		{
			upperArmAngle = 270;
		}
	}
	else 
	{
		if (GetAsyncKeyState('S') < 0)
		{
			++upperArmAngle;
			if (upperArmAngle>405)
			{
				upperArmAngle = 405;
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
			if (lowerArmAngle>140)
			{
				lowerArmAngle = 140;
			}
		}
	}

	// move scoop
	if (GetAsyncKeyState('R') < 0)
	{
		--scoopAngle;
		if (scoopAngle<-135)
		{
			scoopAngle = -135;
		}
	}
	else 
	{
		if (GetAsyncKeyState('F') < 0)
		{
			++scoopAngle;
			if (scoopAngle>70)
			{
				scoopAngle = 70;
			}
		}
	}

}