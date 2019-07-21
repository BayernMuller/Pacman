
// PacView.cpp : CPacView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Pac.h"
#endif

#include "PacDoc.h"
#include "PacView.h"

#include "PacMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

UINT DrawThread(void* p);

// CPacView

IMPLEMENT_DYNCREATE(CPacView, CView)

BEGIN_MESSAGE_MAP(CPacView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(UM_GAMEOVER, &CPacView::OnGameOver)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPacView ����/�Ҹ�

CPacView::CPacView() : m_pMap(nullptr), m_bFlag(true), m_pThread(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CPacView::~CPacView()
{
	
}

BOOL CPacView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CPacView �׸���

void CPacView::OnDraw(CDC* pDC)
{
	CPacDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CDC MemDC;
	CRect rect;
	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);

	if (m_pMap)
		m_pMap->Draw(&MemDC);	

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();	
}


// CPacView �μ�

BOOL CPacView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CPacView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CPacView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CPacView ����

#ifdef _DEBUG
void CPacView::AssertValid() const
{
	CView::AssertValid();
}

void CPacView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPacDoc* CPacView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPacDoc)));
	return (CPacDoc*)m_pDocument;
}
#endif //_DEBUG


// CPacView �޽��� ó����


void CPacView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_pThread = new thread(DrawThread, this);
	m_pMap = new CPacMap(m_hWnd);
	
}


void CPacView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_pMap)
	{
		m_pMap->OnKeyDown(nChar);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CPacView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

UINT DrawThread(void* p)
{
	CPacView* pView = (CPacView*)p;
	while (pView->m_bFlag)
	{
		pView->Invalidate(0);
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	return 0;
}

void CPacView::OnDestroy()
{
	CView::OnDestroy();

	m_bFlag = false;
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}
	delete m_pMap;
}

LRESULT CPacView::OnGameOver(WPARAM wParam, LPARAM lParam)
{
	delete m_pMap;
	m_pMap = new CPacMap(m_hWnd);
	return LRESULT();
}
