#include "Wagon.h"

Wagon::Wagon(CatmullRomSpline* spline, Engine* engine, Mesh* cube_mesh, float startPointOnPath, float height, float speed)
{
	this->engine = engine;
	this->spline = spline;
	this->maxCurvePoints = (*spline).GetCountCurvePoints();
	this->distanceTraveled = startPointOnPath;
	this->height = height;
	this->speed = speed;

	Object* cube = engine->createObject(cube_mesh);
	cube->setColor(113.0f/255, 23.0f/255, 0);
	cube->setScale(1);
	cube->setRotation(-90.0f, 0.0f, 0.0f);
	this->cubeView = cube;
	CalculateTransform();
}

inline void Wagon::CalculateTransform()
{
	this->position = this->spline->GetPointOnPath(this->distanceTraveled);
	this->curvePointNumber = this->spline->GetPointCurveNumber(this->distanceTraveled);
	this->direction = (this->spline->GetPointCurveInfo(this->curvePointNumber))->direction;
	this->distanceForNextCurvePoint= (this->spline->GetPointCurveInfo(this->curvePointNumber+1))->pathLength;
	UpdateViewData();
}

void Wagon::UpdateViewData()
{
	this->cubeView->setPosition(Vec2ToVec3(this->position, this->height));

	vec3 modelDirection = vec3(0, 0, 1);
	vec3 dir = vec3( this->direction.x, 0, direction.y);
	float d = dot(modelDirection, dir);
	float s = sqrt((1 + d) * 2);
	float inverseS = 1 / s;
	vec3 c = cross(modelDirection, dir);

	quat q = this->cubeView->getRotation();
	q.x = c.x * inverseS;
	q.y = c.y * inverseS;
	q.z = c.z * inverseS;
	q.w = s * 0.5f;
	normalize(q);
	this->cubeView->setRotation(q);
}

void Wagon::Update(float deltaTime)
{
	float deltaDistanceTravelled = deltaTime * this->speed;
	float oldDistance = this->distanceTraveled;
	float prevDistanceForNextCurvePoint;
	CatmullRomSpline::PointLength* passedPoint;
	this->distanceTraveled += deltaDistanceTravelled;
	if (this->distanceTraveled > this->distanceForNextCurvePoint)
	{
		int curvePointNumber = this->curvePointNumber;
		int maxPoints = this->maxCurvePoints;

		++curvePointNumber;
		if (curvePointNumber > maxPoints)
		{
			this->distanceTraveled = 0;
			curvePointNumber = 0;
		}
		passedPoint = this->spline->GetPointCurveInfo(curvePointNumber);
		this->direction = passedPoint->direction;
		prevDistanceForNextCurvePoint = this->distanceForNextCurvePoint;
		this->distanceForNextCurvePoint = (this->spline->GetPointCurveInfo(curvePointNumber + 1))->pathLength;

		while (this->distanceTraveled > this->distanceForNextCurvePoint)
		{
			++curvePointNumber;
			if (curvePointNumber > maxPoints)
			{
				this->distanceTraveled = 0;
				curvePointNumber = 0;
			}

			prevDistanceForNextCurvePoint = this->distanceForNextCurvePoint;
			this->distanceForNextCurvePoint = (this->spline->GetPointCurveInfo(curvePointNumber + 1))->pathLength;
		}

		passedPoint = this->spline->GetPointCurveInfo(curvePointNumber);
		this->direction = passedPoint->direction;
		this->position = (*passedPoint->point) + this->direction * (deltaDistanceTravelled - (prevDistanceForNextCurvePoint - oldDistance));

		this->curvePointNumber = curvePointNumber;
	}
	else
	{
		this->position += this->direction * deltaDistanceTravelled;
	}
	UpdateViewData();
}
