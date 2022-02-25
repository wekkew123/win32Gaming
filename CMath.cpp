#include "CMath.h"

float CMath::GetDistance(const POSITION& tPos1, const POSITION& tPos2)
{
	float x, y;

	x = tPos1.x - tPos2.x;
	y = tPos1.y - tPos2.y;

	return sqrtf(x*x+y*y);
}
