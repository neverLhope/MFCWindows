#pragma once
#include <iostream>
#include <vector>
using namespace std;
class CGraphic
{
public:

	//图标相关的信息
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
		int rValue;//设置选中是的颜色
	} chartData;
	Data paintData;
	vector<Data> dataVec;

	int selectItem;//判断在List中选中的是哪一个
	//获取窗口句柄
	HWND hwnd_dataList;
	HWND hwnd_dataForm;

	//CString bc_title;
	//vector<CString> bc_name;
	//vector<double> bc_valueX;
	//存图形RGB的值
	//vector<int>bc_r;
	//vector<int>bc_g;
	//vector<int>bc_b;

	//放置位图
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

