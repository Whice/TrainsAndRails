#pragma once
#include "glm/vec2.hpp"
#include <vector>
#include "AdditionalFunctions.h"

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

       /// <summary>
       /// Хранит длинну пути для двумерной точки.
       /// </summary>
public: struct PointLength
{
public:
    vec2* point;
    float pathLength;
    float vectorLength;
    vec2 direction;
};
      /// <summary>
      /// Набор точек и длинны для них.
      /// </summary>
private: vector<PointLength> pointsLength;

#pragma endregion Полученные после подсчета данные.

#pragma region инициализация и подсчет данных.

       /// <summary>
       /// Инициализироать объект для создания кривой.
       /// </summary>
       /// <param name="originPoints"></param>
       /// <param name="tension"></param>
       /// <param name="isClosedCurve"></param>
       /// <param name="aditionaPointsCount"></param>
public: void Init(const vector<vec2>& originPoints, float tension = 0.4f, bool isClosedCurve = true, int aditionaPointsCount = 30);
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
private: inline static  vector<vec2> BuildVectors(const vector<vec2>& points, bool isClosedCurve);
       /// <summary>
       /// Посчитать длину пути для каждого узла.
       /// </summary>
private: inline void CalculateLengthPath();

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
      /// <summary>
      /// Получить длину всей кривой.
      /// </summary>
public: inline float GetLengthSpline();
      /// <summary>
      /// Получить точку на указанной длине пути.
      /// (Не узел кривой, а именно точку, для которой будет верна эта длина пути.)
      /// </summary>
public: vec2 GetPointOnPath(float length);
      /// <summary>
      /// Получить количество узлов кривой.
      /// </summary>
public: inline size_t GetCountCurvePoints();
       /// <summary>
       /// Получить индекс последнего узла кривой.
       /// </summary>
private: inline size_t GetLastIndexCurvePoints();
       /// <summary>
       /// Получить информацию о узле кривой по ее порядковому номеру.
       /// </summary>
public:PointLength* GetPointCurveInfo(int numberPoint);
      /// <summary>
      /// Получить номер последнего узла, который встретился на пути с такой длиной.
      /// </summary>
public:int GetPointCurveNumber(float length);
      /// <summary>
      /// Скорректировать длину, чтобы она верно пападала в диапазон с 0 по максимальную длинну.
      /// </summary>
private: float CorrectLength(float length);

};

