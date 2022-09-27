#include "Sleeper.h"


Sleeper::Sleeper(CatmullRomSpline* spline, Engine* engine, Mesh* cube_mesh, float position, float height)
{
	this->engine = engine;
	this->spline = spline;
	this->height = height;
	this->position = position;

	Object* cube = engine->createObject(cube_mesh);
	cube->setColor(113.0f / 180, 23.0f / 180, 0);
	cube->setScale(1.2f, 0.1f, 0.2f);
	cube->setRotation(-90, 0, 0.0f);
	this->view = cube;
	CalculateTransform();
}

inline void Sleeper::CalculateTransform()
{
	this->vec2Position = this->spline->GetPointOnPath(this->position);
	int curvePointNumber = this->spline->GetPointCurveNumber(this->position);
	this->direction = (this->spline->GetPointCurveInfo(curvePointNumber))->direction;
	UpdateViewData();
}

void Sleeper::UpdateViewData()
{
	float len = Vec2Length(this->vec2Position);
	vec3 newPos = Vec2ToVec3(this->vec2Position, this->height);
	this->view->setPosition(newPos);

	vec3 modelDirection = vec3(0, 0, 1);
	vec3 dir = vec3(this->direction.x, 0, direction.y);
	float d = dot(modelDirection, dir);
	float s = sqrt((1 + d) * 2);
	float inverseS = 1 / s;
	vec3 c = cross(modelDirection, dir);

	quat q = this->view->getRotation();
	q.x = c.x * inverseS;
	q.y = c.y * inverseS;
	q.z = c.z * inverseS;
	q.w = s * 0.5f;
	normalize(q);
	this->view->setRotation(q);
}
