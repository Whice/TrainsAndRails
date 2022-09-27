#include "Rails.h"

vector<vec2> Rails::GetRailsOuterCountour1()
{
	return this->railsOuterCountour1;
}

vector<vec2> Rails::GetRailsOuterCountour2()
{
	return this->railsOuterCountour2;
}

vector<vec2> Rails::GetRailsInnerCountour1()
{
	return this->railsInnerCountour1;
}

vector<vec2> Rails::GetRailsInnerCountour2()
{
	return this->railsInnerCountour2;
}

Rails::Rails(CatmullRomSpline& spline, float distanceToPath, float railsWidth)
{
	this->distanceToPath = distanceToPath;
	this->railsWidth = railsWidth;
	this->spline = &spline;
	CreateRails();
}

void Rails::CreateRails()
{
	size_t size = this->spline->GetCountCurvePoints() - 1;
	const float distanceToPath = this->distanceToPath;
	const float distanceToPathWithWidth = this->distanceToPath + this->railsWidth;

	CatmullRomSpline::PointLength* pointInfo;
	vec2 direction;
	vec2 newRailsPoint;
	vec2 splinePoint;
	for (size_t i = 0; i < size; ++i)
	{
		pointInfo = this->spline->GetPointCurveInfo(i);
		splinePoint = (*pointInfo->point);
		direction = pointInfo->direction;
		Rotate90Degree(direction);
		newRailsPoint = splinePoint - direction * distanceToPath;
		this->railsOuterCountour1.push_back(newRailsPoint);
		newRailsPoint = splinePoint - direction * (distanceToPathWithWidth);
		this->railsOuterCountour2.push_back(newRailsPoint);
		newRailsPoint = splinePoint + direction * distanceToPath;
		this->railsInnerCountour1.push_back(newRailsPoint);
		newRailsPoint = splinePoint + direction * (distanceToPathWithWidth);
		this->railsInnerCountour2.push_back(newRailsPoint);
	}
	this->railsOuterCountour1.push_back(this->railsOuterCountour1[0]);
	this->railsOuterCountour2.push_back(this->railsOuterCountour2[0]);
	this->railsInnerCountour1.push_back(this->railsInnerCountour1[0]);
	this->railsInnerCountour2.push_back(this->railsInnerCountour2[0]);
}
