// ChangeTitleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalTest.h"
#include "ChangeTitleDlg.h"
#include "afxdialogex.h"


// CChangeTitleDlg �Ի���

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


// CChangeTitleDlg ��Ϣ�������


void CChangeTitleDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString title;
	GetDlgItem(IDC_TITLE_CHANGE)->GetWindowText(title);
	m_gra->csTitle = title;
	CDialogEx::OnOK();
}
