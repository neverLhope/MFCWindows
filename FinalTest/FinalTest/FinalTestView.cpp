
// FinalTestView.cpp : CFinalTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FinalTest.h"
#endif

#include "FinalTestDoc.h"
#include "FinalTestView.h"

#include "FormDoc.h"
#include "conio.h"
#include "ChangeDlg.h"
#include "ChangeTitleDlg.h"
#include "AddDataDlg.h"
#include "AddChartDlg.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinalTestView

IMPLEMENT_DYNCREATE(CFinalTestView, CView)

BEGIN_MESSAGE_MAP(CFinalTestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_CHANGE, &CFinalTestView::OnChange)
	ON_COMMAND(ID_DELETE, &CFinalTestView::OnDelete)
	ON_COMMAND(ID_CHANGE_TITLE, &CFinalTestView::OnChangeTitle)
	ON_COMMAND(ID_ADD, &CFinalTestView::OnAdd)
	ON_COMMAND(ID_NEW_CHART, &CFinalTestView::OnNewChart)
END_MESSAGE_MAP()

// CFinalTestView ����/����

CFinalTestView::CFinalTestView()
{
	// TODO:  �ڴ˴���ӹ������

	//�ж��Ƿ���Ҫ��ͼ

	m_flgDraw = false;

}

CFinalTestView::~CFinalTestView()
{
}

BOOL CFinalTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}
// CFinalTestView ����

void CFinalTestView::OnDraw(CDC* pDC)
{
	CFinalTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CFinalTestDoc* pdoc = (CFinalTestDoc*)pDoc;
	m_flgDraw = pdoc->doc_flgFormAdd;
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	if (m_flgDraw)
	{
		//CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
		//m_graphic = &app->m_columnChart;
		InitPaintData();
		if (m_graphic->dataVec.size() > 0)
		{
			m_graphic->Draw(pDC);
		}
		m_flgDraw = false;
	}
}

void CFinalTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFinalTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFinalTestView ���

#ifdef _DEBUG
void CFinalTestView::AssertValid() const
{
	CView::AssertValid();
}

void CFinalTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinalTestDoc* CFinalTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinalTestDoc)));
	return (CFinalTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CFinalTestView ��Ϣ�������

//��ʼ������
void CFinalTestView::InitPaintData()
{
	int i;
	int count = m_graphic->dataVec.size();
	for (i = 0; i < count; i++)
	{
		m_graphic->bc_hImage = m_graphic->loadPic(m_graphic->dataVec[i].csPath);
		m_graphic->bc_hImageVec.push_back(m_graphic->bc_hImage);
	}
}

//�������¼�
void CFinalTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDown(nFlags, point);
	int i;
	for (i = 0; i < m_graphic->dataVec.size(); i++)
	{
		if (point.x > m_graphic->dataVec[i].rect.left && point.x < m_graphic->dataVec[i].rect.right
			&& point.y > m_graphic->dataVec[i].rect.top && point.y < m_graphic->dataVec[i].rect.bottom)
		{
			m_graphic->dataVec[i].penWidth = 5;
			m_graphic->dataVec[i].rValue = 255;
			m_flgDraw = true;
			CString str;
			str.Format(L"%d", i);
			::SendMessage(m_graphic->hwnd_dataForm, WM_SendChangeItem, (WPARAM)this->GetSafeHwnd(), (LPARAM)&str);
			CFinalTestDoc* pDoc = GetDocument();
			pDoc->UpdateAllViews(NULL);
		}
		else
		{
			m_graphic->dataVec[i].penWidth = 1;
			m_graphic->dataVec[i].rValue = 0;
			m_flgDraw = true;
			CFinalTestDoc* pDoc = GetDocument();
			pDoc->UpdateAllViews(NULL);
		}
	}
}

