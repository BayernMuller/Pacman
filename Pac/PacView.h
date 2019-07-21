
// PacView.h : CPacView Ŭ������ �������̽�
//

#pragma once
class CPacMap;
#include <thread>

class CPacView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPacView();
	DECLARE_DYNCREATE(CPacView)
private:
	CPacMap* m_pMap;
	std::thread* m_pThread;
// Ư���Դϴ�.
public:
	CPacDoc* GetDocument() const;
	bool m_bFlag;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CPacView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnGameOver(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // PacView.cpp�� ����� ����
inline CPacDoc* CPacView::GetDocument() const
   { return reinterpret_cast<CPacDoc*>(m_pDocument); }
#endif

