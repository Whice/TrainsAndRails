#pragma once
#include "CatmullRomSpline.h"

/// <summary>
/// Рельсы.
/// </summary>
class Rails
{
private: 
	/// <summary>
	/// Внешний контур рельс, ближний к оси кривой.
	/// </summary>
	vector<vec2> railsOuterCountour1;
/// <summary>
/// Получить внешний контур рельс, ближний к оси кривой.
/// </summary>
/// <returns></returns>
public: vector<vec2> GetRailsOuterCountour1();
	/// <summary>
	/// Внешний контур рельс, дальний к оси кривой.
	/// </summary>
	vector<vec2> railsOuterCountour2;
	/// <summary>
	/// Получить внешний контур рельс, дальний к оси кривой.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsOuterCountour2();
	/// <summary>
	/// Внутренний контур рельс, ближний к оси кривой.
	/// </summary>
	vector<vec2> railsInnerCountour1;
	/// <summary>
	/// Получить внутренний контур рельс, ближний к оси кривой.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsInnerCountour1();
	/// <summary>
	/// Внутренний контур рельс, дальний к оси кривой.
	/// </summary>
	vector<vec2> railsInnerCountour2;
	/// <summary>
	/// Получить внутренний контур рельс, дальний к оси кривой.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsInnerCountour2();
/// <summary>
/// Дальность до оси кривой.
/// </summary>
private: float distanceToPath;
/// <summary>
/// Ширина рельсы.
/// </summary>
private: float railsWidth;
	/// <summary>
	/// Данные о кривой.
	/// </summary>
private: CatmullRomSpline* spline;

public: Rails(CatmullRomSpline& spline, float distanceToPath, float railsWidth);

/// <summary>
/// Создать контуры рельс.
/// </summary>
private: void CreateRails();
	  /// <summary>
	/// Осуществить вращение через комплексное число.
	/// </summary>
	/// <param name="a">Действительная часть.</param>
	/// <param name="b">Мнимая часть.</param>
private: inline void RotateWithComplex(vec2& v, double a, double b)
{
	double x = v.x;
	double y = v.y;
	v.x = x * a - y * b;
	v.y = x * b + y * a;
}
	   /// <summary>
	/// Осуществить вращение на 90 градусов против часовой стрелки.
	/// </summary>
private: inline void Rotate90Degree(vec2& v)
{
	RotateWithComplex(v, 0, 1);
}
};