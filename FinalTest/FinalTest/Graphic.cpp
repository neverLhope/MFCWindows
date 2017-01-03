#include "stdafx.h"
#include "Graphic.h"


CGraphic::CGraphic()
{
}


CGraphic::~CGraphic()
{
}

void CGraphic::Init()
{

}

void CGraphic::Draw(CDC* pDC)
{

}

void CGraphic::GetClientWH(CDC* hwnd)
{
	hwnd->GetWindow()->GetClientRect(&bc_rect);
}

void CGraphic::GetMemCDC(CDC* pDC)
{
	int scWidth, scHeight;
	scWidth = GetScWidth(pDC);
	scHeight = GetScHeight(pDC);
	//承载内存中临时的位图
	CBitmap bitmap;
	//依附窗口DC创建兼容内存DC
	bc_memDC.CreateCompatibleDC(pDC); 
	//创建兼容位图(必须用pDC创建，否则画出的图形变成黑色)
	bitmap.CreateCompatibleBitmap(pDC, scWidth, scHeight);
	//将位图选择进内存DC
	bc_memDC.SelectObject(&bitmap);
	//按原来背景填充客户区，不然会是黑色
	bc_memDC.FillSolidRect(bc_rect.left, bc_rect.left, scWidth, scHeight, pDC->GetBkColor());

	bitmap.DeleteObject(); //删除位图

}

int CGraphic::GetScWidth(CDC* pDC)
{
	GetClientWH(pDC);
	return (bc_rect.right - bc_rect.left);
}

int CGraphic::GetScHeight(CDC* pDC)
{
	GetClientWH(pDC);
	return (bc_rect.bottom - bc_rect.top);
}

void CGraphic::ReleaseVector()
{
	bc_imageVec.clear();
	bc_hImageVec.clear();
}

HBITMAP CGraphic::loadPic(CString picName)
{
	return NULL;
}
