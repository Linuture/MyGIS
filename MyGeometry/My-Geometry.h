#pragma once
#ifndef _MYGEOMETRY_H_
#define _MYGEOMETRY_H_

#ifndef MYGEOMETRY_EXPORT
#define MYGEOMETRY_API  __declspec(dllimport)
#else
#define MYGEOMETRY_API  __declspec(dllexport)
#endif
#include "stdafx.h"
#include <vector>
using namespace std;

class MyVector
{
public:
	int m_x;
	int m_y;
public:
	MyVector (int x1, int y1, int x2, int y2)
	{
		m_x = x2 - x1;
		m_y = y2 - y1;
	}
	MyVector (const CPoint & p1, const CPoint & p2)
	{
		m_x = p2.x - p1.x;
		m_y = p2.y - p1.y;
	}
public:
	MyVector m_Plus (MyVector rhs)
	{
		int x = this->m_x + rhs.m_x;
		int y = this->m_y + rhs.m_y;
		return MyVector (0, 0, x, y);
	}
	MyVector m_Minus (MyVector rhs)
	{
		int x = this->m_x - rhs.m_x;
		int y = this->m_y - rhs.m_y;
		return MyVector (0, 0, x, y);
	}
	MyVector m_ProductNumber (double number)
	{
		double x = this->m_x * number;
		double y = this->m_y * number;
		return MyVector (0, 0, (int)x, (int)y);
	}
	int m_CalculateModule ( )
	{
		return sqrt (m_y * m_y + m_x * m_x);
	}
	int m_DotProduct (MyVector rhs)
	{
		return (this->m_x*rhs.m_x + this->m_y*rhs.m_y);
	}
};

class MyGeometry : public CObject
{
public:
	MyGeometry ( ) { m_myDC = nullptr; }
	DECLARE_SERIAL (MyGeometry)
public:
	virtual void m_DrawGeometry ( ) {}
	virtual void m_SetStartPoint (const CPoint & point) {}
	virtual void m_SetEndPoint (const CPoint & point) {}
	virtual bool m_IsPointNear (const CPoint & point) { return false; }
public:
	void m_PassInDC (CDC * dc) {
		m_myDC = dc;
	}
	void m_NullDC ( ) {
		m_myDC = nullptr;
	}
	int m_SetContrast ( ) {
		return m_myDC->SetROP2 (10);
	}
protected:
	CDC * m_myDC;
};

