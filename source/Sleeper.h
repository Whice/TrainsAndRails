#pragma once
#include "framework/mesh.h"
#include "framework/engine.h"
#include "CatmullRomSpline.h"

/// <summary>
/// Шпала.
/// </summary>
class Sleeper
{
private: Engine* engine;
	   /// <summary>
	   /// Представление объекта в мире.
	   /// </summary>
private: Object* view;
	   /// <summary>
	   /// Данные о кривой для передвижения вагона.
	   /// </summary>
private: CatmullRomSpline* spline;

	   /// <summary>
	   /// Положение шпалы.
	   /// </summary>
private: vec2 vec2Position;
public: vec2 GetVec2Position()
{
	return this->vec2Position;
}
	   /// <summary>
	   /// Положение шпалы на пути.
	   /// </summary>
private: float position;
	   /// <summary>
	   /// Высота, на которой должна находиться шапала.
	   /// </summary>
private: float height;
	   /// <summary>
	   /// Направление шпалы.
	   /// </summary>
private: vec2 direction;


public: Sleeper(CatmullRomSpline* spline, Engine* engine, Mesh* plane_mesh, float position, float height);


	  /// <summary>
	  /// Рассчитать информацию о положении в пространстве.
	  /// </summary>
private: inline void CalculateTransform();

	   /// <summary>
	   /// Обновить данные для отображения.
	   /// </summary>
private: void UpdateViewData();
};