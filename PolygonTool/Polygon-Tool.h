#pragma once
#ifndef _POLYGONTOOL_H_
#define _POLYGONTOOL_H_

#ifndef POLYGONTOOL_EXPORT
#define POLYGONTOOL_API  __declspec(dllimport)
#else
#define POLYGONTOOL_API  __declspec(dllexport)
#endif

#include "Base-Tool.h"

class POLYGONTOOL_API PolygonTool : public BaseTool
{
public:
	PolygonTool ( );
	virtual ~PolygonTool ( );
	PolygonTool (CView * view);
public:
	virtual short m_ProcMouse (UINT msg, CPoint point, UINT keyFlags);
	virtual short m_LButtonDown (UINT nFlags, CPoint point);
	//virtual short m_LButtonUp (UINT nFlags, CPoint point);
	virtual short m_RButtonUp (UINT nFlags, CPoint point);
	virtual short m_MouseMove (UINT nFlags, CPoint point);
private:
	void m_GetDC ( );
	void m_ReleaseDC ( );
	bool m_IsDrawing ( );
	void m_SetFlagZero ( );
	void m_IncreaseFlag ( );
	void m_CreateGeometry (const CPoint & point);
	void m_SaveGeometry ( );
	bool m_CanClose ( );
private:
	void m_ShowDrawing (const CPoint & point);
	void m_EndAndStartDraw (const CPoint & point);
private:
	CView * m_polygonView;
	CDC * m_dc;
private:
	//GPoint m_point;
	//GPointProperty m_pntProp;
	MyPolygon * m_myPolygon;
	short m_flag;
};

#include "Base-Tool.h"
#include "My-Geometry.h"

#ifndef POLYGONTOOL_EXPORT
#pragma comment(lib,"PolygonTool.lib")
#endif

#endif