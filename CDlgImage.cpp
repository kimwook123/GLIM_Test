// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "GLIM_Test.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include "GLIM_Test_Dlg.h"
#include <algorithm>
#include <cstring>


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitImage();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (!m_image.IsNull())
	{
		m_image.Draw(dc, 0, 0);
		DrawOverlay(dc);
	}
}

void CDlgImage::InitImage()
{
	m_hasOverlay = false;
	int nWidth = 600;
	int nHeight = 350;
	int nBpp = 8;

	if (!m_image.IsNull())  // 겹침이 아니라 갱신을 위한 기존 이미지 제거
	{
		m_image.Destroy();
	}

	m_image.Create(nWidth, -nHeight, nBpp);
	if (m_image.IsNull())
		return;
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb); // 흑백처리
	}
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 번째 포인터를 가져온다.

	if (fm) // 유효성 검사
	{
		const int pitch = m_image.GetPitch();
		for (int y = 0; y < nHeight; ++y)
			memset(fm + y * pitch, 0xff, nWidth);
	}
}

void CDlgImage::SetOverlay(CPoint center, int radius)
{
    m_overlayCenter = center;
    m_overlayRadius = radius;
    m_hasOverlay = true;
    Invalidate(FALSE);
}

void CDlgImage::DrawOverlay(CDC& dc) const
{
    if (!m_hasOverlay)
        return;

    const int length = (std::max)(5, m_overlayRadius / 10);
    CPen crossPen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen* oldPen = dc.SelectObject(&crossPen);
    dc.MoveTo(m_overlayCenter.x - length, m_overlayCenter.y);
    dc.LineTo(m_overlayCenter.x + length + 1, m_overlayCenter.y);
    dc.MoveTo(m_overlayCenter.x, m_overlayCenter.y - length);
    dc.LineTo(m_overlayCenter.x, m_overlayCenter.y + length + 1);

    CPen circlePen(PS_SOLID, 3, RGB(255, 255, 0));
    dc.SelectObject(&circlePen);
    CBrush* oldBrush = static_cast<CBrush*>(dc.SelectStockObject(NULL_BRUSH));
    const int markedRadius = m_overlayRadius + 10;
    dc.Ellipse(m_overlayCenter.x - markedRadius, m_overlayCenter.y - markedRadius,
               m_overlayCenter.x + markedRadius + 1, m_overlayCenter.y + markedRadius + 1);
    dc.SelectObject(oldBrush);
    dc.SelectObject(oldPen);
}
