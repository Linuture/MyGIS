
// MyGISView.cpp: CMyGISView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyGIS.h"
#endif

#include "MyGISDoc.h"
#include "MyGISView.h"

//--------------self-defined headers-------------------
#include "Point-Tool.h"
#include "Line-Tool.h"
#include "Polygon-Tool.h"
#include "My-DataManager.h"
#include "DialogShowQuery.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyGISView

IMPLEMENT_DYNCREATE(CMyGISView, CView)

BEGIN_MESSAGE_MAP(CMyGISView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN ( )
	ON_COMMAND (ID_Menu_PointInput, &CMyGISView::OnMenuPointinput)
	ON_COMMAND (ID_Project_CreateProject, &CMyGISView::OnProjectCreateproject)
	ON_COMMAND (ID_Menu_LineInput, &CMyGISView::OnMenuLineinput)
	ON_WM_MOUSEMOVE ( )
	ON_WM_RBUTTONUP ( )
	ON_COMMAND (ID_Menu_PolygonInput, &CMyGISView::OnMenuPolygoninput)
	ON_COMMAND (ID_Menu_LineSelect, &CMyGISView::OnMenuLineselect)
	ON_COMMAND (ID_AddGeometries, &CMyGISView::OnAddgeometries)
	ON_COMMAND (ID_QueryGeometries, &CMyGISView::OnQuerygeometries)
END_MESSAGE_MAP()

//---------------------------

void CMyGISView::m_DeleteTool ( )
{
	if (this->m_tool != nullptr)
	{
		m_GetGeomFromTool ( );
		delete (this->m_tool);
		this->m_tool = nullptr;
	}
	else
	{
		// do nothing.
	}
}

void CMyGISView::m_GetGeomFromTool ( )
{
	CMyGISDoc * myDoc = GetDocument ( );
	ASSERT_VALID (myDoc);
	if (myDoc == nullptr)
	{
		return;
	}
	else
	{
		vector<MyGeometry *> * toolGeometries = m_tool->m_GetGeometries ( );
		myDoc->m_PassInGeomFromTool (toolGeometries);
	}
}
/*
void CMyGISView::m_DeleteGeomtries ( )
{
	int length = m_geometries.size ( );
	for (int i = 0; i < length; i++)
	{
		delete m_geometries[i];
	}
}
*/

vector<MyGeometry *> * CMyGISView::m_GetGeomeFromDoc ( )
{
	CMyGISDoc * myDoc = GetDocument ( );
	ASSERT_VALID (myDoc);
	if (!myDoc)
	{
		return nullptr;
	}
	else
	{
		return (myDoc->m_GetGeometries ( ));
	}
}
// CMyGISView 构造/析构

CMyGISView::CMyGISView() noexcept
{
	// TODO: 在此处添加构造代码
	this->m_tool = nullptr;
}

CMyGISView::~CMyGISView()
{
	m_DeleteTool ( );
	//m_DeleteGeomtries ( );
}

BOOL CMyGISView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyGISView 绘图

void CMyGISView::OnDraw(CDC * pDC)
{
	CMyGISDoc * myDoc = GetDocument();
	ASSERT_VALID(myDoc);
	if (!myDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	m_DeleteTool ( );
	vector<MyGeometry *> * geometries = myDoc->m_GetGeometries ( );
	int length = geometries->size ( );
	for (int i = 0; i < length; i++)
	{
		(*geometries)[i]->m_PassInDC (pDC);
		(*geometries)[i]->m_DrawGeometry ( );
		(*geometries)[i]->m_NullDC ( );
	}

}


// CMyGISView 打印

BOOL CMyGISView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyGISView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyGISView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyGISView 诊断

#ifdef _DEBUG
void CMyGISView::AssertValid() const
{
	CView::AssertValid();
}

void CMyGISView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGISDoc* CMyGISView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGISDoc)));
	return (CMyGISDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyGISView 消息处理程序


void CMyGISView::OnLButtonDown (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_tool != nullptr)
	{
		m_tool->m_ProcMouse (WM_LBUTTONDOWN, point, nFlags);
	}
	else
	{
		//nothing, you did not choose anything on menu
	}
	CView::OnLButtonDown (nFlags, point);
}

void CMyGISView::OnMouseMove (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_tool != nullptr)
	{
		m_tool->m_PassInGeomFromDoc (m_GetGeomeFromDoc ( ));
		m_tool->m_ProcMouse (WM_MOUSEMOVE, point, nFlags);
	}
	else
	{
		//nothing, you did not choose anything on menu
	}
	CView::OnMouseMove (nFlags, point);
}


void CMyGISView::OnRButtonUp (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_tool != nullptr)
	{
		m_tool->m_ProcMouse (WM_RBUTTONUP, point, nFlags);
	}
	else
	{
		//nothing, you did not choose anything on menu
	}
	CView::OnRButtonUp (nFlags, point);
}

void CMyGISView::OnMenuPointinput ( )
{
	// TODO: 在此添加命令处理程序代码
	m_DeleteTool ( );
	this->m_tool = new PointTool (this);
}


void CMyGISView::OnProjectCreateproject ( )
{
	// TODO: 在此添加命令处理程序代码
}


void CMyGISView::OnMenuLineinput ( )
{
	// TODO: 在此添加命令处理程序代码
	m_DeleteTool ( );
	this->m_tool = new LineTool (this);
}


void CMyGISView::OnMenuPolygoninput ( )
{
	// TODO: 在此添加命令处理程序代码
	m_DeleteTool ( );
	this->m_tool = new PolygonTool (this);
}


void CMyGISView::OnMenuLineselect ( )
{
	// TODO: 在此添加命令处理程序代码
	m_DeleteTool ( );
	this->m_tool = new LineTool (this);
}


void CMyGISView::OnAddgeometries ( )
{
	// TODO: 在此添加命令处理程序代码
	MyDataBase myDB;
	myDB.m_InsertGeometries (1, 1, (CString)"POINT", (CString)"(20,20)", 1, RGB (0, 0, 0));
	myDB.m_InsertGeometries (1, 2, (CString)"POINT", (CString)"(50,50)", 1, RGB (255, 0, 0));
	myDB.m_InsertGeometries (1, 3, (CString)"POINT", (CString)"(120,120)", 2, RGB (0, 0, 0));
	myDB.m_InsertGeometries (2, 4, (CString)"POINT", (CString)"(80,70)", 2, RGB (0, 0, 0));
	myDB.m_InsertGeometries (2, 5, (CString)"LINESTRING", (CString)"(30 50, 80 80, 140 70)", 1, RGB (255, 0, 0));
	myDB.m_InsertGeometries (3, 6, (CString)"LINESTRING", (CString)"(40 50, 20 80, 120 130)", 2, RGB (0, 0, 0));
	AfxMessageBox ((CString)"添加成功!");
}


void CMyGISView::OnQuerygeometries ( )
{
	// TODO: 在此添加命令处理程序代码
	DialogShowQuery dialog;
	dialog.DoModal ( );
	return;
}
