#include "stdafx.h"

#define POLYGONTOOL_EXPORT
#include "My-Geometry.h"
#include "Polygon-Tool.h"

IMPLEMENT_SERIAL (MyGeometry, CObject, 1)
//IMPLEMENT_SERIAL (MyLine, MyGeometry, 1)

PolygonTool::PolygonTool ( )
{
	this->m_polygonView = nullptr;
	this->m_dc = nullptr;
	this->m_myPolygon = nullptr;
	this->m_flag = 0;
}

PolygonTool::~PolygonTool ( )
{
	this->m_polygonView = nullptr;
	this->m_dc = nullptr;
	this->m_myPolygon = nullptr;
}

PolygonTool::PolygonTool (CView * view)
{
	this->m_polygonView = view;
	//this->m_myGeom = new MyLine ( );
	this->m_flag = 0;
}

short PolygonTool::m_ProcMouse (UINT msg, CPoint point, UINT keyFlags)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			return (this->m_LButtonDown (keyFlags, point));
		case WM_MOUSEMOVE:
			return (this->m_MouseMove (keyFlags, point));
		case WM_RBUTTONUP:
			return (this->m_RButtonUp (keyFlags, point));
		default:
			return 1;
	}
	return 1;
}

short PolygonTool::m_LButtonDown (UINT nFlags, CPoint point)
{
	if (!m_IsDrawing ( ))
	{
		m_CreateGeometry (point);

		m_GetDC ( );

		m_myPolygon->m_DrawLine ( );
		m_myPolygon->m_AddPoint (point);

		m_ReleaseDC ( );

		m_IncreaseFlag ( );

		return 1;
	}
	else
	{
		return 0;
	}
}

short PolygonTool::m_MouseMove (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		if (m_CanClose ( ))
		{
			if (m_myPolygon->m_IsCloseEnough (point))
			{
				CPoint endPoint = m_myPolygon->m_GetPolygonStartPoint ( );
				m_ShowDrawing (endPoint);
			}
			else
			{
				m_ShowDrawing (point);
			}
		}
		else
		{
			m_ShowDrawing (point);
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

short PolygonTool::m_RButtonUp (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		if (m_CanClose ( ))
		{
			if (m_myPolygon->m_IsCloseEnough (point))
			{
				CPoint endPoint = m_myPolygon->m_GetPolygonStartPoint ( );

				m_GetDC ( );

				m_myPolygon->m_SetEndPoint (endPoint);

				m_myPolygon->m_DrawLine ( );
				m_myPolygon->m_AddPoint (endPoint);

				m_ReleaseDC ( );

				m_SaveGeometry ( );
				//m_DeleteGeometry ( );

				m_SetFlagZero ( );
			}
			else
			{
				m_EndAndStartDraw (point);
			}
		}
		else
		{
			m_EndAndStartDraw (point);
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

void PolygonTool::m_GetDC ( )
{
	m_dc = m_polygonView->GetDC ( );
	m_myPolygon->m_PassInDC (m_dc);
	return;
}

void PolygonTool::m_ReleaseDC ( )
{
	m_myPolygon->m_NullDC ( );
	m_polygonView->ReleaseDC (m_dc);
	m_dc = nullptr;
	return;
}

bool PolygonTool::m_IsDrawing ( )
{
	if (m_flag != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PolygonTool::m_SetFlagZero ( )
{
	m_flag = 0;
}

void PolygonTool::m_IncreaseFlag ( )
{
	m_flag = m_flag + 1;
}

void PolygonTool::m_CreateGeometry (const CPoint & point)
{
	this->m_myPolygon = new MyPolygon (point, point);

	return;
}

void PolygonTool::m_SaveGeometry ( )
{
	this->BaseTool::m_geometries.push_back (this->m_myPolygon);
	//delete this->m_myPolygon;
	//this->m_myPolygon = nullptr;

	return;
}

bool PolygonTool::m_CanClose ( )
{
	if (m_flag > 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PolygonTool::m_ShowDrawing (const CPoint & point)
{
	m_GetDC ( );

	m_myPolygon->m_SetContrast ( );

	m_myPolygon->m_DrawLine ( );

	m_myPolygon->m_SetEndPoint (point);

	m_myPolygon->m_DrawLine ( );

	m_ReleaseDC ( );
}

void PolygonTool::m_EndAndStartDraw (const CPoint & point)
{
	m_GetDC ( );

	m_myPolygon->m_SetEndPoint (point);

	m_myPolygon->m_DrawLine ( );
	m_myPolygon->m_AddPoint (point);

	m_myPolygon->m_SetStartPoint (point);
	m_myPolygon->m_SetEndPoint (point);

	m_myPolygon->m_DrawLine ( );

	m_ReleaseDC ( );

	m_IncreaseFlag ( );
}