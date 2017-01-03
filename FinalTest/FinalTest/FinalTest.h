
// FinalTest.h : FinalTest 应用程序的主头文件
//
#pragma once
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include <afxwin.h>
#include "Columnchart.h"


// CFinalTestApp:
// 有关此类的实现，请参阅 FinalTest.cpp
//

#include <vector>
using namespace std;
class CFinalTestApp : public CWinAppEx
{
public:
	////图标相关的信息
	//CString csTitle;
	//typedef struct Data{
	//	CString csName;
	//	double csValue;
	//	CString csPath;
	//	int iR;
	//	int iG;
	//	int iB;
	//	CRect rect;
	//	int penWidth;
	//	int rValue;//设置选中是的颜色
	//} chartData;
	//Data paintData;
	//vector<Data> dataVec;

	//int selectItem;//判断在List中选中的是哪一个
	////获取窗口句柄
	//HWND hwnd_dataList;
	//HWND hwnd_dataForm;
	CColumnchart m_columnChart;

	CFinalTestApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFinalTestApp theApp;
