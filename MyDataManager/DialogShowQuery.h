#pragma once


// DialogShowQuery 对话框

class DialogShowQuery : public CDialogEx
{
	DECLARE_DYNAMIC(DialogShowQuery)
private:
	//void m_ShowList ( );
public:
	DialogShowQuery(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogShowQuery();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ShowQuery };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
};
