#pragma once
#include "framework/engine.h"
#include "framework/utils.h"

using namespace std;
using namespace glm;


inline vec2 Vec3ToVec2(const vec3& v)
{
	return vec2(v.x, v.z);
}
inline vector<vec2> VectorVec3ToVec2(const vector<vec3>& v3)
{
	vector<vec2> v2;
	for (vec3 v : v3)
	{
		v2.push_back(Vec3ToVec2(v));
	}
	return v2;
}

inline vec3 Vec2ToVec3(const vec2& v, float y = -0.375f)
{
	return vec3(v.x, y, v.y);
}
inline vector<vec3> VectorVec2ToVec3(const vector<vec2>& v2, float y = -0.375f)
{
	vector<vec3> v3;
	for (vec2 v : v2)
	{
		v3.push_back(Vec2ToVec3(v, y));
	}
	return v3;
}
/// <summary>
/// Получить длину вектора.
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
inline float Vec2Length(vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

