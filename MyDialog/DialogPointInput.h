#pragma once


// DialogPointInput 对话框

class DialogPointInput : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPointInput)

public:
	DialogPointInput(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogPointInput();
//-----------------------------------------
public:
	int m_GetPointRadius ( ) { return m_pntRadius; }

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_pntRadius;
public:
	afx_msg void OnBnClickedOk ( );
};
