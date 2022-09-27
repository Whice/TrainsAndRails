#pragma once
#include "CatmullRomSpline.h"
#include "framework/engine.h"
#include "Sleeper.h"

class Sleepers
{

private:Mesh* cube_mesh;
private: Engine* engine;
	   /// <summary>
	   /// Данные о кривой для передвижения вагона.
	   /// </summary>
private: CatmullRomSpline* spline;
	   /// <summary>
	   /// Высота, на которой должнен находиться поезд.
	   /// </summary>
private: float height;
/// <summary>
/// Минимальное расстояние между шапалами.
/// </summary>
private: const float minDistanceBettwenSleepres = 1.3f;
/// <summary>
/// Набор шпал.
/// </summary>
private: vector<Sleeper> sleepers;

public:
	Sleepers(CatmullRomSpline& spline, Engine* engine, Mesh& cube_mesh, float height);

/// <summary>
/// Создать набор шпал.
/// </summary>
private: void CreateSleepers();

};