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
    float segmentLegth;
    float lengthForNPoints = 10;
    int additionalCounts;
    vec2 v0, v1, v2, v3;
    for (size_t i = 1; i < circleEnd; ++i) 
    {
        v0 = vectors[i - 1];
        v1 = vectors[i];
        v2 = vectors[i + 1];
        v3 = vectors[i + 2];
        segmentLegth = Vec2Length(v2 - v1);
        if (segmentLegth < 0)
            segmentLegth = -segmentLegth;
        additionalCounts = this->aditionaPointsCount * (segmentLegth / lengthForNPoints);
        vector<vec2> singleSpline = CalculateSpline
        (
            this->tension,
            additionalCounts,
            v0,
            v1,
            v2,
            v3
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
    return this->pointsLength[0].pathLength;
}

vec2 CatmullRomSpline::GetPointOnPath(float length)
{
    length = CorrectLength(length);

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
    v = normalize(v);
    float deltaLength = currentPoint.pathLength - length;
    v *= deltaLength;
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

CatmullRomSpline::PointLength* CatmullRomSpline::GetPointCurveInfo(int numberPoint)
{
    int size = this->pointsLength.size();
    if (numberPoint >= size)
    {
        numberPoint -= size;
    }
    else if (numberPoint < 0)
    {
        if (numberPoint < -size)
        {
            numberPoint = numberPoint - ((numberPoint / size) * size);
        }
        numberPoint = size + numberPoint;
    }

    return &this->pointsLength[numberPoint];
}

int CatmullRomSpline::GetPointCurveNumber(float length)
{
    length = CorrectLength(length);
    const size_t size = this->pointsLength.size();
    for (size_t i = 1; i < size; ++i)
    {
        if (this->pointsLength[i].pathLength > length)
            return i - 1;
    }

    return 0;
}

float CatmullRomSpline::CorrectLength(float length)
{
    const float maxLength = GetLengthSpline();
    if (length>0 && length > maxLength)
    {
        int mult = length / maxLength;
        length -= maxLength * mult;
    }
    else if (length < 0 && length < -maxLength)
    {
        int mult = length / maxLength;
        length -= maxLength * mult;
    }
    if (length < 0)
    {
        length = maxLength + length;
    }
    return length;
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
    size_t nextIndex;
    size_t size = this->curvePoints.size();

    //Данные для самой первой точки посчитать сначала (она же в списке и последняя).
    size_t lastIndex = size - 1;
    pointLength.point = &(this->curvePoints[lastIndex]);
    pointLength.vectorLength = Vec2Length(this->curvePoints[lastIndex] - this->curvePoints[lastIndex - 1]);
    //Последняя и первая точка одна и та же, потому для последней (первой) точки следующая будет второй.
    pointLength.direction = normalize(this->curvePoints[1] - this->curvePoints[0]);
    this->pointsLength.push_back(pointLength);

    for (size_t index = 1; index < lastIndex; ++index)
    {
        pointLength.point = &(this->curvePoints[index]);
        pointLength.vectorLength = Vec2Length(this->curvePoints[index] - this->curvePoints[index - 1]);
        pathLength += pointLength.vectorLength;
        pointLength.pathLength = pathLength;
        nextIndex = index + 1;
        pointLength.direction = normalize(this->curvePoints[nextIndex] - this->curvePoints[index]);

        this->pointsLength.push_back(pointLength);
    }

    pathLength += this->pointsLength[0].vectorLength;
    this->pointsLength[0].pathLength = pathLength;
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