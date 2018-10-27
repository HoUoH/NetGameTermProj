#include "stdafx.h"

#include "Collision.h"
#include "object.h"
#include "Global.h"
#include <math.h>
#include <float.h>

float e = 1;	// Åº¼º °è¼ö

bool CollisionCheck(object * oA, object * oB)
{

	float oA_rad, oB_rad;
	float sizex, sizey;
	float x1, y1;
	float x2, y2;
	oA->GetSize(&oA_rad, &sizex);
	oB->GetSize(&oB_rad, &sizey);
	oA->GetLocation(&x1, &y1);
	oB->GetLocation(&x2, &y2);


	float colLen = oA_rad / 2 + oB_rad / 2;
	float len = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));


	if (colLen <= len)
		return false;

	return true;
}

void CollisionReaction(class object* oA, class object* oB)
{
	int oA_Kind,oB_Kind = 0; 
	oA->GetKind(&oA_Kind);
	oB->GetKind(&oB_Kind);

	float oA_X, oA_Y = 0.f;
	float oB_X, oB_Y = 0.f;
	oA->GetLocation(&oA_X, &oA_Y);
	oB->GetLocation(&oB_X, &oB_Y);

	float oA_rad, oB_rad, s1, s2 = 0.f;
	oA->GetSize(&oA_rad, &s1);
	oB->GetSize(&oB_rad, &s2);


	float oA_preVX, oA_preVY = 0.f;
	oA->GetVelocity(&oA_preVX, &oA_preVY);

	float oB_preVX, oB_preVY = 0.f;
	oB->GetVelocity(&oB_preVX, &oB_preVY);

	float oA_preVMag = sqrt(oA_preVX * oA_preVX + oA_preVY * oA_preVY);
	float oB_preVMag = sqrt(oB_preVX * oB_preVX + oB_preVY * oB_preVY);

	float oA_M, oB_M = 0.f;
	oA->GetMass(&oA_M);
	oB->GetMass(&oB_M);

	float oA_prePoten, oB_prePoten = 0.f;
	oA_prePoten = oA_M * oA_preVMag;
	oB_prePoten = oB_M * oB_preVMag;

	float prePotenSum = oA_prePoten + oB_prePoten;

	
		if (oA_Kind == oB_Kind)
		{
			float dx = oA_X - oB_X;
			float dy = oA_Y - oB_Y;
			float dab = fabsf(sqrt(dx*dx + dy * dy));

			float sinTheta = dy / fabsf(sqrt(dx*dx + dy * dy));
			float cosTheta = dx / fabsf(sqrt(dx*dx + dy * dy));

			float vxAp = (oA_M - e * oB_M) / (oA_M + oB_M)*(oA_preVX*cosTheta + oA_preVY*sinTheta) +
				(oB_M + e * oB_M) / (oA_M + oB_M)*(oB_preVX*cosTheta + oB_preVY*sinTheta);
			float vxBp = (oA_M + e * oA_M) / (oA_M + oB_M)*(oA_preVX*cosTheta + oA_preVY*sinTheta) +
				(oB_M - e * oA_M) / (oA_M + oB_M)*(oB_preVX*cosTheta + oB_preVY*sinTheta);
			float vyAp = oA_preVX*(-sinTheta) + oA_preVY*cosTheta;
			float vyBp = oB_preVX*(-sinTheta) + oB_preVY*cosTheta;

			float angleAB = atan2(dy, dx);
			float angleBA = atan2(-dy, -dx);
			float moveToDistance = fabsf(oA_rad + oB_rad) - dab;
			oA_X = oA_X + moveToDistance * cos(angleAB);
			oB_X = oB_X + moveToDistance * cos(angleBA);

			oA->SetVelocity(vxAp, vyAp);
			oB->SetVelocity(vyAp, vyBp);
	
		}
		else
		{
			if (oA_Kind == KIND_HERO)
			{
				float oB_newVMag = sqrt(oB_preVX*oB_preVX + oB_preVY * oB_preVY);
				if (oB_newVMag > FLT_EPSILON)
					oA->SetIsVisible(false);
			}
			else if (oB_Kind == KIND_HERO) {
				float oA_newVMag = sqrt(oA_preVX*oA_preVX + oA_preVY * oA_preVY);
				if (oA_newVMag > FLT_EPSILON)
					oB->SetIsVisible(false);
			}
		}
	
	
}

void WallCollision(class object* obj)
{
	float posX, posY = 0;
	float rad, height = 0;
	obj->GetLocation(&posX, &posY);
	obj->GetSize(&rad, &height);




}
