
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "PaSchulteGrid2018MFC2010.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	PA_DoInitMatrix();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);
	int w = rect.right;
	int h = rect.bottom;
	int m_nCellW = (w > h ? h : w) / 6;
	int m_nStartX = (w - m_nCellW * 5) / 2;
	int m_nStartY = (h - m_nCellW * 5) / 2;
	int m_nGridW = m_nCellW * 5;

	int m_nFontSizePt = m_nCellW * 4;
	int m_nFontOffsetY = m_nCellW / 10;
	int m_nFontOffsetX1 = m_nCellW / 10 * 3;
	int m_nFontOffsetX2 = m_nCellW / 10;

	m_fontText.CreatePointFont(m_nFontSizePt, _T("Arial Black"), RGB(0, 0, 0));

	CFont* m_pOldFont = dc.SelectObject(&m_fontText);

	int m_nOffsetX = m_nStartX;
	int m_nOffsetY = m_nStartY;
	for(int i = 0; i < 6; i++){
		if(i<5){
			for(int j = 0; j < 5; j++){
				int n = j * 5 + i;
				int m_nFontOffsetX = A_nMatrix[n] < 10 ? m_nFontOffsetX1 : m_nFontOffsetX2;
				int m_nFontOfssetY1 = m_nStartY + m_nCellW * j + m_nFontOffsetY;
				dc.TextOutW(m_nOffsetX + m_nFontOffsetX, m_nFontOfssetY1, A_strMatrix[n]);
			}
		}
		dc.MoveTo(m_nStartX, m_nOffsetY);
		dc.LineTo(m_nStartX + m_nGridW, m_nOffsetY);

		dc.MoveTo(m_nOffsetX, m_nStartY);
		dc.LineTo(m_nOffsetX, m_nStartY + m_nGridW);


		m_nOffsetX += m_nCellW;
		m_nOffsetY += m_nCellW;
	}

	dc.SelectObject(m_pOldFont);

	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::PA_DoInitMatrix(void)
{
	int A_nSource[25][2];

	srand(time(NULL));

	for(int i = 0; i < 25; i++){
		A_nSource[i][0] = A_nSource[i][1] = i + 1;
	}

	int current = 0;
	int prev = 25 - 1;
	A_nSource[prev][1] = current;
	for(int i = 0; i < 25; i++){
		int r = rand() % (25 - i);
		for(int n = 0; n < r; n++){
			prev = current;
			current = A_nSource[current][1];
		}
		A_nMatrix[i] = A_nSource[current][0];
		A_strMatrix[i].Format(_T("%d"), A_nMatrix[i]);

		A_nSource[prev][1] = A_nSource[current][1];
		A_nSource[current][1] = -1;
		current = A_nSource[prev][1];
	}
}
