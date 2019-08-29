#pragma once
#ifndef _LINETOOL_H_
#define _LINETOOL_H_

#ifndef LINETOOL_EXPORT
#define LINETOOL_API  __declspec(dllimport)
#else
#define LINETOOL_API  __declspec(dllexport)
#endif

#include "Base-Tool.h"
#include "My-Geometry.h"


class LINETOOL_API LineTool : public BaseTool
{
public:
	LineTool ( );
	virtual ~LineTool ( );
	LineTool (CView * view);
public:
	virtual short m_ProcMouse (UINT msg, CPoint point, UINT keyFlags);
	virtual short m_LButtonDown (UINT nFlags, CPoint point);
	//virtual short m_LButtonUp (UINT nFlags, CPoint point);
	virtual short m_RButtonUp (UINT nFlags, CPoint point);
	virtual short m_MouseMove (UINT nFlags, CPoint point);
	virtual bool m_IsHighLight (const CPoint & point);
private:
	void m_GetDC ( );
	void m_ReleaseDC ( );
	bool m_IsDrawing ( );
	void m_SetFlagZero ( );
	void m_SetFlagOne ( );
	void m_CreateGeometry (const CPoint & point);
	void m_SaveGeometry ( );
private:
	CView * m_lineView;
	CDC * m_dc;
private:
	//GPoint m_point;
	//GPointProperty m_pntProp;
	MyLine * m_myLine;
	short m_flag;
};

class LINETOOL_API LineSelect : public BaseTool
{
public:
	LineSelect ( );
	virtual ~LineSelect ( );
	LineSelect (CView * view);
public:
	virtual short m_ProcMouse (UINT msg, CPoint point, UINT keyFlags);
	virtual short m_LButtonDown (UINT nFlags, CPoint point);
	virtual short m_LButtonUp (UINT nFlags, CPoint point);
	virtual short m_RButtonUp (UINT nFlags, CPoint point);
	virtual short m_MouseMove (UINT nFlags, CPoint point);
	virtual bool m_IsHighLight (const CPoint & point);
private:
	void m_GetDC ( );
	void m_ReleaseDC ( );
	bool m_IsDrawing ( );
	void m_SetFlagZero ( );
	void m_SetFlagOne ( );
	void m_CreateGeometry (const CPoint & point);
	void m_SaveGeometry ( );
private:
	CView * m_lineView;
	CDC * m_dc;
private:
	MyGeometry * m_myGeometry;
	short m_flag;
};

#ifndef LINETOOL_EXPORT
#pragma comment(lib,"LineTool.lib")
#endif

#endif