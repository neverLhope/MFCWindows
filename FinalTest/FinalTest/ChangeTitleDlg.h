#pragma once

#include "Columnchart.h"
// CChangeTitleDlg �Ի���

class CChangeTitleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeTitleDlg)

public:
	CChangeTitleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeTitleDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CGraphic* m_gra;
	//CColumnchart m_columnChart;
	afx_msg void OnBnClickedOk();
};
