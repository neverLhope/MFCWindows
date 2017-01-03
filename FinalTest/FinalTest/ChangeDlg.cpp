// ChangeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalTest.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"


// CChangeDlg �Ի���

IMPLEMENT_DYNAMIC(CChangeDlg, CDialogEx)

CChangeDlg::CChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeDlg::IDD, pParent)
{
	flg_DataChanged = false;
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;
}

CChangeDlg::~CChangeDlg()
{
}

void CChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_COLOR_BUTTON, &CChangeDlg::OnBnClickedColorButton)
	ON_BN_CLICKED(IDC_ADD_PIC_PATH, &CChangeDlg::OnBnClickedAddPicPath)
	ON_BN_CLICKED(IDOK, &CChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CChangeDlg ��Ϣ�������

//����ͼ�ε�RGBֵ
void CChangeDlg::OnBnClickedColorButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	COLORREF color = RGB(255, 0, 0);      // ��ɫ�Ի���ĳ�ʼ��ɫΪ��ɫ
	CColorDialog colorDlg(color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ
	if (IDOK == colorDlg.DoModal())       // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����
	{
		color = colorDlg.GetColor();      // ��ȡ��ɫ�Ի�����ѡ�����ɫֵ
		SetDlgItemInt(IDC_COLOR_EDIT, color);         // ��Color�༭������ʾ��ѡ��ɫֵ
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // ��R�༭������ʾ��ѡ��ɫ��R����ֵ
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // ��G�༭������ʾ��ѡ��ɫ��G����ֵ
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // ��B�༭������ʾ��ѡ��ɫ��B����ֵ

		m_gra->dataVec[m_gra->selectItem].iR = GetRValue(color);
		m_gra->dataVec[m_gra->selectItem].iG = GetGValue(color);
		m_gra->dataVec[m_gra->selectItem].iB = GetBValue(color);
	}
	
}
//�޸�dlg��ѡ��ͼƬ
void CChangeDlg::OnBnClickedAddPicPath()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	// ���ù�����
	TCHAR szFilter[] = _T("ͼƬ(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_PICPATH, strFilePath);

		m_gra->dataVec[m_gra->selectItem].csPath = strFilePath;
	}
}
//�޸����֮�����İ�ť
void CChangeDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString name, value;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowText(name);
	GetDlgItem(IDC_VALUE_EDIT)->GetWindowText(value);
	if (!name.IsEmpty())
		m_gra->dataVec[m_gra->selectItem].csName = name;
	if (!value.IsEmpty())
		m_gra->dataVec[m_gra->selectItem].csValue = _ttol(value);

	flg_DataChanged = true;
	CDialogEx::OnOK();
}
//��дOnInitDialog��������ʼ������
BOOL CChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString value;
	CString r,g,b;
	value.Format(L"%.1f", m_gra->dataVec[m_gra->selectItem].csValue);
	r.Format(L"%d", m_gra->dataVec[m_gra->selectItem].iR);
	g.Format(L"%d", m_gra->dataVec[m_gra->selectItem].iG);
	b.Format(L"%d", m_gra->dataVec[m_gra->selectItem].iB);
	GetDlgItem(IDC_NAME_EDIT)->SetWindowTextW(m_gra->dataVec[m_gra->selectItem].csName);
	GetDlgItem(IDC_VALUE_EDIT)->SetWindowTextW(value);
	GetDlgItem(IDC_PICPATH)->SetWindowTextW(m_gra->dataVec[m_gra->selectItem].csPath);
	GetDlgItem(IDC_R_EDIT)->SetWindowTextW(r);
	GetDlgItem(IDC_G_EDIT)->SetWindowTextW(g);
	GetDlgItem(IDC_B_EDIT)->SetWindowTextW(b);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
