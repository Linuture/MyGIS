#include "stdafx.h"
#include "MyStruct.h"

#define MYDIALOG_EXPORT
#include "My-Dialog.h"
#include "DialogPointInput.h"

bool MYDIALOG_API g_DlgPointInput (GPointProperty * pntProp)
{
	DialogPointInput dialog;

	if (dialog.DoModal ( ) == IDOK)
	{
		pntProp->pointRadius = dialog.m_GetPointRadius ( ); //radius is legal or is set to 5.
		pntProp->pointColor = RGB (0, 0, 0);
		return true;
	}
	else
	{
		pntProp->pointRadius = dialog.m_GetPointRadius ( );	//cancel and radius is set to 1.
		pntProp->pointColor = RGB (0, 0, 0);
		return false;
	}
}

bool MYDIALOG_API g_DlgCreateproject (CString & projectPath, CString & projectName, CString & projectExtend)
{
	CFileDialog dialog (FALSE, L"pjct", L"我的工程.pjct", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"工程文件(*.pjct)|*pjct||");
	dialog.m_ofn.lpstrTitle = L"设置工程名称";

	if (dialog.DoModal ( ) == IDOK)
	{
		projectPath = dialog.GetPathName ( );
		projectName = dialog.GetFileName ( );
		projectExtend = dialog.GetFileExt ( );
		return true;
	}
	else
	{
		projectPath = L"";
		projectName = L"";
		projectExtend = L"";
		return false;
	}
}