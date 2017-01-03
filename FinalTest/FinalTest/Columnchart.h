#pragma once
#include "Graphic.h"
class CColumnchart :
	public CGraphic
{
public:

	double GetMaxValue();
	int GetScale(double scale);
	void SetAxis(double width, double height);
	void SetAxisPoint(double width, double height, int scale);
	void SetName(int index, double posX, double posY);
	void SetNum(int index, double posX, double posY);

	void Init();
	void Draw(CDC* pDC);
	HBITMAP loadPic(CString picName);

	CColumnchart();
	~CColumnchart();
	void SetRectEdge(CRect rect);
};

