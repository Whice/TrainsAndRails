#pragma once
#include "CatmullRomSpline.h"
#include "CatmullRomSpline.h"
#include "Wagon.h"

/// <summary>
/// Поезд.
/// </summary>
class Train
{
private:Mesh* cube_mesh;
private: Engine* engine;
	   /// <summary>
	   /// Данные о кривой для передвижения вагона.
	   /// </summary>
private: CatmullRomSpline* spline;
	   /// <summary>
	   /// Нынешнее положение поезда.
	   /// </summary>
private: vec2 startPosition;
	   /// <summary>
	   /// Высота, на которой должнен находиться поезд.
	   /// </summary>
private: float height;
	   /// <summary>
	   /// Скорость передвижения вагона.
	   /// </summary>
private: float speed;
/// <summary>
/// Расстояние между вагонами.
/// </summary>
private: const float distanceBeetwenWagons = 1.2f;
/// <summary>
/// Вагоны поезда.
/// </summary>
private: vector<Wagon> wagons;

public: Train(CatmullRomSpline& spline, Engine* engine, Mesh& cube_mesh, float startPointOnPath, float height, float speed, int wagonsCount);

/// <summary>
/// Получить стартовую точку для следующего вагона.
/// </summary>
private: float GetStartPointforNextWagon();
/// <summary>
/// Создать один вагон для поезда.
/// </summary>
private: void CreateWagon();

private:
	   
/// <summary>
/// Обновить внутренние данные поезда.
/// </summary>
public: void Update(float deltaTime);
};

