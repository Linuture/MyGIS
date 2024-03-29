
// MyGISView.h: CMyGISView 类的接口
//

#pragma once
#include "Base-Tool.h"


class CMyGISView : public CView
{
private:
	BaseTool * m_tool;
	//vector<MyGeometry *> m_geometries;
private:
	void m_DeleteTool ( );
	void m_GetGeomFromTool ( );
	//void m_DeleteGeomtries ( );
public:
	vector<MyGeometry *> * m_GetGeomeFromDoc ( );
//----------------------------------------------
protected: // 仅从序列化创建
	CMyGISView() noexcept;
	DECLARE_DYNCREATE(CMyGISView)

// 特性
public:
	CMyGISDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyGISView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnMenuPointinput ( );
	afx_msg void OnProjectCreateproject ( );
	afx_msg void OnMenuLineinput ( );
	afx_msg void OnMouseMove (UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMenuPolygoninput ( );
	afx_msg void OnMenuLineselect ( );
	afx_msg void OnAddgeometries ( );
	afx_msg void OnQuerygeometries ( );
};

#ifndef _DEBUG  // MyGISView.cpp 中的调试版本
inline CMyGISDoc* CMyGISView::GetDocument() const
   { return reinterpret_cast<CMyGISDoc*>(m_pDocument); }
#endif

