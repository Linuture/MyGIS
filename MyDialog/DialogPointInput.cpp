// DialogPointInput.cpp: 实现文件
//

#include "stdafx.h"
#include "DialogPointInput.h"
#include "afxdialogex.h"
#include "resource.h"


// DialogPointInput 对话框

IMPLEMENT_DYNAMIC(DialogPointInput, CDialogEx)

DialogPointInput::DialogPointInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_pntRadius (0)
{
	m_pntRadius = 5;
}

DialogPointInput::~DialogPointInput()
{
}

void DialogPointInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange (pDX);
	DDX_Text (pDX, IDC_EDIT_Radius, m_pntRadius);
}


BEGIN_MESSAGE_MAP(DialogPointInput, CDialogEx)
	ON_BN_CLICKED (IDOK, &DialogPointInput::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogPointInput 消息处理程序


void DialogPointInput::OnBnClickedOk ( )
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pntRadius >= 1 && m_pntRadius <= 20)
	{
		return CDialogEx::OnOK ( );
	}
	else
	{
		m_pntRadius = 5;
		AfxMessageBox (_T ("半径输入超出范围，自动设置为默认值5！"));
		return CDialogEx::OnOK ( );
	}
}
