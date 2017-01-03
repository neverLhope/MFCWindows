#pragma once

#include "Columnchart.h"
// CChangeDlg 对话框

class CChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeDlg)

public:
	CChangeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeDlg();

// 对话框数据
	enum { IDD = IDD_CHANGE_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGraphic* m_gra;
	//CColumnchart m_columnChart;

	bool flg_DataChanged;

	afx_msg void OnBnClickedColorButton();
	afx_msg void OnBnClickedAddPicPath();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
