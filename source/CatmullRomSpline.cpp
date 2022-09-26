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
}

vector<vec2> CatmullRomSpline::GetCurvePoints()
{
    return this->curvePoints;
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