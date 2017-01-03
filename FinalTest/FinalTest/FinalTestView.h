
// FinalTestView.h : CFinalTestView 类的接口
//

#pragma once
#define WM_SendChangeItem WM_USER+101
#define WM_SendChangeTitle WM_USER+102

#include "FinalTestDoc.h"
#include "Columnchart.h"

class CFinalTestView : public CView
{
protected: // 仅从序列化创建
	CFinalTestView();
	DECLARE_DYNCREATE(CFinalTestView)

// 特性
public:
	CFinalTestDoc* GetDocument() const;

// 操作
public:
	//右键选中项的i
	int m_item;
	//判断是否可以开始画图
	bool m_flgDraw;
	//ColumnChart对象
	//CColumnchart m_columnChar;
	CGraphic* m_graphic;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CFinalTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // FinalTestView.cpp 中的调试版本
inline CFinalTestDoc* CFinalTestView::GetDocument() const
   { return reinterpret_cast<CFinalTestDoc*>(m_pDocument); }
#endif

