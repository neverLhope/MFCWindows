// AddChartDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalTest.h"
#include "AddChartDlg.h"
#include "afxdialogex.h"
#include "FinalTestDoc.h"


// CAddChartDlg �Ի���

IMPLEMENT_DYNAMIC(CAddChartDlg, CDialogEx)

CAddChartDlg::CAddChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddChartDlg::IDD, pParent)
{
}

CAddChartDlg::~CAddChartDlg()
{
}

void CAddChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddChartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_PIC_PATH, &CAddChartDlg::OnBnClickedAddPicPath)
	ON_BN_CLICKED(IDC_COLOR_BUTTON, &CAddChartDlg::OnBnClickedColorButton)
	ON_BN_CLICKED(IDOK, &CAddChartDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddChartDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAddChartDlg ��Ϣ�������


void CAddChartDlg::OnBnClickedAddPicPath()
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
	}
}

//������ɫ
void CAddChartDlg::OnBnClickedColorButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	COLORREF color = RGB(255, 0, 0);      // ��ɫ�Ի���ĳ�ʼ��ɫΪ��ɫ
	CColorDialog colorDlg(color);         // ������ɫ�Ի��򣬴����ʼ��ɫֵ
	if (IDOK == colorDlg.DoModal())       // ��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����
	{
		// ��ȡ��ɫ�Ի�����ѡ�����ɫֵ
		color = colorDlg.GetColor();
		// ��Color�༭������ʾ��ѡ��ɫֵ
		//SetDlgItemInt(IDC_COLOR_EDIT, GetRValue(color));
		CString m_r, m_g, m_b;
		m_r.Format(L"%d", GetRValue(color));
		m_g.Format(L"%d", GetGValue(color));
		m_b.Format(L"%d", GetBValue(color));
		CString csColor = m_r + " " + m_g + " " + m_b;
		SetDlgItemText(IDC_COLOR_EDIT, csColor);         // ��Color�༭������ʾ��ѡ��ɫֵ
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // ��R�༭������ʾ��ѡ��ɫ��R����ֵ
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // ��G�༭������ʾ��ѡ��ɫ��G����ֵ
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // ��B�༭������ʾ��ѡ��ɫ��B����ֵ

	}
}

//���ȷ����ť
void CAddChartDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//���ؼ���ߵ���ֵȡ����
	CString csEditName, csEditValue, csPinPath, csColor;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowText(csEditName);
	GetDlgItem(IDC_VALUE_EDIT)->GetWindowText(csEditValue);
	GetDlgItem(IDC_PICPATH)->GetWindowText(csPinPath);
	GetDlgItem(IDC_TITLE)->GetWindowText(m_csTitle);
	GetDlgItem(IDC_COLOR_EDIT)->GetWindowText(csColor);

	if (csEditName.GetLength() != 0 && csEditValue.GetLength() != 0)
	{
		//�����ݴ浽�ṹ�����
		m_gra->csTitle = m_csTitle;
		m_gra->paintData.csName = csEditName;
		m_gra->paintData.csValue = _ttol(csEditValue);
		m_gra->paintData.csPath = csPinPath;
		m_gra->paintData.penWidth = 1;
		vector<CString>RGB;
		//��ȡRGB��ֵ
		RGB = GetRGBValue(csColor);
		m_gra->paintData.iR = _ttoi(RGB[0]);
		m_gra->paintData.iG = _ttoi(RGB[1]);
		m_gra->paintData.iB = _ttoi(RGB[2]);
		RGB.clear();

		m_gra->dataVec.push_back(m_gra->paintData);
		//���֮������Edit����
		SetEditContent();
		UpdateViews();
		CDialog::OnOK();
	}
	else{
		MessageBox(L"��ȷ�����ּ���ֵ��Ϊ�գ�");
	}

	//CDialogEx::OnOK();
}


void CAddChartDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

//����RGBֵ
vector<CString> CAddChartDlg::GetRGBValue(CString strSource)
{
	//������ȡRGB�ı���
	int nRGB;
	vector<CString> RGB;
	CString strTemp;

	//��ȡRGB
	nRGB = strSource.Find(L" ");
	while (nRGB != -1)
	{
		strTemp = strSource.Left(nRGB + 1);
		RGB.push_back(strTemp);
		strSource = strSource.Mid(nRGB + 1);
		nRGB = strSource.Find(L" ");
		if (nRGB == -1)
		{
			RGB.push_back(strSource);
			break;
		}
	}
	return RGB;
}

//�������е��ĵ���ͼ
void CAddChartDlg::UpdateViews()
{
	//��GetActiveFrame()ȡ�û�ӿ�ܴ��ڣ�Ȼ��ͨ�����Ӵ��ڻ�ȡ���ͼ���ĵ�
	CMDIChildWnd* pChild = (CMDIChildWnd*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	//ȡ�û�ĵ�
	CFinalTestDoc* pDoc = (CFinalTestDoc*)(pChild->GetActiveDocument());
	pDoc->doc_flgFormAdd = true;

	pDoc->csTitle = m_csTitle;

	//������ͼ
	pDoc->UpdateAllViews(NULL);
}

//������֮������Edit������
void CAddChartDlg::SetEditContent()
{
	GetDlgItem(IDC_NAME_EDIT)->SetWindowTextW(L"");
	GetDlgItem(IDC_VALUE_EDIT)->SetWindowTextW(L"");
	GetDlgItem(IDC_PICPATH)->SetWindowTextW(L"ͼƬ·��");
	GetDlgItem(IDC_TITLE)->SetWindowTextW(m_csTitle);
	GetDlgItem(IDC_COLOR_EDIT)->SetWindowTextW(m_csColor);
}

void CAddChartDlg::SetEditContent(int item)
{
	//����RGB����ʾ
	CString m_r, m_g, m_b;
	m_r.Format(L"%d", m_gra->dataVec[item].iR);
	m_g.Format(L"%d", m_gra->dataVec[item].iG);
	m_b.Format(L"%d", m_gra->dataVec[item].iB);
	CString csColor = m_r + " " + m_g + " " + m_b;
	//������ʾ��value
	CString value;
	value.Format(L"%.f", m_gra->dataVec[item].csValue);

	SetDlgItemText(IDC_COLOR_EDIT, csColor);
	SetDlgItemText(IDC_NAME_EDIT, m_gra->dataVec[item].csName);
	SetDlgItemText(IDC_VALUE_EDIT, value);
	SetDlgItemText(IDC_PICPATH, m_gra->dataVec[item].csPath);
	SetDlgItemText(IDC_TITLE, m_gra->csTitle);
}

BOOL CAddChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;

	CString csColor = L"100 100 100";
	vector<CString>RGB;
	//��ȡRGB��ֵ
	RGB = GetRGBValue(csColor);
	SetDlgItemText(IDC_R_EDIT, RGB[0]);
	SetDlgItemText(IDC_G_EDIT, RGB[1]);
	SetDlgItemText(IDC_B_EDIT, RGB[2]);

	SetDlgItemText(IDC_COLOR_EDIT, csColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
