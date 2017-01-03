#pragma once

#include "Columnchart.h"
// CAddDataDlg 对话框

class CAddDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDataDlg)

public:
	CAddDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddDataDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGraphic* m_gra;
	//CColumnchart m_columnChart;

	vector<CString> GetRGBValue(CString strSource);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAddPicPath();
	afx_msg void OnBnClickedColorButton();
	virtual BOOL OnInitDialog();
};
