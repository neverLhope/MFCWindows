#include "stdafx.h"
#include "Columnchart.h"
#include "conio.h"
#include "FinalTest.h"


CColumnchart::CColumnchart()
{
}

CColumnchart::~CColumnchart()
{

}


void CColumnchart::Init()
{

}

void CColumnchart::Draw(CDC* pDC)
{
	//Init();
	double scWidth, scHeight;
	scWidth = GetScWidth(pDC);
	scHeight = GetScHeight(pDC);

	GetMemCDC(pDC);

	SetAxis(scWidth, scHeight);
	bc_memDC.TextOut(scWidth / 2 - 30, scHeight / 15, csTitle);
	//确定坐标scale != 0,如果等于0画出来的图形是负方向的
	double maxValue = GetMaxValue();
	int scale, scaleTemp;
	if (maxValue > 11)
	{
		scaleTemp = maxValue / 11;//坐标中每一份代表的大小
		scale = GetScale(scaleTemp);
		if (scaleTemp - scale > 10)
			scale = scale + 100;
		else
			scale = scale + 4;
	}
	else{
		scale = maxValue;
	}

	CPen pen(PS_DASH, 1, RGB(0, 0, 0));
	bc_memDC.SelectObject(&pen);

	SetAxisPoint(scWidth, scHeight, scale);

	//画柱子以及图案
	int heightScale = scHeight * 5 / (8 * dataVec.size() * 2);//平均每一个柱子的宽度
	if (heightScale > 30){
		heightScale = 30;
	}
	double coStartX, coStartY, coEndX, coEndY;

	coStartX = scWidth * 2 / 9;
	coStartY = scHeight * 19 / 24 - heightScale;

	CDC tempDC;
	tempDC.CreateCompatibleDC(pDC);

	CString num;
	int i;
	for (i = 0; i < dataVec.size(); i++)
	{
		//设置画刷
		CBrush brush(RGB(dataVec[i].iR, dataVec[i].iG, dataVec[i].iB));
		CPen pen(PS_SOLID, dataVec[i].penWidth, RGB(dataVec[i].rValue,0,0));
		//bc_memDC.SelectObject(&brush);
		

		//设置要绘制的矩形的区域
		coEndX = coStartX + (dataVec[i].csValue / scale)*scWidth / 20;
		coEndY = coStartY + heightScale;
		CRect columnRect(coStartX, coStartY, coEndX, coEndY);
		//存储图形的矩形区域
		dataVec[i].rect = columnRect;
		//绘制矩形边框
		bc_memDC.FillRect(columnRect, &brush);
		bc_memDC.SelectObject(&pen);
		SetRectEdge(columnRect);

		SetName(i, coStartX, coEndY);

		tempDC.SelectObject(bc_hImageVec[i]);
		tempDC.SetBkColor(RGB(0, 0, 0));
		bc_memDC.BitBlt(scWidth * 2 / 9 + (dataVec[i].csValue / scale)*scWidth / 20, coStartY + heightScale - 20,
			bc_imageVec[i].bmWidth, bc_imageVec[i].bmHeight, &tempDC, 0, 0, SRCCOPY);
		//重置开始点x坐标
		coStartY = coEndY - 3 * heightScale;

		DeleteObject(brush);
		DeleteObject(pen);
	}

	pDC->BitBlt(0, 0, scWidth, scHeight, &bc_memDC, 0, 0, SRCCOPY);//将内存DC上的图象拷贝到前台
	//ReleaseVector();
	tempDC.DeleteDC();
	bc_memDC.DeleteDC();     //删除DC
	DeleteObject(pen);

	ReleaseVector();
}

void CColumnchart::SetAxis(double width, double height)
{
	//坐标轴
	bc_memDC.MoveTo(width * 2 / 9, height / 8);
	bc_memDC.LineTo(width * 2 / 9, height * 5 / 6 + 30);
	bc_memDC.MoveTo(width * 2 / 9 - 30, height * 5 / 6);
	bc_memDC.LineTo(width * 5 / 6, height * 5 / 6);
	bc_memDC.TextOut(width * 2 / 9 - 10, height * 5 / 6 + 3, L"0");
}

void CColumnchart::SetAxisPoint(double width, double height, int scale)
{
	CString num;
	int i;
	for (i = 0; i < 12; i++)
	{
		bc_memDC.MoveTo(width * 2 / 9 + (i + 1)*width / 20, height * 5 / 6);
		bc_memDC.LineTo(width * 2 / 9 + (i + 1)*width / 20, height / 8);

		num.Format(L"%d", (i + 1)*scale);
		bc_memDC.TextOut(width * 2 / 9 + (i + 1)*width / 20 - 8, height * 5 / 6 + 6, num);
	}
}

void CColumnchart::SetName(int index, double posX, double posY)
{
	//设置名字
	bc_memDC.TextOut(posX - 50, posY - 17, dataVec[index].csName);
}

void CColumnchart::SetNum(int index, double posX, double posY)
{
	//设置数值
	CString csNum;
	csNum.Format(L"%.2f", dataVec[index].csValue);
	bc_memDC.TextOut(posX + bc_imageVec[index].bmWidth, posY - 17, csNum);
}

double CColumnchart::GetMaxValue()
{
	//AllocConsole();
	double max = 0;
	int i;
	for (i = 0; i < dataVec.size(); i++)
	{
		if (dataVec[i].csValue > max)
		{
			max = dataVec[i].csValue;
		}
	}
	//_cprintf("%.f", max);
	//FreeConsole();
	return max;
}

HBITMAP CColumnchart::loadPic(CString picName)
{
	//DeleteObject(m_hImage);
	BITMAP image;
	HBITMAP bitImage = (HBITMAP)LoadImage(::AfxGetInstanceHandle(), picName, IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	GetObject(bitImage, sizeof(BITMAP), &image);

	bc_imageVec.push_back(image);
	return bitImage;
}

int CColumnchart::GetScale(double scale)
{
	//转成末位为0的整数
	int flg = 0;
	int temp;
	while (true)
	{
		temp = scale;
		if (temp % 10 == temp)
			break;
		scale = scale / 10;
		flg++;
	}
	int i;
	for (i = 0; i < flg; i++)
		temp *= 10;
	return temp;
}


void CColumnchart::SetRectEdge(CRect rect)
{
	bc_memDC.MoveTo(rect.left, rect.top);
	bc_memDC.LineTo(rect.right, rect.top);

	bc_memDC.MoveTo(rect.left, rect.top);
	bc_memDC.LineTo(rect.left, rect.bottom);

	bc_memDC.MoveTo(rect.left, rect.bottom);
	bc_memDC.LineTo(rect.right, rect.bottom);
	
	bc_memDC.MoveTo(rect.right, rect.bottom);
	bc_memDC.LineTo(rect.right, rect.top);
}
