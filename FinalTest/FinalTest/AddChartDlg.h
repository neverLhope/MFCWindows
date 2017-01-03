#pragma once

#include "Columnchart.h"
// CAddChartDlg 对话框

class CAddChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddChartDlg)

public:
	CAddChartDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddChartDlg();

// 对话框数据
	enum { IDD = IDD_ADD_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//图表标题
	CString m_csTitle;
	//颜色
	CString m_csColor;
	//标记是否点击了设置颜色的按钮
	bool m_flgClickSure;
	//标记是否点击了设置颜色的按钮
	bool m_flgColor;

	CGraphic* m_gra;
	//CColumnchart m_columnChart;

	afx_msg void OnBnClickedAddPicPath();
	afx_msg void OnBnClickedColorButton();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void SetEditContent();
	void SetEditContent(int item);
	vector<CString> GetRGBValue(CString strSource);
	void UpdateViews();
	virtual BOOL OnInitDialog();
};
