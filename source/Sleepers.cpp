#include "Sleepers.h"

Sleepers::Sleepers(CatmullRomSpline& spline, Engine* engine, Mesh& cube_mesh, float height)
{
	this->spline = &spline;
	this->engine = engine;
	this->cube_mesh = &cube_mesh;
	this->height = height;
	CreateSleepers();
}

void Sleepers::CreateSleepers()
{
	float pathLength = this->spline->GetLengthSpline();
	//Т.к. количество шпал не может быть дробным числом, то надо округлить
	const int countSleepers = (int)(pathLength / minDistanceBettwenSleepres) + 1;
	//Высчитать шаг между шпалами.
	float step = pathLength / countSleepers;

	float distance = 0;
	int sleeperNumber = 0;
	while(sleeperNumber < countSleepers)
	{
		this->sleepers.push_back(Sleeper(this->spline, this->engine, this->cube_mesh, distance, this->height));

		float len = 0;
		if (sleeperNumber > 1)
			len = Vec2Length(sleepers[sleeperNumber].GetVec2Position() - sleepers[sleeperNumber - 1].GetVec2Position());

		++sleeperNumber;
		distance += step;
	}
}
