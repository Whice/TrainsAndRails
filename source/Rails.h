#pragma once
#include "CatmullRomSpline.h"

/// <summary>
/// ������.
/// </summary>
class Rails
{
private: 
	/// <summary>
	/// ������� ������ �����, ������� � ��� ������.
	/// </summary>
	vector<vec2> railsOuterCountour1;
/// <summary>
/// �������� ������� ������ �����, ������� � ��� ������.
/// </summary>
/// <returns></returns>
public: vector<vec2> GetRailsOuterCountour1();
	/// <summary>
	/// ������� ������ �����, ������� � ��� ������.
	/// </summary>
	vector<vec2> railsOuterCountour2;
	/// <summary>
	/// �������� ������� ������ �����, ������� � ��� ������.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsOuterCountour2();
	/// <summary>
	/// ���������� ������ �����, ������� � ��� ������.
	/// </summary>
	vector<vec2> railsInnerCountour1;
	/// <summary>
	/// �������� ���������� ������ �����, ������� � ��� ������.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsInnerCountour1();
	/// <summary>
	/// ���������� ������ �����, ������� � ��� ������.
	/// </summary>
	vector<vec2> railsInnerCountour2;
	/// <summary>
	/// �������� ���������� ������ �����, ������� � ��� ������.
	/// </summary>
	/// <returns></returns>
public: vector<vec2> GetRailsInnerCountour2();
/// <summary>
/// ��������� �� ��� ������.
/// </summary>
private: float distanceToPath;
/// <summary>
/// ������ ������.
/// </summary>
private: float railsWidth;
	/// <summary>
	/// ������ � ������.
	/// </summary>
private: CatmullRomSpline* spline;

public: Rails(CatmullRomSpline& spline, float distanceToPath, float railsWidth);

/// <summary>
/// ������� ������� �����.
/// </summary>
private: void CreateRails();
	  /// <summary>
	/// ����������� �������� ����� ����������� �����.
	/// </summary>
	/// <param name="a">�������������� �����.</param>
	/// <param name="b">������ �����.</param>
private: inline void RotateWithComplex(vec2& v, double a, double b)
{
	double x = v.x;
	double y = v.y;
	v.x = x * a - y * b;
	v.y = x * b + y * a;
}
	   /// <summary>
	/// ����������� �������� �� 90 �������� ������ ������� �������.
	/// </summary>
private: inline void Rotate90Degree(vec2& v)
{
	RotateWithComplex(v, 0, 1);
}
};