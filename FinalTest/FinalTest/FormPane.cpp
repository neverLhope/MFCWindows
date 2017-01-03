// FormPane.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalTest.h"
#include "FormPane.h"
// CFormPane

IMPLEMENT_DYNAMIC(CFormPane, CDockablePane)

CFormPane::CFormPane()
{
	//创建AddDataForm
	m_addDataForm = (CAddDataForm*)(RUNTIME_CLASS(CAddDataForm)->CreateObject());
}

CFormPane::~CFormPane()
{
}


BEGIN_MESSAGE_MAP(CFormPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CFormPane 消息处理程序




void CFormPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	if (GetSafeHwnd() == NULL)
	{
		return;
	}
	if (m_addDataForm->GetSafeHwnd() != NULL)
	{
		CRect rect;
		GetClientRect(rect);
		m_addDataForm->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

}


void CFormPane::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


int CFormPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码


	RECT rect;
	GetClientRect(&rect);
	m_addDataForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 0, NULL);
	return 0;
}
