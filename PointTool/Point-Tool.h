#pragma once
#ifndef _POINTTOOL_H_
#define _POINTTOOL_H_

#ifndef POINTTOOL_EXPORT
#define POINTTOOL_API  __declspec(dllimport)
#else
#define POINTTOOL_API  __declspec(dllexport)
#endif

#include "MyStruct.h"
#include "Base-Tool.h"
#include "My-Geometry.h"
#include <vector>
using namespace std;

class POINTTOOL_API PointTool : public BaseTool
{
public:
	PointTool ( );
	virtual ~PointTool ( );
	PointTool (CView * view);
public:
	virtual short m_ProcMouse (UINT msg, CPoint point, UINT keyFlags);
	virtual short m_LButtonDown (UINT nFlags, CPoint point);
private:
	void m_SetPointProperty ( );
	void m_GetDC ( );
	void m_ReleaseDC ( );
	MyPoint * m_CreateGeometry (const CPoint & point);
	void m_SaveGeometries ( );
private:
	CView * m_pointView;
	CDC * m_dc;
private:
	//GPoint m_point;
	//GPointProperty m_pntProp;
	MyPoint * m_myPoint;
};

#ifndef POINTTOOL_EXPORT
#pragma comment(lib,"PointTool.lib")
#endif

#endif