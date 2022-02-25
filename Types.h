#pragma once
#include "Flag.h"

typedef struct _tagResolution
{
	unsigned int iW;
	unsigned int iH;

	_tagResolution() :
		iW(0),
		iH(0)
	{
	}
	_tagResolution(int _x,int _y) :
		iW(_x),
		iH(_y)
	{
	}


}RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition
{
	float x, y;

	_tagPosition()	:
		x(0),
		y(0) 
	{
	}
	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}
	_tagPosition(const _tagPosition& ps)
	{
		x = ps.x;
		y = ps.y;
	}
	_tagPosition operator +(const _tagPosition& ps)	const
	{
		_tagPosition t;
		t.x = x + ps.x;
		t.y = y + ps.y;
		return t;
	}
	void operator =(const _tagPosition& ps) 
	{
		x = ps.x;
		y = ps.y;
	}
	_tagPosition operator +(float f)	const
	{
		_tagPosition t;
		t.x = x + f;
		t.y = y + f;
		return t;
	}
	void operator +=(const _tagPosition& ps)
	{
		x += ps.x;
		y += ps.y;
	}
	_tagPosition operator -(const _tagPosition& ps)	const
	{
		_tagPosition t;
		t.x = x - ps.x;
		t.y = y - ps.y;
		return t;
	}
	_tagPosition operator -(float f)	const
	{
		_tagPosition t;
		t.x = x - f;
		t.y = y - f;
		return t;
	}
	void operator -=(const _tagPosition& ps)
	{
		x -= ps.x;
		y -= ps.y;
	}
	_tagPosition operator *(const _tagPosition& ps)	const
	{
		_tagPosition t;
		t.x = x * ps.x;
		t.y = y * ps.y;
		return t;
	}
	_tagPosition operator *( float f)	const 
	{
		_tagPosition t;
		t.x = x * f;
		t.y = y * f;
		return t;
	}
	void operator *=(const _tagPosition& ps)
	{
		x *= ps.x;
		y *= ps.y;
	}
	_tagPosition operator /(const _tagPosition& ps)	const
	{
		_tagPosition t;
		t.x = x / ps.x;
		t.y = y / ps.y;
		return t;
	}
	_tagPosition operator /(const float f)	const
	{
		_tagPosition t;
		t.x = x / f;
		t.y = y / f;
		return t;
	}
	void operator /=(const _tagPosition& ps)
	{
		x /= ps.x;
		y /= ps.y;
	}
}POSITION, *PPOSITION, _SIZE, *_PSIZE;

typedef struct _tagRectangle
{
	float l;
	float t;
	float r;
	float b;

	_tagRectangle()	:
		l(0.f),
		t(0.f),
		r(0.f),
		b(0.f)
	{
	}

}RECTANGLE, *PRECTANGLE;

typedef struct _tagSphere
{
	POSITION	tCenter;
	float		fRadius;

	_tagSphere() :
		tCenter(0.f,0.f),
		fRadius(0.f)
	{
	}
}SPHERE,* PSPHERE;

typedef struct _tagAnimationClip
{
	ANIMATION_TYPE	eType;
	ANIMATION_OPTION eOption;
	vector<class CTexture*>	vecTexture;
	float	fAnimationTime;
	float	fAnimationLimitTime;
	float	fAnimationFramTime;
	int		iFramX;
	int		iFramY;
	int		iFramMaxX;
	int		iFramMaxY;
	int		iStarX;
	int		iStarY;
	int		iLengthX;
	int		iLengthY;
	float	fOptionTIme;
	float	fOptionLimitTIme;
}ANIMATIONCLIP, *PANIMATIONCLIP;