// FormDoc.cpp : 实现文件
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


// CFormDoc 诊断

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
// CFormDoc 序列化

void CFormDoc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	CAddDataForm* pAddData = (CAddDataForm*)GetNextView(pos);
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		/*ar << doc_csTitle;*/
		ar << pAddData->m_csTitle;
	}
	else
	{
		// TODO:  在此添加加载代码
		/*ar >> doc_csTitle;*/
		CString csT;
		ar >> csT;
	}
}
#endif


// CFormDoc 命令
