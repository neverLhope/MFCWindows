
// FinalTestView.h : CFinalTestView ��Ľӿ�
//

#pragma once
#define WM_SendChangeItem WM_USER+101
#define WM_SendChangeTitle WM_USER+102

#include "FinalTestDoc.h"
#include "Columnchart.h"

class CFinalTestView : public CView
{
protected: // �������л�����
	CFinalTestView();
	DECLARE_DYNCREATE(CFinalTestView)

// ����
public:
	CFinalTestDoc* GetDocument() const;

// ����
public:
	//�Ҽ�ѡ�����i
	int m_item;
	//�ж��Ƿ���Կ�ʼ��ͼ
	bool m_flgDraw;
	//ColumnChart����
	//CColumnchart m_columnChar;
	CGraphic* m_graphic;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CFinalTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void InitPaintData();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void LoadMenuOnRBtDown_Chart();
	void LoadMenuOnRBtDown_Blank();
	afx_msg void OnChange();
	afx_msg void OnDelete();
	afx_msg void OnChangeTitle();
	afx_msg void OnAdd();
	afx_msg void OnNewChart();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // FinalTestView.cpp �еĵ��԰汾
inline CFinalTestDoc* CFinalTestView::GetDocument() const
   { return reinterpret_cast<CFinalTestDoc*>(m_pDocument); }
#endif

