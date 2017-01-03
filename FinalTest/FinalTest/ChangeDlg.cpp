// ChangeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"


// CChangeDlg 对话框

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


// CChangeDlg 消息处理程序

//设置图形的RGB值
void CChangeDlg::OnBnClickedColorButton()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(255, 0, 0);      // 颜色对话框的初始颜色为红色
	CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值
	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”
	{
		color = colorDlg.GetColor();      // 获取颜色对话框中选择的颜色值
		SetDlgItemInt(IDC_COLOR_EDIT, color);         // 在Color编辑框中显示所选颜色值
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // 在R编辑框中显示所选颜色的R分量值
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // 在G编辑框中显示所选颜色的G分量值
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // 在B编辑框中显示所选颜色的B分量值

		m_gra->dataVec[m_gra->selectItem].iR = GetRValue(color);
		m_gra->dataVec[m_gra->selectItem].iG = GetGValue(color);
		m_gra->dataVec[m_gra->selectItem].iB = GetBValue(color);
	}
	
}
//修改dlg中选择图片
void CChangeDlg::OnBnClickedAddPicPath()
{
	// TODO:  在此添加控件通知处理程序代码

	// 设置过滤器
	TCHAR szFilter[] = _T("图片(*.bmp)|*.bmp|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_PICPATH, strFilePath);

		m_gra->dataVec[m_gra->selectItem].csPath = strFilePath;
	}
}
//修改完成之后点击的按钮
void CChangeDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

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
//重写OnInitDialog函数，初始化数据
BOOL CChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	// 异常:  OCX 属性页应返回 FALSE
}
