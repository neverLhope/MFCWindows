#pragma once

#include "Columnchart.h"
// CChangeDlg �Ի���

class CChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeDlg)

public:
	CChangeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeDlg();

// �Ի�������
	enum { IDD = IDD_CHANGE_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
