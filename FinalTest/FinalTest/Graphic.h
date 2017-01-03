#pragma once
#include <iostream>
#include <vector>
using namespace std;
class CGraphic
{
public:

	//ͼ����ص���Ϣ
	CString csTitle;
	typedef struct Data{
		CString csName;
		double csValue;
		CString csPath;
		int iR;
		int iG;
		int iB;
		CRect rect;
		int penWidth;
		int rValue;//����ѡ���ǵ���ɫ
	} chartData;
	Data paintData;
	vector<Data> dataVec;

	int selectItem;//�ж���List��ѡ�е�����һ��
	//��ȡ���ھ��
	HWND hwnd_dataList;
	HWND hwnd_dataForm;

	//CString bc_title;
	//vector<CString> bc_name;
	//vector<double> bc_valueX;
	//��ͼ��RGB��ֵ
	//vector<int>bc_r;
	//vector<int>bc_g;
	//vector<int>bc_b;

	//����λͼ
	HBITMAP bc_hImage;
	vector<HBITMAP> bc_hImageVec;
	vector<BITMAP> bc_imageVec;
	vector<CPoint> bc_picPos;

	RECT bc_rect;

	CDC bc_memDC;

	virtual void Init();
	virtual void Draw(CDC* pDC);
	virtual HBITMAP loadPic(CString picName);

	void ReleaseVector();
	void GetClientWH(CDC* hwnd);
	void GetMemCDC(CDC* pDC);
	int GetScWidth(CDC* pDC);
	int GetScHeight(CDC* pDC);

	CGraphic();
	~CGraphic();
};

