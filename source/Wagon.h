#pragma once
#include "framework/engine.h"
#include "framework/utils.h"
#include "CatmullRomSpline.h"
#include "AdditionalFunctions.h"

using namespace std;
using namespace glm;

/// <summary>
/// Вагон поезда.
/// </summary>
class Wagon
{
private:Mesh* cube_mesh;
private: Engine* engine;
	   /// <summary>
	   /// Представление объекта в мире.
	   /// </summary>
private: Object* cubeView;
/// <summary>
/// Данные о кривой для передвижения вагона.
/// </summary>
private: CatmullRomSpline* spline;
/// <summary>
/// Количество узлов в кривой.
/// </summary>
private: int maxCurvePoints;
/// <summary>
/// <summary>
/// Длинна всей кривой.
/// </summary>
private: float maxCurveLength;
/// <summary>
/// Нынешнее положение вагона.
/// </summary>
private: vec2 position;
/// <summary>
/// Высота, на которой должны находиться вагоны.
/// </summary>
private: float height;
/// <summary>
/// Нынешнее направление движения вагона.
/// </summary>
private: vec2 direction;
/// <summary>
/// Скорость передвижения вагона.
/// </summary>
private: float speed;
/// <summary>
/// Пройденный путь.
/// </summary>
private: float distanceTraveled;
/// <summary>
/// Путь, который надо пройти, чтобы достичь следующего узла кривой.
/// </summary>
private: float distanceForNextCurvePoint;
/// <summary>
/// Номер последнего пройденого узла кривой.
/// </summary>
private: int curvePointNumber;
public: Wagon(CatmullRomSpline* spline, Engine* engine, Mesh *cube_mesh, float startPointOnPath, float height, float speed);

/// <summary>
/// Рассчитать информацию о положении в пространстве.
/// </summary>
private: inline void CalculateTransform();

/// <summary>
/// Обновить данные для отображения вагона.
/// </summary>
private: void UpdateViewData();
/// <summary>
/// Метод обновления внутренних данных в зависимости от 
///	времени, которое прошло после последнего кадра.
/// </summary>
/// <param name="deltaTime"></param>
public: void Update(float deltaTime);

};

