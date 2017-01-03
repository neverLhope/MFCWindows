#pragma once

#define WM_FormDataMessage WM_USER+100
#include "Columnchart.h"

// CAddDataForm 窗体视图

class CAddDataForm : public CFormView
{
	DECLARE_DYNCREATE(CAddDataForm)
public:

	virtual void OnInitialUpdate();

	CAddDataForm();           // 动态创建所使用的受保护的构造函数
	virtual ~CAddDataForm();

public:
	enum { IDD = IDD_SHOW_DATA };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCPropertyGridCtrl m_gridCtrl;
	int m_item;
	CGraphic* m_gra;
	//CColumnchart m_columnChart;

	//重写Create将其改为public
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	afx_msg LRESULT OnSelectItem(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnPropertyChanged(WPARAM, LPARAM);
	
	vector<CString> GetRGBValue(CString strSource);
	void SetProperty(int item);
	void SetChangedData(CString changedName, CString changedValue, int item);
	void UpdateViews();
};


