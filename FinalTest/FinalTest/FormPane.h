#pragma once

#include "AddDataForm.h"

// CFormPane

class CFormPane : public CDockablePane
{
	DECLARE_DYNAMIC(CFormPane)

public:
	//ÃÌº”±‰¡ø
	CAddDataForm* m_addDataForm;

	CFormPane();
	virtual ~CFormPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


