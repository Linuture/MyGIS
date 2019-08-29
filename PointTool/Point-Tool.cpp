#include "stdafx.h"

#define POINTTOOL_EXPORT
#include "Point-Tool.h"
//#include "My-Dialog.h"

IMPLEMENT_SERIAL (MyGeometry, CObject, 1)
//IMPLEMENT_SERIAL (MyLine, MyGeometry, 1)

PointTool::PointTool ( )
{
	this->m_pointView = nullptr;
	this->m_dc = nullptr;
	this->m_myPoint = nullptr;
}

PointTool::~PointTool ( )
{
	this->m_pointView = nullptr;
	this->m_dc = nullptr;
	this->m_myPoint = nullptr;
}

PointTool::PointTool (CView * view)
{
	this->m_pointView = view;
	//m_SetPointProperty ( );
}

short PointTool::m_ProcMouse (UINT msg, CPoint point, UINT keyFlags)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			return (this->m_LButtonDown (keyFlags, point));
		default:
			return 1;
	}
	return 1;
}

short PointTool::m_LButtonDown (UINT nFlags, CPoint point) 
{
	/*	//AfxMessageBox (_T("LeftButtonDown"));
	//CPen pen(0, 1, m_pntProp.pointColor);
	//CPen * oldPen = m_dc->SelectObject (&pen);
	m_SetDC ( );
	int x1, x2, y1, y2;
	x1 = point.x - m_pntProp.pointRadius;
	x2 = point.x + m_pntProp.pointRadius;
	y1 = point.y - m_pntProp.pointRadius;
	y2 = point.y + m_pntProp.pointRadius;
	m_dc->Ellipse (x1, y1, x2, y2);
	m_DeleteDC ( ); 
	//m_dc->SelectObject (oldPen);*/

	this->m_myPoint = this->m_CreateGeometry (point);

	this->m_GetDC ( );

	m_myPoint->m_SetStartPoint (point);
	m_myPoint->m_DrawGeometry ( );

	this->m_ReleaseDC ( );

	this->m_SaveGeometries ( );
	return 1;
}

void PointTool::m_SetPointProperty ( )
{
/*	bool isInput = g_DlgPointInput (&m_pntProp);
	if (isInput)
	{
		AfxMessageBox (_T ("属性输入成功！"));
	}
	else
	{
		AfxMessageBox (_T ("属性输入失败！"));
	}
	return; */
}

void PointTool::m_GetDC ( )
{
	m_dc = m_pointView->GetDC ( );
	m_myPoint->m_PassInDC (m_dc);
	return;
}

void PointTool::m_ReleaseDC ( )
{
	m_myPoint->m_NullDC ( );
	m_pointView->ReleaseDC (m_dc);
	m_dc = nullptr;
	return;
}

MyPoint * PointTool::m_CreateGeometry (const CPoint & point)
{
	return new MyPoint (point);
}

void PointTool::m_SaveGeometries ( )
{
	this->BaseTool::m_geometries.push_back (this->m_myPoint);

	//It's not right, because I delete what the points coordinate.
	//They should be delete at last.
	//delete this->m_myPoint;
	//this->m_myPoint = nullptr;

	return;
}