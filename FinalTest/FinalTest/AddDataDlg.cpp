// AddDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "AddDataDlg.h"
#include "afxdialogex.h"


// CAddDataDlg 对话框

IMPLEMENT_DYNAMIC(CAddDataDlg, CDialogEx)

CAddDataDlg::CAddDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddDataDlg::IDD, pParent)
{
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;
}

CAddDataDlg::~CAddDataDlg()
{
}

void CAddDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddDataDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddDataDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD_PIC_PATH, &CAddDataDlg::OnBnClickedAddPicPath)
	ON_BN_CLICKED(IDC_COLOR_BUTTON, &CAddDataDlg::OnBnClickedColorButton)
END_MESSAGE_MAP()


// CAddDataDlg 消息处理程序


void CAddDataDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	//将控件里边的数值取出来
	CString csEditName, csEditValue, csPinPath, csColor;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowText(csEditName);
	GetDlgItem(IDC_VALUE_EDIT)->GetWindowText(csEditValue);
	GetDlgItem(IDC_PICPATH)->GetWindowText(csPinPath);
	GetDlgItem(IDC_COLOR_EDIT)->GetWindowText(csColor);

	if (csEditName.GetLength() != 0 && csEditValue.GetLength() != 0)
	{
		//把数据存到结构体里边
		vector<CString>RGB;
		m_gra->paintData.csName = csEditName;
		m_gra->paintData.csValue = _ttol(csEditValue);
		m_gra->paintData.csPath = csPinPath;
		//获取RGB的值
		RGB = GetRGBValue(csColor);
		m_gra->paintData.iR = _ttoi(RGB[0]);
		m_gra->paintData.iG = _ttoi(RGB[1]);
		m_gra->paintData.iB = _ttoi(RGB[2]);
		RGB.clear();
		m_gra->dataVec.push_back(m_gra->paintData);
		//发送消息
	}
	else{
		MessageBox(L"请确定名字及数值不为空！");
	}

	CDialogEx::OnOK();
}


//设置RGB值
vector<CString> CAddDataDlg::GetRGBValue(CString strSource)
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


void CAddDataDlg::OnBnClickedAddPicPath()
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


void CAddDataDlg::OnBnClickedColorButton()
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



BOOL CAddDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
