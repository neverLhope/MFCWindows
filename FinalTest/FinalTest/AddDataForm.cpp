// AddDataForm.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "AddDataForm.h"

#include "FinalTestView.h"
#include "resource.h"
#include "FormDoc.h"
#include "FinalTestDoc.h"
#include "ChangeDlg.h"
#include "afxpropertygridctrl.h"



// CAddDataForm

IMPLEMENT_DYNCREATE(CAddDataForm, CFormView)

CAddDataForm::CAddDataForm()
	: CFormView(CAddDataForm::IDD)
{
	m_item = -1;

}

CAddDataForm::~CAddDataForm()
{
}

void CAddDataForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//title控件绑定变量

	DDX_Control(pDX, IDC_SHOW_PROPERTY, m_gridCtrl);

}

BEGIN_MESSAGE_MAP(CAddDataForm, CFormView)
	ON_MESSAGE(WM_SendChangeItem, OnSelectItem)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// CAddDataForm 诊断

#ifdef _DEBUG
void CAddDataForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDataForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDataForm 消息处理程序


BOOL CAddDataForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAddDataForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;
	// TODO:  在此添加专用代码和/或调用基类
	m_gra->hwnd_dataForm = this->GetSafeHwnd();

	HDITEM item;
	item.cxy = 120;
	item.mask = HDI_WIDTH;
	m_gridCtrl.GetHeaderCtrl().SetItem(0, new HDITEM(item));

	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(
		_T("图表名称"),
		_T("NULL"),
		_T("图表标题"));

	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(
		_T("项目名称"),
		_T("NULL"),
		_T("柱状图中某一项的名称"));

	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(
		_T("项目值"),
		_T("NULL"),
		_T("柱状图中某一项的数值"));
/*	pProp2->AddOption(_T("是"));
	pProp2->AddOption(_T("肯定是"));
	pProp2->AddOption(_T("绝对是"));
	pProp2->AllowEdit(FALSE); */ //不允许对选项进行编辑  

	CMFCPropertyGridColorProperty * pProp4 = new CMFCPropertyGridColorProperty(
		_T("颜色"), NULL);
	//pProp4->Enable(FALSE);


	//CMFCPropertyGridFontProperty * pProp5 = new CMFCPropertyGridFontProperty(
	//	_T("选择字体"), font);

	CMFCPropertyGridProperty * group1 = new CMFCPropertyGridProperty(_T("基础信息"));
	CMFCPropertyGridProperty * group2 = new CMFCPropertyGridProperty(_T("扩展项"));

	group1->AddSubItem(pProp1);
	group1->AddSubItem(pProp2);
	group1->AddSubItem(pProp3);
	group2->AddSubItem(pProp4);
	//group2->AddSubItem(pProp5);

	m_gridCtrl.AddProperty(group1);
	m_gridCtrl.AddProperty(group2);
}

LRESULT CAddDataForm::OnSelectItem(WPARAM wParam, LPARAM lParam)
{
	CString* str = (CString*)lParam;
	int item = _ttoi(str[0]);
	m_item = item;
	SetProperty(item);
	return 0;
}


void CAddDataForm::SetProperty(int item)
{

	m_gridCtrl.RemoveAll();
	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(
		_T("图表名称"),
		m_gra->csTitle,
		_T("图表标题"));

	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(
		_T("项目名称"),
		m_gra->dataVec[item].csName,
		_T("柱状图中某一项的名称"));

	CString value;
	value.Format(L"%.f", m_gra->dataVec[item].csValue);
	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(
		_T("项目值"),
		value,
		_T("柱状图中某一项的数值"));

	CMFCPropertyGridColorProperty * pProp4 = new CMFCPropertyGridColorProperty(
		_T("颜色"), RGB(m_gra->dataVec[item].iR, m_gra->dataVec[item].iG, m_gra->dataVec[item].iB));
	//pProp4->Enable(FALSE);

	CMFCPropertyGridProperty * group1 = new CMFCPropertyGridProperty(_T("基础信息"));
	CMFCPropertyGridProperty * group2 = new CMFCPropertyGridProperty(_T("扩展项"));

	group1->AddSubItem(pProp1);
	group1->AddSubItem(pProp2);
	group1->AddSubItem(pProp3);
	group2->AddSubItem(pProp4);

	m_gridCtrl.AddProperty(group1);
	m_gridCtrl.AddProperty(group2);
}
//对property的修改
LRESULT CAddDataForm::OnPropertyChanged(WPARAM, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	
	int i = (int)pProp->GetData();

	CString chName = pProp->GetName();  //被改变的参数名
	CString chValue;
	COleVariant t = pProp->GetValue(); //改变之后的值

	if (chName == "颜色")
	{
		COLORREF color = ((CMFCPropertyGridColorProperty*)pProp)->GetColor();
		pProp = new CMFCPropertyGridColorProperty(
			_T("颜色"),RGB( GetRValue(color), GetGValue(color), GetBValue(color)));

		CString m_r, m_g, m_b;
		m_r.Format(L"%d", GetRValue(color));
		m_g.Format(L"%d", GetGValue(color));
		m_b.Format(L"%d", GetBValue(color));
		CString csColor = m_r + " " + m_g + " " + m_b;
		chValue = csColor;
	}

	//t = pProp->GetOriginalValue();  //改变之前的值
	else
		chValue = t.bstrVal;      //从COleVariant到CString
	SetChangedData(chName, chValue, m_item);


	return 0;
}


void CAddDataForm::SetChangedData(CString changedName, CString changedValue, int item)
{
	if (item == -1)
	{
		MessageBox(L"请选中您要修改的项");
		return;
	}
	if (changedName == "图表名称")
	{
		m_gra->csTitle = changedValue;
	}
	if (changedName == "项目名称")
	{
		m_gra->dataVec[item].csName = changedValue;
	}
	if (changedName == "项目值")
	{
		m_gra->dataVec[item].csValue = _ttoi(changedValue);
	}
	if (changedName == "颜色")
	{
		vector<CString>RGB;
		//获取RGB的值
		RGB = GetRGBValue(changedValue);
		m_gra->dataVec[item].iR = _ttoi(RGB[0]);
		m_gra->dataVec[item].iG = _ttoi(RGB[1]);
		m_gra->dataVec[item].iB = _ttoi(RGB[2]);
		RGB.clear();
	}
	UpdateViews();
}

//设置RGB值
vector<CString> CAddDataForm::GetRGBValue(CString strSource)
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
void CAddDataForm::UpdateViews()
{
	//用GetActiveFrame()取得活动子框架窗口，然后通过该子窗口获取活动视图和文档
	CMDIChildWnd* pChild = (CMDIChildWnd*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	//取得活动文档
	CFinalTestDoc* pDoc = (CFinalTestDoc*)(pChild->GetActiveDocument());
	pDoc->doc_flgFormAdd = true;

	//更新视图
	pDoc->UpdateAllViews(NULL);
}
