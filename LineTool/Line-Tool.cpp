#include "stdafx.h"

#define LINETOOL_EXPORT
#include "Line-Tool.h"
//#include "MyGISView.h"

IMPLEMENT_SERIAL (MyGeometry, CObject, 1)
//IMPLEMENT_SERIAL (MyLine, MyGeometry, 1)

LineTool::LineTool ( )
{
	this->m_lineView = nullptr;
	this->m_dc = nullptr;
	this->m_myLine = nullptr;
	this->m_flag = 0;
	this->m_geomFromDoc = nullptr;
}

LineTool::~LineTool ( )
{
	this->m_lineView = nullptr;
	this->m_dc = nullptr;
	this->m_myLine = nullptr;
	this->m_geomFromDoc = nullptr;
}

LineTool::LineTool (CView * view)
{
	this->m_lineView = view;
	this->m_flag = 0;
	this->m_geomFromDoc = nullptr;
	//this->m_editType = type;
}

short LineTool::m_ProcMouse (UINT msg, CPoint point, UINT keyFlags)
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

short LineTool::m_LButtonDown (UINT nFlags, CPoint point)
{
	if (!m_IsDrawing ( )) // draw
	{
		m_CreateGeometry (point);

		m_GetDC ( );

		m_myLine->m_DrawGeometry ( );

		m_ReleaseDC ( );

		m_SetFlagOne ( );
		return 1;
	}
	else // select
	{
		return 0;
	}
}

short LineTool::m_MouseMove (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		m_GetDC ( );

		m_myLine->m_SetContrast ( );

		m_myLine->m_DrawGeometry ( );

		m_myLine->m_SetEndPoint (point);

		m_myLine->m_DrawGeometry ( );

		m_ReleaseDC ( );

		return 1;
	}
	else
	{
		if (m_IsHighLight (point))
		{
			return 0;
		}
		else
		{
			return 0;
		}
		return 0;
	}
}

short LineTool::m_RButtonUp (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		m_GetDC ( );

		m_myLine->m_SetEndPoint (point);

		m_myLine->m_DrawGeometry ( );

		m_ReleaseDC ( );

		m_SaveGeometry ( );
		//m_DeleteGeometry ( );

		m_SetFlagZero ( );

		return 1;
	}
	else
	{		
		return 0;
	}
}

void LineTool::m_GetDC ( )
{
	m_dc = m_lineView->GetDC ( );
	m_myLine->m_PassInDC (m_dc);
	return;
}

void LineTool::m_ReleaseDC ( )
{
	m_myLine->m_NullDC ( );
	m_lineView->ReleaseDC (m_dc);
	m_dc = nullptr;
	return;
}

