
// FinalTestDoc.h : CFinalTestDoc ��Ľӿ�
//


#pragma once
#include "Columnchart.h"

class CFinalTestDoc : public CDocument
{
protected: // �������л�����
	CFinalTestDoc();
	DECLARE_DYNCREATE(CFinalTestDoc)

// ����
public:

	CString csTitle;
	bool doc_flgFormAdd;

	

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:

	
	virtual ~CFinalTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
