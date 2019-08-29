#pragma once
#ifndef _MYDATAMANAGER_H_
#define _MYDATAMANAGER_H_

#ifndef MYDATAMANAGER_EXPORT
#define MYDATAMANAGER_API  __declspec(dllimport)
#else
#define MYDATAMANAGER_API  __declspec(dllexport)
#endif

#include "stdafx.h"
#include <afxdb.h>

struct DBGeometries
{
	CString layerID;
	CString geomID;
	CString geomType;
	CString wkt;
	CString width;
	CString color;
};

class MYDATAMANAGER_API MyDataBase
{
private:
	const CString m_strConnect = _T ("DSN=CloudDB;UID=sa;PWD=2018dlxxxt");
	CDatabase m_DB;
public:
	bool m_ConnectDB ( );
	void m_CloseDB ( );
	CDatabase * m_GetDB ( ) { return &m_DB; }
public:
	void m_InsertLayer (int layerID, CString layerName);
	void m_InsertGeometries (int layerID, int geomID, CString geomType, CString wkt, int width, COLORREF color);
	void m_InsertAnnotation (int layerID, int annotID, CString annotation);
	void m_QueryLayer ( );
	bool m_QueryGeometries (DBGeometries & geometry);
	void m_QueryAnnotation ( );
};

#ifndef MYDATAMANAGER_EXPORT
#pragma comment(lib,"MyDataManager.lib")
#endif

#endif