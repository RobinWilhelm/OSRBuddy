#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "QAngle.h"
#include <d3dx9math.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif


namespace MathHelper
{
	inline void SinCos(float radians, float* sine, float* cosine);
	void AngleVectors(const QAngle& angles, D3DXVECTOR3* forward, D3DXVECTOR3* right, D3DXVECTOR3* up);
	bool VectorToAngles(const D3DXVECTOR3& forward, QAngle& angles);
}