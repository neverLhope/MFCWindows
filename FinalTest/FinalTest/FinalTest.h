
// FinalTest.h : FinalTest Ӧ�ó������ͷ�ļ�
//
#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include <afxwin.h>
#include "Columnchart.h"


// CFinalTestApp:
// �йش����ʵ�֣������ FinalTest.cpp
//

#include <vector>
using namespace std;
class CFinalTestApp : public CWinAppEx
{
public:
	////ͼ����ص���Ϣ
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
	//	int rValue;//����ѡ���ǵ���ɫ
	//} chartData;
	//Data paintData;
	//vector<Data> dataVec;

	//int selectItem;//�ж���List��ѡ�е�����һ��
	////��ȡ���ھ��
	//HWND hwnd_dataList;
	//HWND hwnd_dataForm;
	CColumnchart m_columnChart;

	CFinalTestApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFinalTestApp theApp;
