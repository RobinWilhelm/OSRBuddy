#include "MathHelper.h"

enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

void MathHelper::SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void MathHelper::AngleVectors(const QAngle& angles, D3DXVECTOR3* forward, D3DXVECTOR3* right, D3DXVECTOR3* up)
{
	float sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
	SinCos(DEG2RAD(angles[ROLL]), &sr, &cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

bool MathHelper::VectorToAngles(const D3DXVECTOR3& forward, QAngle& angles)
{
	//angles.pitch = RAD2DEG(atan2(sqrt(forward.x * forward.x + forward.y * forward.y), forward.z));
	angles.pitch = RAD2DEG(atan2(-forward.z, sqrt(forward.x * forward.x + forward.y * forward.y)));
	angles.yaw = RAD2DEG(atan2(forward.y, forward.x));
	angles.roll = 0.0f;

	if (!std::isnan(angles.yaw) && !std::isnan(angles.pitch))
		return true;
	return false;
}
