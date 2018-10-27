#include "stdafx.h"
#include "object.h"
#include <math.h>
#include <float.h>

float maxVelocity = 300.f;
float minVelocity = -300.f;

object::object()
{
	posX = 0;	posY = 0;
	sizeX = 0;	sizeY = 0;
	accX = 0;	accY = 0;

}


object::~object()
{
	delete this;
}

void object::Update(float elapsed_time_in_sec)
{

	float gz = mass * 9.8;
	float friction = coefFriction * gz;
	float velmag = sqrtf(velX*velX + velY * velY);

	if (velmag < FLT_EPSILON) {
		velX = 0.f;
		velY = 0.f;
	}
	else {
		//방향 구하기 정규화
		frictionX = -friction * velX / velmag;
		frictionY = -friction * velY / velmag;

		float accX = frictionX / mass;
		float accY = frictionY / mass;
		float newVelX = velX + accX * elapsed_time_in_sec;
		float newVelY = velY + accY * elapsed_time_in_sec;
		if (newVelX*velX < 0.f)
			velX = 0.f;
		else
			velX = newVelX;
		if (newVelY*velY < 0.f)
			velY = 0.f;
		else
			velY = newVelY;
	}
	//속도 계산
	velX = velX + accX * elapsed_time_in_sec;
	velY = velY + accY * elapsed_time_in_sec;

	//갱신될 위치 = 이전 위치 + 속도 * 시간 
	posX = posX + velX * elapsed_time_in_sec;
	posY = posY + velY * elapsed_time_in_sec;



}
void object::SetLocation(float x, float y)
{
	posX = x;
	posY = y;

}

void object::GetLocation(float *x, float *y)
{
	*x = posX;
	*y = posY;

}

void object::SetSize(float sizeX, float sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

}

void object::GetSize(float *sizeX, float *sizeY)
{
	*sizeX = this->sizeX;
	*sizeY = this->sizeY;

}

void object::SetVelocity(float velX, float velY)
{
	this->velX = velX;
	this->velY = velY;
}

void object::GetVelocity(float * velX, float * velY)
{
	*velX = this->velX;
	*velY = this->velY;
}

void object::SetAcc(float accX, float accY)
{
	this->accX = accX;
	this->accY = accY;
}

void object::GetAcc(float * accX, float * accY)
{
	*accX = this->accX;
	*accY = this->accY;
}

void object::SetForce(float ForceX, float ForceY)
{
	this->ForceX = ForceX;
	this->ForceY = ForceY;
}

void object::GetForce(float * ForceX, float * ForceY)
{
	*ForceX = this->ForceX;
	*ForceY = this->ForceY;
}

void object::SetMass(float mass)
{
	this->mass = mass;
}

void object::GetMass(float * mass)
{
	*mass = this->mass;
}

void object::SetCoefFriction(float coefFriction)
{
	this->coefFriction = coefFriction;

}

void object::GetCoefFriction(float * coefFriction)
{

	*coefFriction = this->coefFriction;

}

void object::SetKind(int kind)
{
	this->kind = kind;
}

void object::GetKind(int * kind)
{
	*kind = this->kind;

}

void object::SetIsVisible(bool view)
{
	this->isVisible = isVisible;
}

bool object::GetIsVisible()
{
	return isVisible;
}

void object::ApplyForce(float ForceX, float ForceY, float elapsed_time_in_sec)
{
	//가속도 계산 힘/질량
	accX = ForceX / mass;
	accY = ForceY / mass;

	//속도 계산
	velX = velX + accX * elapsed_time_in_sec;
	velY = velY + accY * elapsed_time_in_sec;

	accX = 0;
	accY = 0;

	if (velX > maxVelocity)
		velX = maxVelocity;

	if (velX < minVelocity)
		velX = minVelocity;

	if (velY > maxVelocity)
		velY = maxVelocity;

	if (velY < minVelocity)
		velY = minVelocity;
}

void object::BreakMovement(bool W_KeyIsDown, bool S_KeyIsDown, bool D_KeyIsDown, bool A_KeyIsDown, float elapsed_time_in_sec)
{
	if (!W_KeyIsDown)
	{
		if (velY > 0)
		{
			velY = velY + (frictionY * elapsed_time_in_sec / (mass *0.01f));
		}

	}
	if (!S_KeyIsDown)
	{
		if (velY < 0)
		{
			velY = velY + (frictionY * elapsed_time_in_sec / (mass *0.01f));
		}
	}
	if (!D_KeyIsDown)
	{
		if (velX > 0)
		{
			velX = velX + (frictionX * elapsed_time_in_sec / (mass *0.01f));

		}
	}
	if (!A_KeyIsDown)
	{
		if (velX < 0)
		{
			velX = velX + (frictionX * elapsed_time_in_sec / (mass *0.01f));
		}
	}

}


