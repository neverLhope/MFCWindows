// ChangeTitleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "ChangeTitleDlg.h"
#include "afxdialogex.h"


// CChangeTitleDlg 对话框

IMPLEMENT_DYNAMIC(CChangeTitleDlg, CDialogEx)

CChangeTitleDlg::CChangeTitleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeTitleDlg::IDD, pParent)
{
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;
}

CChangeTitleDlg::~CChangeTitleDlg()
{
}

void CChangeTitleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeTitleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangeTitleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChangeTitleDlg 消息处理程序


void CChangeTitleDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString title;
	GetDlgItem(IDC_TITLE_CHANGE)->GetWindowText(title);
	m_gra->csTitle = title;
	CDialogEx::OnOK();
}
