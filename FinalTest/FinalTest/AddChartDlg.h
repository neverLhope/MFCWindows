#pragma once

#include "Columnchart.h"
// CAddChartDlg �Ի���

class CAddChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddChartDlg)

public:
	CAddChartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddChartDlg();

// �Ի�������
	enum { IDD = IDD_ADD_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//ͼ�����
	CString m_csTitle;
	//��ɫ
	CString m_csColor;
	//����Ƿ�����������ɫ�İ�ť
	bool m_flgClickSure;
	//����Ƿ�����������ɫ�İ�ť
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
