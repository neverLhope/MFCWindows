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
	//�����ڴ�����ʱ��λͼ
	CBitmap bitmap;
	//��������DC���������ڴ�DC
	bc_memDC.CreateCompatibleDC(pDC); 
	//��������λͼ(������pDC���������򻭳���ͼ�α�ɺ�ɫ)
	bitmap.CreateCompatibleBitmap(pDC, scWidth, scHeight);
	//��λͼѡ����ڴ�DC
	bc_memDC.SelectObject(&bitmap);
	//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
	bc_memDC.FillSolidRect(bc_rect.left, bc_rect.left, scWidth, scHeight, pDC->GetBkColor());

	bitmap.DeleteObject(); //ɾ��λͼ

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