class MyLine : public MyGeometry
{
	//DECLARE_SERIAL (MyLine)
private:
	CPoint m_P1;
	CPoint m_P2;
public:
	MyLine (const CPoint & p1 = CPoint (0, 0),
			const CPoint & p2 = CPoint (0, 0))
	{
		m_P1 = CPoint (p1.x, p1.y);
		m_P2 = CPoint (p2.x, p2.y);
	}
	~MyLine ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawLine ( );
	}
	virtual void m_SetStartPoint (const CPoint & point) {
		this->m_P1 = CPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point) {
		this->m_P2 = CPoint (point.x, point.y);
	}
	virtual bool m_IsPointNear (const CPoint & point)
	{
		bool isPossible = m_IsPointNearPossible (point);
		if (isPossible)
		{
			MyVector vectorA = MyVector (m_P1, m_P2);
			MyVector vectorB = MyVector (m_P1, point);

			int dotProduct = vectorA.m_DotProduct (vectorB);
			int moduleOfA = vectorA.m_CalculateModule ( );
			double ratio = dotProduct / (moduleOfA * moduleOfA);

			MyVector vectorD = vectorA.m_ProductNumber (ratio);

			MyVector vectorC = vectorD.m_Minus (vectorB);
			int moduleOfC = vectorC.m_CalculateModule ( );

			if (moduleOfC <= 7)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}
private:
	bool m_IsPointNearPossible (const CPoint & point) 
	{
		int x = point.x;
		int y = point.y;
		if (x > m_P1.x && x < m_P2.x)
		{
			if (y > m_P1.y && y < m_P2.y)
			{
				return true;
			}
			else if (y < m_P1.y && y > m_P2.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (x < m_P1.x && x > m_P2.x)
		{
			if (y > m_P1.y && y < m_P2.y)
			{
				return true;
			}
			else if (y < m_P1.y && y > m_P2.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	void m_DrawLine ( )
	{
		MyGeometry::m_myDC->MoveTo (m_P1);
		MyGeometry::m_myDC->LineTo (m_P2);
		return;
	}

};

class MyRect : public MyGeometry
{
private:
	CPoint m_P1;//clockwise
	CPoint m_P2;
	CPoint m_P3;
	CPoint m_P4;
public:
	MyRect (const CPoint & p1 = CPoint (0, 0),
			const CPoint & p3 = CPoint (0, 0))
	{
		m_P1 = CPoint (p1.x, p1.y);
		m_P3 = CPoint (p3.x, p3.y);
	}
	~MyRect ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawRect ( );
	}
	virtual void m_SetStartPoint (const CPoint & point) {
		this->m_P1 = CPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point) {
		this->m_P3 = CPoint (point.x, point.y);
	}
public:
	void m_DrawRect ( )
	{
		m_P2 = CPoint (m_P3.x, m_P1.y);
		m_P4 = CPoint (m_P1.x, m_P3.y);
		m_myDC->MoveTo (m_P1);
		m_myDC->LineTo (m_P2);
		m_myDC->LineTo (m_P3);
		m_myDC->LineTo (m_P4);
		m_myDC->LineTo (m_P1);
		return;
	}
};

class MyPoint : public MyGeometry
{
	//DECLARE_SERIAL (MyPoint)
private:
	CPoint m_center;
	const short m_radius = 7;
public:
	MyPoint (const CPoint & p = CPoint (0, 0))
	{
		m_center = CPoint (p.x, p.y);
	}
	~MyPoint ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawPoint ( );
	}
	virtual void m_SetStartPoint (const CPoint & point) {
		this->m_center = CPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point) {
		this->m_center = CPoint (point.x, point.y);
	}
private:
	void m_DrawPoint ( )
	{
		int x1, x2, y1, y2;
		x1 = m_center.x - m_radius;
		x2 = m_center.x + m_radius;
		y1 = m_center.y - m_radius;
		y2 = m_center.y + m_radius;
		m_myDC->Ellipse (x1, y1, x2, y2);

		return;
	}
};

class MyPolygon : public MyGeometry
{
	//DECLARE_SERIAL (MyPolygon)
private:
	vector<CPoint> m_points;
	CPoint m_P1;	//p1 is the temporary start point of the Polygon, 
	CPoint m_P2;	//which means that it is the start point of each line when drawing.
public:
	MyPolygon (const CPoint & p1 = CPoint (0, 0),
			   const CPoint & p2 = CPoint (0, 0))
	{
		m_P1 = CPoint (p1.x, p1.y);
		m_P2 = CPoint (p2.x, p2.y);
	}
	~MyPolygon ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		int length = m_points.size ( );
		for (int i = 0; i < length; i++)
		{
			if (i == 0) 
			{
				m_myDC->MoveTo (m_points[0]);
				m_myDC->LineTo (m_points[1]);
			}
			else
			{
				if (i == length - 1)
				{
					m_myDC->LineTo (m_points[0]);
				}
				else
				{
					m_myDC->LineTo (m_points[i + 1]);
				}
				
			}
			
		}
	}
	virtual void m_SetStartPoint (const CPoint & point) {
		this->m_P1 = CPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point) {
		this->m_P2 = CPoint (point.x, point.y);
	}
public:
	void m_DrawLine ( )
	{
		MyGeometry::m_myDC->MoveTo (m_P1);
		MyGeometry::m_myDC->LineTo (m_P2);
		return;
	}
public:
	void m_AddPoint (const CPoint & point)
	{
		m_points.push_back (CPoint (point.x, point.y));
		return;
	}

	bool m_IsCloseEnough (const CPoint & point)
	{
		int x1, x2, y1, y2;
		x1 = m_points[0].x;
		y1 = m_points[0].y;
		x2 = point.x;
		y2 = point.y;

		double distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		if (distance <= 15)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	CPoint m_GetPolygonStartPoint ( )
	{
		return m_points[0];
	}
};

#ifndef MYGEOMETRY_EXPORT
#pragma comment(lib,"MyGeometry.lib")
#endif

#endif