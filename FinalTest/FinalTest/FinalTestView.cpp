
// FinalTestView.cpp : CFinalTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CFinalTestView 构造/析构

CFinalTestView::CFinalTestView()
{
	// TODO:  在此处添加构造代码

	//判断是否需要绘图

	m_flgDraw = false;

}

CFinalTestView::~CFinalTestView()
{
}

BOOL CFinalTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}
// CFinalTestView 绘制

void CFinalTestView::OnDraw(CDC* pDC)
{
	CFinalTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CFinalTestDoc* pdoc = (CFinalTestDoc*)pDoc;
	m_flgDraw = pdoc->doc_flgFormAdd;
	// TODO:  在此处为本机数据添加绘制代码
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


// CFinalTestView 诊断

#ifdef _DEBUG
void CFinalTestView::AssertValid() const
{
	CView::AssertValid();
}

void CFinalTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFinalTestDoc* CFinalTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinalTestDoc)));
	return (CFinalTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CFinalTestView 消息处理程序

//初始化数据
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

//左键点击事件
void CFinalTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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

//右键点击事件
void CFinalTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
	//把所有的都设置成未点中的状态
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

//加载Menu
void CFinalTestView::LoadMenuOnRBtDown_Chart()
{
	DWORD dwPos = GetMessagePos();
	CPoint Point(LOWORD(dwPos), HIWORD(dwPos));
	CMenu Menu;
	Menu.LoadMenu(IDR_MENU1);  //你要弹的菜单ID
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
	Menu.LoadMenu(IDR_MENU2);  //你要弹的菜单ID
	CMenu* Popup = Menu.GetSubMenu(0);
	ASSERT(Popup != NULL);
	Popup->EnableMenuItem(4, MF_BYPOSITION | MF_GRAYED);
	Popup->TrackPopupMenu(TPM_CENTERALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this);
	Popup->Detach();
}
//菜单中修改的事件
void CFinalTestView::OnChange()
{
	// TODO:  在此添加命令处理程序代码
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

//删除选项
void CFinalTestView::OnDelete()
{
	// TODO:  在此添加命令处理程序代码

	vector <CGraphic::Data>::iterator iter;
	iter = m_graphic->dataVec.begin() + m_item;
	m_graphic->dataVec.erase(iter);
	CFinalTestDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);
}

//修改标题
void CFinalTestView::OnChangeTitle()
{
	// TODO:  在此添加命令处理程序代码
	CChangeTitleDlg titleDlg;
	if (IDOK == titleDlg.DoModal())
	{
		SetDlgItemText(IDC_TITLE_EDIT, m_graphic->csTitle);
		::SendMessage(m_graphic->hwnd_dataForm, WM_SendChangeTitle, (WPARAM)this->GetSafeHwnd(), (LPARAM)"1");
		CFinalTestDoc* pDoc = GetDocument();
		pDoc->UpdateAllViews(NULL);
	}
}

//添加新的项目
void CFinalTestView::OnAdd()
{
	// TODO:  在此添加命令处理程序代码
	CAddDataDlg addDlg;
	addDlg.DoModal();
	CFinalTestDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(NULL);
}


void CFinalTestView::OnNewChart()
{
	// TODO:  在此添加命令处理程序代码
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
		MessageBox(L"新建图表成功");
		m_flgDraw = true;
	}
}




void CFinalTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO:  在此添加专用代码和/或调用基类
	CFinalTestApp* app = (CFinalTestApp*)AfxGetApp();
	m_graphic = &app->m_columnChart;
}
