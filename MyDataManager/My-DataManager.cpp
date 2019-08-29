#include "stdafx.h"

#define MYDATAMANAGER_EXPORT

#include "My-DataManager.h"
using namespace std;

bool MyDataBase::m_ConnectDB ( )
{
	BOOL isOpen = m_DB.OpenEx (m_strConnect, CDatabase::noOdbcDialog);
	if (isOpen == FALSE || !m_DB.BeginTrans ( ))
	{
		AfxMessageBox (_T ("连接数据库失败!"));
		return false;
	}
	else
	{
		return true;
	}

}

void MyDataBase::m_CloseDB ( )
{
	m_DB.Close ( );
}

void MyDataBase::m_InsertGeometries (int layerID, int geomID, CString geomType, CString wkt, int width, COLORREF color)
{
	bool isConnect = this->m_ConnectDB ( );
	if (isConnect)
	{
		TRY
		{
			CString cstrLayerID;
			CString cstrGeomID;
			CString cstrWidth;
			CString cstrColor;
			cstrLayerID.Format ((CString)"%d", layerID);
			cstrGeomID.Format ((CString)"%d", geomID);
			cstrWidth.Format ((CString)"%d", width);
			cstrColor.Format ((CString)"%d", color);

			CString strSQL =
				(CString)"insert into G_Geometries values ('" +
				cstrLayerID +
				(CString)"','" +
				cstrGeomID +
				(CString)"','" +
				geomType +
				(CString)"','" +
				wkt +
				(CString)"','" +
				cstrWidth +
				(CString)"','" +
				cstrColor +
				(CString)"')";
			m_DB.ExecuteSQL (strSQL);
			m_DB.CommitTrans ( );
		}
			CATCH_ALL (e)
		{
			TCHAR tc_ErrorMsg[255];
			e->GetErrorMessage (tc_ErrorMsg, 255);

			CString str_HitMsg;
			str_HitMsg =
				(CString)"添加数据库记录失败，原因是:\r\n " +
				(CString)tc_ErrorMsg;
			AfxMessageBox (str_HitMsg);
		}
		END_CATCH_ALL

			this->m_CloseDB ( );
	}
	else
	{
		AfxMessageBox ((CString)"添加数据库记录失败，数据库未连接!");
		return;
	}
}

void MyDataBase::m_InsertLayer (int layerID, CString layerName)
{

}

bool MyDataBase::m_QueryGeometries (DBGeometries & geometry)
{
	bool isConnect = this->m_ConnectDB ( );
	//DBGeometries geometry;
	if (isConnect)
	{
		CRecordset myDBSet (&m_DB);
		TRY
		{
			CString strSQL = (CString)"select * from G_Geometries";
			myDBSet.Open (CRecordset::snapshot, strSQL, CRecordset::readOnly);

			int index = 0;
			if (!myDBSet.IsEOF ( ))
			{
				CString cstrLayerID;
				CString cstrGeomID;
				CString geomType;
				CString wkt;
				CString cstrWidth;
				CString cstrColor;

				myDBSet.GetFieldValue ((CString)"L_ID", cstrLayerID);
				cstrLayerID.TrimRight ( );

				myDBSet.GetFieldValue ((CString)"G_ID", cstrGeomID);
				cstrGeomID.TrimRight ( );

				myDBSet.GetFieldValue ((CString)"GType", geomType);
				geomType.TrimRight ( );

				myDBSet.GetFieldValue ((CString)"WKT", wkt);
				wkt.TrimRight ( );

				myDBSet.GetFieldValue ((CString)"width", cstrWidth);
				cstrWidth.TrimRight ( );

				myDBSet.GetFieldValue ((CString)"color", cstrColor);
				cstrColor.TrimRight ( );

				geometry.layerID = cstrLayerID;
				geometry.geomID = cstrGeomID;
				geometry.geomType = geomType;
				geometry.wkt = wkt;
				geometry.width = cstrWidth;
				geometry.color = cstrColor;

				myDBSet.Close ( );
			}
			else
			{
				// do nothing
			}
		}
			CATCH_ALL (e)
		{
			TCHAR tc_ErrorMsg[255];
			e->GetErrorMessage (tc_ErrorMsg, 255);

			CString str_HitMsg;
			str_HitMsg =
				(CString)"添加数据库记录失败，原因是:\r\n " +
				(CString)tc_ErrorMsg;

			AfxMessageBox (str_HitMsg);

			m_DB.Rollback ( );
			myDBSet.Close ( );
			m_DB.Close ( );
			return false;
		}
		END_CATCH_ALL

			this->m_CloseDB ( );

		return true;
	}
	else
	{
		AfxMessageBox ((CString)"添加数据库记录失败，数据库未连接!");
		return false;
	}
}