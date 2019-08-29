#pragma once
#ifndef _MYDIALOG_H_
#define _MYDIALOG_H_

#ifndef MYDIALOG_EXPORT
#define MYDIALOG_API  __declspec(dllimport)
#else
#define MYDIALOG_API  __declspec(dllexport)
#endif

bool MYDIALOG_API g_DlgPointInput (GPointProperty * pntProp);

bool MYDIALOG_API g_DlgCreateproject (CString & projectPath, CString & projectName, CString & projectExt);

#ifndef MYDIALOG_EXPORT
#pragma comment(lib,"MyDialog.lib")
#endif

#endif