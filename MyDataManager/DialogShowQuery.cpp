// DialogShowQuery.cpp: 实现文件
//

#include "stdafx.h"
#include "MyDataManager.h"
#include "DialogShowQuery.h"
#include "afxdialogex.h"

#include "My-DataManager.h"
// DialogShowQuery 对话框

IMPLEMENT_DYNAMIC(DialogShowQuery, CDialogEx)

DialogShowQuery::DialogShowQuery(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ShowQuery, pParent)
{

}

DialogShowQuery::~DialogShowQuery()
{
}

void DialogShowQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange (pDX);
	DDX_Control (pDX, IDC_LIST1, m_list);

	//m_ShowList ( );
}


BEGIN_MESSAGE_MAP(DialogShowQuery, CDialogEx)
END_MESSAGE_MAP()


// DialogShowQuery 消息处理程序
/*
void DialogShowQuery::m_ShowList ( )
{
	for (int i = 0; i < 6; ++i)
	{
		m_list.DeleteColumn (0);
	}
	m_list.DeleteAllItems ( );
	m_list.InsertColumn (0, (CString)"图层号", LVCFMT_LEFT, 100, 0);
	m_list.InsertColumn (1, (CString)"几何对象号", LVCFMT_LEFT, 100, 1);
	m_list.InsertColumn (2, (CString)"几何对象类型", LVCFMT_LEFT, 100, 2);
	m_list.InsertColumn (3, (CString)"WKT", LVCFMT_LEFT, 100, 3);
	m_list.InsertColumn (4, (CString)"线宽", LVCFMT_LEFT, 100, 4);
	m_list.InsertColumn (5, (CString)"颜色", LVCFMT_LEFT, 100, 5);

	MyDataBase myDB;
	DBGeometries geometry;
	bool isQuery = myDB.m_QueryGeometries (geometry);

	int index = 0;
	if (isQuery)
	{
		m_list.SetItemText (index, 0, geometry.layerID);
		m_list.SetItemText (index, 1, geometry.geomID);
		m_list.SetItemText (index, 2, geometry.geomType);
		m_list.SetItemText (index, 3, geometry.wkt);
		m_list.SetItemText (index, 4, geometry.width);
		m_list.SetItemText (index, 5, geometry.color);

		index++;
	}
	else
	{
		return;
	}
}
*/