// FormDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalTest.h"
#include "FormDoc.h"

#include "AddDataForm.h"


// CFormDoc

IMPLEMENT_DYNCREATE(CFormDoc, CDocument)

CFormDoc::CFormDoc()
{
	doc_csTitle = "title";
}

BOOL CFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CFormDoc::~CFormDoc()
{
}


BEGIN_MESSAGE_MAP(CFormDoc, CDocument)
END_MESSAGE_MAP()


// CFormDoc ���

#ifdef _DEBUG
void CFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CFormDoc ���л�

void CFormDoc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	CAddDataForm* pAddData = (CAddDataForm*)GetNextView(pos);
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
		/*ar << doc_csTitle;*/
		ar << pAddData->m_csTitle;
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
		/*ar >> doc_csTitle;*/
		CString csT;
		ar >> csT;
	}
}
#endif


// CFormDoc ����
