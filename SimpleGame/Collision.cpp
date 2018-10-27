#include "stdafx.h"

#include "Collision.h"
#include "object.h"
#include <math.h>

bool CollisionCheck(object * o1, object * o2)
{

	float size1, size2;
	float sizex, sizey;
	float x1, y1;
	float x2, y2;
	o1->GetSize(&size1, &sizex);
	o2->GetSize(&size2, &sizey);
	o1->GetLocation(&x1, &y1);
	o2->GetLocation(&x2, &y2);


	float colLen = size1 / 2 + size2 / 2;
	float len = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));


	if (colLen <= len)
		return false;

	return true;
}
