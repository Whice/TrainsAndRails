#include "CatmullRomSpline.h"


void CatmullRomSpline::Init(const vector<vec2>& originPoints, float tension, bool isClosedCurve, int aditionaPointsCount)
{
    this->originPoints = originPoints;
    this->tension = tension;
    this->isClosedCurve = isClosedCurve;
    this->aditionaPointsCount = aditionaPointsCount;
}

void CatmullRomSpline::Calculate()
{
    vector<vec2> vectors = BuildVectors(this->originPoints, this->isClosedCurve);

    const size_t circleEnd = vectors.size() - 2;
    for (size_t i = 1; i < circleEnd; ++i) 
    {
        vector<vec2> singleSpline = CalculateSpline
        (
            this->tension,
            this->aditionaPointsCount,
            vectors[i - 1],
            vectors[i],
            vectors[i + 1],
            vectors[i + 2]
        );

        for (vec2 point : singleSpline)
            this->curvePoints.push_back(point);
    }
    CalculateLengthPath();
}

vector<vec2> CatmullRomSpline::GetCurvePoints()
{
    return this->curvePoints;
}

inline float CatmullRomSpline::GetLengthSpline()
{
    return this->pointsLength[this->pointsLength.size() - 1].pathLength;
}

/// <summary>
/// Получить нормализованный вектор.
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
inline vec2 Normalize(vec2 v)
{
    double length = v.length();
    double rLength = length != 0 ? 1 / length : 0;
    v.x *= rLength;
    v.y *= rLength;
    return v;
}

vec2 CatmullRomSpline::GetPointOnPath(float length)
{
    float fullPathLength = GetLengthSpline();
    while (length > fullPathLength)
        length -= fullPathLength;

    size_t index = 1;
    while (this->pointsLength[index].pathLength<length)
        ++index;

    PointLength prevPoint;
    PointLength currentPoint;
    if (index == GetCountCurvePoints())
    {
        prevPoint = this->pointsLength[GetLastIndexCurvePoints()];
        currentPoint = this->pointsLength[0];
    }
    else
    {
        prevPoint = this->pointsLength[index-1];
        currentPoint = this->pointsLength[index];
    }

    vec2 v = *currentPoint.point - *prevPoint.point;
    v = Normalize(v);
    float miniLength = currentPoint.pathLength - length;
    v *= miniLength;
    vec2 result = *prevPoint.point + v;

    return result;
}

size_t CatmullRomSpline::GetCountCurvePoints()
{
    return this->curvePoints.size();
}

size_t CatmullRomSpline::GetLastIndexCurvePoints()
{
    return GetCountCurvePoints() - 1;
}

inline vector<vec2> CatmullRomSpline::BuildVectors(const vector<vec2>& points, bool isClosedCurve)
{
    const size_t lastIndex = points.size() - 1;
    vector<vec2> vectors;

    if (isClosedCurve)
    {
        vectors.push_back(points[lastIndex]);
    }
    else
    {
        vectors.push_back(points[0]);
    }


    for (auto point : points)
    {
        vectors.push_back(point);
    }


    if (isClosedCurve)
    {
        vectors.push_back(points[0]);
        vectors.push_back(points[1]);
    }
    else
    {
        vectors.push_back(points[lastIndex]);
    }


    return vectors;
}

inline void CatmullRomSpline::CalculateLengthPath()
{
    float pathLength=0;
    PointLength pointLength;
    size_t size = this->curvePoints.size();
    for (size_t index = 1; index < size; ++index)
    {
        pointLength.point = &(this->curvePoints[index]);
        pointLength.vectorLength = (this->curvePoints[index] - this->curvePoints[index - 1]).length();
        pathLength += pointLength.vectorLength;
        pointLength.pathLength = pathLength;
        this->pointsLength.push_back(pointLength);
    }
}

inline vector<vec2> CatmullRomSpline::CalculateSpline(float aTension, int n,
    const vec2& p0, const vec2& p1, const vec2& p2, const vec2& p3)
{
    vector<vec2> resultVectors;
    int vectorIndex = 0;
    float step = 1.0f / n;

    for (int t = 0; t < n; ++t) {
        vec2 vector = ReturnCatmullRomVector(t * step, aTension, p0, p1, p2, p3);
        resultVectors.push_back(vector);
    }
    resultVectors.push_back(p2);

    return resultVectors;
}

inline vec2 CatmullRomSpline::ReturnCatmullRomVector(float dt, float aTension,
    const vec2& p0, const vec2& p1, const vec2& p2, const  vec2& p3)
{
    vec2 a = p1;
    vec2 b = aTension * (p2 - p0);
    vec2 c = 3.0f * (p2 - p1) - aTension * (p3 - p1) - 2.0f * aTension * (p2 - p0);
    vec2 d = -2.0f * (p2 - p1) + aTension * (p3 - p1) + aTension * (p2 - p0);

    vec2 result = a + (b * dt) + (c * dt * dt) + (d * dt * dt * dt);

    return result;
}