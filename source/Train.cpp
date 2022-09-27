#include "Train.h"

Train::Train(CatmullRomSpline& spline, Engine* engine, Mesh& cube_mesh, float startPointOnPath, float height, float speed, int wagonsCount)
{
	this->spline = &spline;
	this->engine = engine;
	this->cube_mesh = &cube_mesh;
	this->startPosition = startPointOnPath;
	this->speed = speed;
	this->height = height;
	for (int i = 0; i < wagonsCount; i++)
		CreateWagon();

}
float Train::GetStartPointforNextWagon()
{
	return this->startPosition + (this->wagons.size() + 1) * this->distanceBeetwenWagons;
}
void Train::CreateWagon()
{
	Wagon w = Wagon(this->spline, this->engine, this->cube_mesh, GetStartPointforNextWagon(), this->height, this->speed);
	this->wagons.push_back(w);
}
void Train::Update(float deltaTime)
{
	size_t size = this->wagons.size();
	for (size_t i=0;i< size;++i)
		this->wagons[i].Update(deltaTime);
}
