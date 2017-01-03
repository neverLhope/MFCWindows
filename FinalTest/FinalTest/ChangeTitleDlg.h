#pragma once

#include "Columnchart.h"
// CChangeTitleDlg 对话框

class CChangeTitleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeTitleDlg)

public:
	CChangeTitleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeTitleDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CGraphic* m_gra;
	//CColumnchart m_columnChart;
	afx_msg void OnBnClickedOk();
};
