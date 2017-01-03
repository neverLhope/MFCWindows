// AddChartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "AddChartDlg.h"
#include "afxdialogex.h"
#include "FinalTestDoc.h"


// CAddChartDlg 对话框

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


// CAddChartDlg 消息处理程序


void CAddChartDlg::OnBnClickedAddPicPath()
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
	}
}

//设置颜色
void CAddChartDlg::OnBnClickedColorButton()
{
	// TODO:  在此添加控件通知处理程序代码
	COLORREF color = RGB(255, 0, 0);      // 颜色对话框的初始颜色为红色
	CColorDialog colorDlg(color);         // 构造颜色对话框，传入初始颜色值
	if (IDOK == colorDlg.DoModal())       // 显示颜色对话框，并判断是否点击了“确定”
	{
		// 获取颜色对话框中选择的颜色值
		color = colorDlg.GetColor();
		// 在Color编辑框中显示所选颜色值
		//SetDlgItemInt(IDC_COLOR_EDIT, GetRValue(color));
		CString m_r, m_g, m_b;
		m_r.Format(L"%d", GetRValue(color));
		m_g.Format(L"%d", GetGValue(color));
		m_b.Format(L"%d", GetBValue(color));
		CString csColor = m_r + " " + m_g + " " + m_b;
		SetDlgItemText(IDC_COLOR_EDIT, csColor);         // 在Color编辑框中显示所选颜色值
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));  // 在R编辑框中显示所选颜色的R分量值
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));  // 在G编辑框中显示所选颜色的G分量值
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));  // 在B编辑框中显示所选颜色的B分量值

	}
}

//点击确定按钮
void CAddChartDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//将控件里边的数值取出来
	CString csEditName, csEditValue, csPinPath, csColor;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowText(csEditName);
	GetDlgItem(IDC_VALUE_EDIT)->GetWindowText(csEditValue);
	GetDlgItem(IDC_PICPATH)->GetWindowText(csPinPath);
	GetDlgItem(IDC_TITLE)->GetWindowText(m_csTitle);
	GetDlgItem(IDC_COLOR_EDIT)->GetWindowText(csColor);

	if (csEditName.GetLength() != 0 && csEditValue.GetLength() != 0)
	{
		//把数据存到结构体里边
		m_gra->csTitle = m_csTitle;
		m_gra->paintData.csName = csEditName;
		m_gra->paintData.csValue = _ttol(csEditValue);
		m_gra->paintData.csPath = csPinPath;
		m_gra->paintData.penWidth = 1;
		vector<CString>RGB;
		//获取RGB的值
		RGB = GetRGBValue(csColor);
		m_gra->paintData.iR = _ttoi(RGB[0]);
		m_gra->paintData.iG = _ttoi(RGB[1]);
		m_gra->paintData.iB = _ttoi(RGB[2]);
		RGB.clear();

		m_gra->dataVec.push_back(m_gra->paintData);
		//完成之后设置Edit内容
		SetEditContent();
		UpdateViews();
		CDialog::OnOK();
	}
	else{
		MessageBox(L"请确定名字及数值不为空！");
	}

	//CDialogEx::OnOK();
}


void CAddChartDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//设置RGB值
vector<CString> CAddChartDlg::GetRGBValue(CString strSource)
{
	//用来获取RGB的变量
	int nRGB;
	vector<CString> RGB;
	CString strTemp;

	//获取RGB
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

//更新所有的文档视图
void CAddChartDlg::UpdateViews()
{
	//用GetActiveFrame()取得活动子框架窗口，然后通过该子窗口获取活动视图和文档
	CMDIChildWnd* pChild = (CMDIChildWnd*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	//取得活动文档
	CFinalTestDoc* pDoc = (CFinalTestDoc*)(pChild->GetActiveDocument());
	pDoc->doc_flgFormAdd = true;

	pDoc->csTitle = m_csTitle;

	//更新视图
	pDoc->UpdateAllViews(NULL);
}

//完成添加之后，设置Edit的内容
void CAddChartDlg::SetEditContent()
{
	GetDlgItem(IDC_NAME_EDIT)->SetWindowTextW(L"");
	GetDlgItem(IDC_VALUE_EDIT)->SetWindowTextW(L"");
	GetDlgItem(IDC_PICPATH)->SetWindowTextW(L"图片路径");
	GetDlgItem(IDC_TITLE)->SetWindowTextW(m_csTitle);
	GetDlgItem(IDC_COLOR_EDIT)->SetWindowTextW(m_csColor);
}

void CAddChartDlg::SetEditContent(int item)
{
	//设置RGB的显示
	CString m_r, m_g, m_b;
	m_r.Format(L"%d", m_gra->dataVec[item].iR);
	m_g.Format(L"%d", m_gra->dataVec[item].iG);
	m_b.Format(L"%d", m_gra->dataVec[item].iB);
	CString csColor = m_r + " " + m_g + " " + m_b;
	//设置显示的value
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

	// TODO:  在此添加额外的初始化
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;

	CString csColor = L"100 100 100";
	vector<CString>RGB;
	//获取RGB的值
	RGB = GetRGBValue(csColor);
	SetDlgItemText(IDC_R_EDIT, RGB[0]);
	SetDlgItemText(IDC_G_EDIT, RGB[1]);
	SetDlgItemText(IDC_B_EDIT, RGB[2]);

	SetDlgItemText(IDC_COLOR_EDIT, csColor);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
