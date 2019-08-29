#pragma once
#ifndef _BASETOOL_H_
#define _BASETOOL_H_

#ifndef BASETOOL_EXPORT
#define BASETOOL_API  __declspec(dllimport)
#else
#define BASETOOL_API  __declspec(dllexport)
#endif

#include "MyStruct.h"
#include "My-Geometry.h"
#include <vector>
using namespace std;

enum Edit_Type
{
	type_input, type_select
};

class BASETOOL_API BaseTool
{
public:
	BaseTool ( );
	virtual ~BaseTool ( );
public:
	virtual short m_ProcMouse (UINT msg, CPoint point, UINT keyFlags);
public:
	virtual short m_LButtonDown (UINT nFlags, CPoint point);
	virtual short m_LButtonUp (UINT nFlags, CPoint point);
	virtual short m_RButtonUp (UINT nFlags, CPoint point);
	virtual short m_MouseMove (UINT nFlags, CPoint point);
	vector<MyGeometry *> * m_GetGeometries ( );
	virtual bool m_IsHighLight (const CPoint & point);
public:
	void m_PassInGeomFromDoc (vector<MyGeometry *> * docGeometries);
protected:
	vector<MyGeometry *> m_geometries;
	vector<MyGeometry *> * m_geomFromDoc;
	//Edit_Type m_editType;
};

#ifndef BASETOOL_EXPORT
#pragma comment(lib,"BaseTool.lib")
#endif

#endif