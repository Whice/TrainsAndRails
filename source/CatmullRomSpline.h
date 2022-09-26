﻿#pragma once
#include "glm/vec2.hpp"
#include <vector>

using namespace std;
using namespace glm;

class CatmullRomSpline
{
#pragma region Исходные данные.

    /// <summary>
    /// Натяжение.
    /// </summary>
private: float tension;
       /// <summary>
       /// Изначальные узлы, по которым строится кривая.
       /// </summary>
private: vector<vec2> originPoints;
       /// <summary>
       /// Кривая будет замкнутой.
       /// </summary>
private: bool isClosedCurve;
       /// <summary>
       /// Количество дополнительных точек.
       /// </summary>
private: int aditionaPointsCount;

#pragma endregion Исходные данные.

#pragma region Полученные после подсчета данные.

       /// <summary>
   /// Узлы построенной кривой.
   /// </summary>
private: vector<vec2> curvePoints;

#pragma endregion Полученные после подсчета данные.

#pragma region инициализация и подсчет данных.

/// <summary>
/// Инициализироать объект для создания кривой.
/// </summary>
/// <param name="originPoints"></param>
/// <param name="tension"></param>
/// <param name="isClosedCurve"></param>
/// <param name="aditionaPointsCount"></param>
public: void Init(const vector<vec2> &originPoints, float tension = 0.4f, bool isClosedCurve = true, int aditionaPointsCount = 30);
      /// <summary>
      /// Расчитать конкретный вектор для заданного шага.
      /// </summary>
      /// <param name="t">Шаг.</param>
      /// <param name="p0">Полюс 1.</param>
      /// <param name="p1">Полюс 2.</param>
      /// <param name="p2">Полюс 3.</param>
      /// <param name="p3">Полюс 4.</param>
      /// <returns>Вектор.</returns>
private: inline static vec2 ReturnCatmullRomVector(float dt, float aTension,
    const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p3);
       /// <summary>
       /// Расчитать вектора для одного участка сплайна, ограниченного p0, p1, p2 и p3.
       /// </summary>
       /// <param name="aTension">Натяжение.</param>
       /// <param name="n">Количество узлов между полюсами.</param>
       /// <param name="p0">Полюс 1.</param>
       /// <param name="p1">Полюс 2.</param>
       /// <param name="p2">Полюс 3.</param>
       /// <param name="p3">Полюс 4.</param>
       /// <returns>Вектора сплайна.</returns>
private: inline static  vector<vec2> CalculateSpline(float aTension, int n,
    const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p3);
       /// <summary>
       /// Построить вектора, по которым будут расчитываться сплайны.
       /// </summary>
       /// <param name="aPoints">Исходные точки.</param>
       /// <param name="aIsClosedCurve">Индикатор замкнутости.</param>
       /// <returns>Вектора.</returns>
private: inline static  vector<vec2> BuildVectors(const vector<vec2> &points, bool isClosedCurve);
       /// <summary>
              /// Вычислить узловые CatmullRom-сплайна.
              /// </summary>
              /// <param name="aPoints">Полюса сплайна (исходные точки). Должно быть не менее 2-х полюсов.</param>
              /// <param name="aTension">Натяжение сплайна.</param>
              /// <param name="n">Число узлов между полюсами сплайна.</param>
              /// <param name="aIsClosedCurve">True - сплайн будет замкнут.</param>
public: void Calculate();

#pragma endregion инициализация и подсчет данных.

/// <summary>
/// Получить посчитанную кривую.
/// </summary>
/// <returns></returns>
public: vector<vec2> GetCurvePoints();

};