//�Ҽ�����¼�
void CFinalTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnRButtonDown(nFlags, point);
	int i;
	for (i = 0; i < m_graphic->dataVec.size(); i++)
	{
		if (point.x > m_graphic->dataVec[i].rect.left && point.x < m_graphic->dataVec[i].rect.right
			&& point.y > m_graphic->dataVec[i].rect.top && point.y < m_graphic->dataVec[i].rect.bottom)
		{
			m_graphic->dataVec[i].penWidth = 5;
			m_graphic->dataVec[i].rValue = 255;
			m_item = i;
			m_flgDraw = true;
			CFinalTestDoc* pDoc = GetDocument();
			pDoc->UpdateAllViews(NULL);
			LoadMenuOnRBtDown_Chart();
			return;
		}
		else
		{
			m_graphic->dataVec[i].penWidth = 1;
			m_graphic->dataVec[i].rValue = 0;
			m_flgDraw = true;
			//LoadMenuOnRBtDown_Blank();
		}
	}
	//�����еĶ����ó�δ���е�״̬
	for (i = 0; i < m_graphic->dataVec.size(); i++)
	{
		m_graphic->dataVec[i].penWidth = 1;
		m_graphic->dataVec[i].rValue = 0;
	}
	m_flgDraw = true;
	CFinalTestDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);
	LoadMenuOnRBtDown_Blank();
}

//����Menu
void CFinalTestView::LoadMenuOnRBtDown_Chart()
{
	DWORD dwPos = GetMessagePos();
	CPoint Point(LOWORD(dwPos), HIWORD(dwPos));
	CMenu Menu;
	Menu.LoadMenu(IDR_MENU1);  //��Ҫ���Ĳ˵�ID
	CMenu* Popup = Menu.GetSubMenu(0);
	ASSERT(Popup != NULL);
	Popup->EnableMenuItem(2, MF_BYPOSITION | MF_GRAYED);
	Popup->TrackPopupMenu(TPM_CENTERALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this);
	Popup->Detach();
}
void CFinalTestView::LoadMenuOnRBtDown_Blank()
{
	DWORD dwPos = GetMessagePos();
	CPoint Point(LOWORD(dwPos), HIWORD(dwPos));
	CMenu Menu;
	Menu.LoadMenu(IDR_MENU2);  //��Ҫ���Ĳ˵�ID
	CMenu* Popup = Menu.GetSubMenu(0);
	ASSERT(Popup != NULL);
	Popup->EnableMenuItem(4, MF_BYPOSITION | MF_GRAYED);
	Popup->TrackPopupMenu(TPM_CENTERALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this);
	Popup->Detach();
}
//�˵����޸ĵ��¼�
void CFinalTestView::OnChange()
{
	// TODO:  �ڴ���������������
	m_graphic->selectItem = m_item;
	CChangeDlg changeDlg;
	if (IDOK == changeDlg.DoModal())
	{
		if (changeDlg.flg_DataChanged)
		{
			CFinalTestDoc* pDoc = GetDocument();
			pDoc->UpdateAllViews(NULL);
		}
	}
	return;
}

//ɾ��ѡ��
void CFinalTestView::OnDelete()
{
	// TODO:  �ڴ���������������

	vector <CGraphic::Data>::iterator iter;
	iter = m_graphic->dataVec.begin() + m_item;
	m_graphic->dataVec.erase(iter);
	CFinalTestDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);
}

//�޸ı���
void CFinalTestView::OnChangeTitle()
{
	// TODO:  �ڴ���������������
	CChangeTitleDlg titleDlg;
	if (IDOK == titleDlg.DoModal())
	{
		SetDlgItemText(IDC_TITLE_EDIT, m_graphic->csTitle);
		::SendMessage(m_graphic->hwnd_dataForm, WM_SendChangeTitle, (WPARAM)this->GetSafeHwnd(), (LPARAM)"1");
		CFinalTestDoc* pDoc = GetDocument();
		pDoc->UpdateAllViews(NULL);
	}
}

//����µ���Ŀ
void CFinalTestView::OnAdd()
{
	// TODO:  �ڴ���������������
	CAddDataDlg addDlg;
	addDlg.DoModal();
	CFinalTestDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);
}


void CFinalTestView::OnNewChart()
{
	// TODO:  �ڴ���������������
	//m_graphic->dataVec.clear();

	CAddChartDlg addChart;
	if (IDOK == addChart.DoModal())
	{
		vector <CGraphic::Data>::iterator iter;
		iter = m_graphic->dataVec.begin() ;
		for (iter; iter < m_graphic->dataVec.end() - 1; iter++)
		{
			m_graphic->dataVec.erase(iter);
		}
		MessageBox(L"�½�ͼ��ɹ�");
		m_flgDraw = true;
	}
}




void CFinalTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_graphic = &app->m_columnChart;
}
