// AddDataForm.cpp : ʵ���ļ�
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
	//title�ؼ��󶨱���

	DDX_Control(pDX, IDC_SHOW_PROPERTY, m_gridCtrl);

}

BEGIN_MESSAGE_MAP(CAddDataForm, CFormView)
	ON_MESSAGE(WM_SendChangeItem, OnSelectItem)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// CAddDataForm ���

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


// CAddDataForm ��Ϣ�������


BOOL CAddDataForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CAddDataForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_gra = &app->m_columnChart;
	// TODO:  �ڴ����ר�ô����/����û���
	m_gra->hwnd_dataForm = this->GetSafeHwnd();

	HDITEM item;
	item.cxy = 120;
	item.mask = HDI_WIDTH;
	m_gridCtrl.GetHeaderCtrl().SetItem(0, new HDITEM(item));

	CMFCPropertyGridProperty* pProp1 = new CMFCPropertyGridProperty(
		_T("ͼ������"),
		_T("NULL"),
		_T("ͼ�����"));

	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(
		_T("��Ŀ����"),
		_T("NULL"),
		_T("��״ͼ��ĳһ�������"));

	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(
		_T("��Ŀֵ"),
		_T("NULL"),
		_T("��״ͼ��ĳһ�����ֵ"));
/*	pProp2->AddOption(_T("��"));
	pProp2->AddOption(_T("�϶���"));
	pProp2->AddOption(_T("������"));
	pProp2->AllowEdit(FALSE); */ //�������ѡ����б༭  

	CMFCPropertyGridColorProperty * pProp4 = new CMFCPropertyGridColorProperty(
		_T("��ɫ"), NULL);
	//pProp4->Enable(FALSE);


	//CMFCPropertyGridFontProperty * pProp5 = new CMFCPropertyGridFontProperty(
	//	_T("ѡ������"), font);

	CMFCPropertyGridProperty * group1 = new CMFCPropertyGridProperty(_T("������Ϣ"));
	CMFCPropertyGridProperty * group2 = new CMFCPropertyGridProperty(_T("��չ��"));

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
		_T("ͼ������"),
		m_gra->csTitle,
		_T("ͼ�����"));

	CMFCPropertyGridProperty* pProp2 = new CMFCPropertyGridProperty(
		_T("��Ŀ����"),
		m_gra->dataVec[item].csName,
		_T("��״ͼ��ĳһ�������"));

	CString value;
	value.Format(L"%.f", m_gra->dataVec[item].csValue);
	CMFCPropertyGridProperty* pProp3 = new CMFCPropertyGridProperty(
		_T("��Ŀֵ"),
		value,
		_T("��״ͼ��ĳһ�����ֵ"));

	CMFCPropertyGridColorProperty * pProp4 = new CMFCPropertyGridColorProperty(
		_T("��ɫ"), RGB(m_gra->dataVec[item].iR, m_gra->dataVec[item].iG, m_gra->dataVec[item].iB));
	//pProp4->Enable(FALSE);

	CMFCPropertyGridProperty * group1 = new CMFCPropertyGridProperty(_T("������Ϣ"));
	CMFCPropertyGridProperty * group2 = new CMFCPropertyGridProperty(_T("��չ��"));

	group1->AddSubItem(pProp1);
	group1->AddSubItem(pProp2);
	group1->AddSubItem(pProp3);
	group2->AddSubItem(pProp4);

	m_gridCtrl.AddProperty(group1);
	m_gridCtrl.AddProperty(group2);
}
//��property���޸�
LRESULT CAddDataForm::OnPropertyChanged(WPARAM, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*)lParam;
	
	int i = (int)pProp->GetData();

	CString chName = pProp->GetName();  //���ı�Ĳ�����
	CString chValue;
	COleVariant t = pProp->GetValue(); //�ı�֮���ֵ

	if (chName == "��ɫ")
	{
		COLORREF color = ((CMFCPropertyGridColorProperty*)pProp)->GetColor();
		pProp = new CMFCPropertyGridColorProperty(
			_T("��ɫ"),RGB( GetRValue(color), GetGValue(color), GetBValue(color)));

		CString m_r, m_g, m_b;
		m_r.Format(L"%d", GetRValue(color));
		m_g.Format(L"%d", GetGValue(color));
		m_b.Format(L"%d", GetBValue(color));
		CString csColor = m_r + " " + m_g + " " + m_b;
		chValue = csColor;
	}

	//t = pProp->GetOriginalValue();  //�ı�֮ǰ��ֵ
	else
		chValue = t.bstrVal;      //��COleVariant��CString
	SetChangedData(chName, chValue, m_item);


	return 0;
}


void CAddDataForm::SetChangedData(CString changedName, CString changedValue, int item)
{
	if (item == -1)
	{
		MessageBox(L"��ѡ����Ҫ�޸ĵ���");
		return;
	}
	if (changedName == "ͼ������")
	{
		m_gra->csTitle = changedValue;
	}
	if (changedName == "��Ŀ����")
	{
		m_gra->dataVec[item].csName = changedValue;
	}
	if (changedName == "��Ŀֵ")
	{
		m_gra->dataVec[item].csValue = _ttoi(changedValue);
	}
	if (changedName == "��ɫ")
	{
		vector<CString>RGB;
		//��ȡRGB��ֵ
		RGB = GetRGBValue(changedValue);
		m_gra->dataVec[item].iR = _ttoi(RGB[0]);
		m_gra->dataVec[item].iG = _ttoi(RGB[1]);
		m_gra->dataVec[item].iB = _ttoi(RGB[2]);
		RGB.clear();
	}
	UpdateViews();
}

//����RGBֵ
vector<CString> CAddDataForm::GetRGBValue(CString strSource)
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
void CAddDataForm::UpdateViews()
{
	//��GetActiveFrame()ȡ�û�ӿ�ܴ��ڣ�Ȼ��ͨ�����Ӵ��ڻ�ȡ���ͼ���ĵ�
	CMDIChildWnd* pChild = (CMDIChildWnd*)((CFrameWnd*)AfxGetApp()->m_pMainWnd)->GetActiveFrame();
	//ȡ�û�ĵ�
	CFinalTestDoc* pDoc = (CFinalTestDoc*)(pChild->GetActiveDocument());
	pDoc->doc_flgFormAdd = true;

	//������ͼ
	pDoc->UpdateAllViews(NULL);
}