bool LineTool::m_IsDrawing ( )
{
	if (m_flag == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LineTool::m_SetFlagZero ( )
{
	m_flag = 0;
}

void LineTool::m_SetFlagOne ( )
{
	m_flag = 1;
}

void LineTool::m_CreateGeometry (const CPoint & point)
{
	this->m_myLine = new MyLine (point, point);

	return;
}

void LineTool::m_SaveGeometry ( )
{
	this->BaseTool::m_geometries.push_back (this->m_myLine);
	//delete this->m_myLine;
	//this->m_myLine = nullptr;

	return;
}

bool LineTool::m_IsHighLight (const CPoint & point)
{
/*	CMyGISDoc * myDoc = m_lineView->GetDocument ( );
	ASSERT_VALID (myDoc);
	if (myDoc == nullptr)
	{
		return false;
	}
	else
	{
		vector<MyGeometry *> * geometries = m_lineView->m_GetGeometries ( );
		int length = geometries->size ( );
		for (int i = 0; i < length; i++)
		{
			BOOL isLine = (*geometries)[i]->IsKindOf (RUNTIME_CLASS (MyLine));
			if (isLine == TRUE)
			{
				(*geometries)[i]->m_IsPointNear (point);
			}
			else
			{
				return false;
			}
			//m_lineView->GetRuntimeClass ( );
		}
	}
	

	if (m_geomFromDoc == nullptr)
	{
		return false;
	}
	else
	{
		int length = m_geomFromDoc->size ( );
		for (int i = 0; i < length; i++)
		{
			BOOL isLine = (*m_geomFromDoc)[i]->IsKindOf (RUNTIME_CLASS (MyLine));
			if (isLine == TRUE)
			{
				bool isHighLight = (*m_geomFromDoc)[i]->m_IsPointNear (point);
				if (isHighLight)
				{
					//m_GetDC ( );
					m_dc = m_lineView->GetDC ( );
					(*m_geomFromDoc)[i]->m_PassInDC (m_dc);
					(*m_geomFromDoc)[i]->m_DrawGeometry ( );
					(*m_geomFromDoc)[i]->m_NullDC ( );
					m_lineView->ReleaseDC (m_dc);
					m_dc = nullptr;
					return true;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		return false;
	}
	*/
	return false;
}

//-------------------------- LineSelect --------------------------

LineSelect::LineSelect ( )
{
	this->m_lineView = nullptr;
	this->m_dc = nullptr;
	this->m_myGeometry = nullptr;
	this->m_geomFromDoc = nullptr;
}

LineSelect::~LineSelect ( )
{
	this->m_lineView = nullptr;
	this->m_dc = nullptr;
	this->m_geomFromDoc = nullptr;
}

LineSelect::LineSelect (CView * view)
{
	this->m_lineView = view;
	this->m_geomFromDoc = nullptr;
}

short LineSelect::m_ProcMouse (UINT msg, CPoint point, UINT keyFlags)
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

short LineSelect::m_LButtonDown (UINT nFlags, CPoint point)
{
	if (!m_IsDrawing ( )) 
	{
		m_CreateGeometry (point);

		m_GetDC ( );

		m_myGeometry->m_DrawGeometry ( );

		m_ReleaseDC ( );

		m_SetFlagOne ( );
		return 1;
	}
	else
	{
		return 0;
	}
}

short LineSelect::m_MouseMove (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		m_GetDC ( );

		m_myGeometry->m_SetContrast ( );

		m_myGeometry->m_DrawGeometry ( );

		m_myGeometry->m_SetEndPoint (point);

		m_myGeometry->m_DrawGeometry ( );

		m_ReleaseDC ( );

		return 1;
	}
	else
	{
		if (m_IsHighLight (point))
		{
			return 0;
		}
		else
		{
			return 0;
		}
		return 0;
	}
}

short LineSelect::m_LButtonUp (UINT nFlags, CPoint point)
{
	return 0;
}

short LineSelect::m_RButtonUp (UINT nFlags, CPoint point)
{
	if (m_IsDrawing ( ))
	{
		m_GetDC ( );

		m_myGeometry->m_SetEndPoint (point);

		m_myGeometry->m_DrawGeometry ( );

		m_ReleaseDC ( );

		m_SaveGeometry ( );
		//m_DeleteGeometry ( );

		m_SetFlagZero ( );

		return 1;
	}
	else
	{
		return 0;
	}
}

void LineSelect::m_GetDC ( )
{
	m_dc = m_lineView->GetDC ( );
	m_myGeometry->m_PassInDC (m_dc);
	return;
}

void LineSelect::m_ReleaseDC ( )
{
	m_myGeometry->m_NullDC ( );
	m_lineView->ReleaseDC (m_dc);
	m_dc = nullptr;
	return;
}

bool LineSelect::m_IsDrawing ( )
{
	if (m_flag == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LineSelect::m_SetFlagZero ( )
{
	m_flag = 0;
}

void LineSelect::m_SetFlagOne ( )
{
	m_flag = 1;
}

void LineSelect::m_CreateGeometry (const CPoint & point)
{
	this->m_myGeometry = new MyLine (point, point);

	return;
}

void LineSelect::m_SaveGeometry ( )
{
	this->BaseTool::m_geometries.push_back (this->m_myGeometry);
	//delete this->m_myLine;
	//this->m_myLine = nullptr;

	return;
}

bool LineSelect::m_IsHighLight (const CPoint & point)
{
	/*	CMyGISDoc * myDoc = m_lineView->GetDocument ( );
		ASSERT_VALID (myDoc);
		if (myDoc == nullptr)
		{
			return false;
		}
		else
		{
			vector<MyGeometry *> * geometries = m_lineView->m_GetGeometries ( );
			int length = geometries->size ( );
			for (int i = 0; i < length; i++)
			{
				BOOL isLine = (*geometries)[i]->IsKindOf (RUNTIME_CLASS (MyLine));
				if (isLine == TRUE)
				{
					(*geometries)[i]->m_IsPointNear (point);
				}
				else
				{
					return false;
				}
				//m_lineView->GetRuntimeClass ( );
			}
		}
		*/

	if (m_geomFromDoc == nullptr)
	{
		return false;
	}
	else
	{
		int length = m_geomFromDoc->size ( );
		for (int i = 0; i < length; i++)
		{
			BOOL isLine = (*m_geomFromDoc)[i]->IsKindOf (RUNTIME_CLASS (MyLine));
			if (isLine == TRUE)
			{
				bool isHighLight = (*m_geomFromDoc)[i]->m_IsPointNear (point);
				if (isHighLight)
				{
					//m_GetDC ( );
					m_dc = m_lineView->GetDC ( );
					(*m_geomFromDoc)[i]->m_PassInDC (m_dc);
					(*m_geomFromDoc)[i]->m_DrawGeometry ( );
					(*m_geomFromDoc)[i]->m_NullDC ( );
					m_lineView->ReleaseDC (m_dc);
					m_dc = nullptr;
					return true;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		return false;
	}
}
