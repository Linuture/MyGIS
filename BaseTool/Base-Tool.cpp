#include "stdafx.h"

#define BASETOOL_EXPORT
#include "Base-Tool.h"
#include <vector>

BaseTool::BaseTool ( )
{

}

BaseTool::~BaseTool ( )
{

}


short BaseTool::m_ProcMouse (UINT msg, CPoint point, UINT keyFlags)
{
	/*
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			return (this->m_LButtonDown (keyFlags, point));
		case WM_LBUTTONUP:
			return (this->m_LButtonUp (keyFlags, point));
		case WM_RBUTTONUP:
			return (this->m_RButtonUp (keyFlags, point));
		case WM_MOUSEMOVE:
			return (this->m_MouseMove (keyFlags, point));
		default:
			return 1;
	}
	*/
	return 1;
}

short BaseTool::m_LButtonDown (UINT nFlags, CPoint point) { return 1; }

short BaseTool::m_LButtonUp (UINT nFlags, CPoint point) { return 1; }

short BaseTool::m_RButtonUp (UINT nFlags, CPoint point) { return 1; }

short BaseTool::m_MouseMove (UINT nFlags, CPoint point) { return 1; }

vector<MyGeometry *> * BaseTool::m_GetGeometries ( )
{
	return &(this->m_geometries);
}

bool BaseTool::m_IsHighLight (const CPoint & point)
{
	return false;
}

void BaseTool::m_PassInGeomFromDoc (vector<MyGeometry *> * docGeometries)
{
	this->m_geomFromDoc = docGeometries;
	return;
}