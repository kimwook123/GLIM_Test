// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Study_app.h"
#include "afxdialogex.h"
#include "CDlgImage.h"
#include "MFC_Study_appDlg.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent)
{
	m_pParent = pParent;
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
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(10, 0, 600, 300);
	InitImage();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
	{
		m_image.Draw(dc, 0, 0);
	}

	drawData(&dc);
}

void CDlgImage::InitImage()
{
	int nWidth = 600;
	int nHeight = 350;
	int nBpp = 8;

	if (m_image != NULL)
	{
		m_image.Destroy();
	}

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb); // 흑백처리
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 번째 포인터를 가져온다.

	memset(fm, 0xff, nWidth * nHeight); // 사이즈를 지정하여 이미지를 조절할 수 있다. memset 쓸 때 m_image.Create 부분의 nHeight를 -로 바꿔주면 된다. 
}

void CDlgImage::drawData(CDC* pDC)
{
	CRect rect(0, 0, 100, 100);
	CPen pen;
	CBrush brush;

	brush.CreateStockObject(NULL_BRUSH);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	pen.CreatePen(PS_SOLID, 5, RGB(0xff, 0xff, 0x00));
	CPen* pOldPen = pDC->SelectObject(&pen);

	for (int i = 0; i < m_nDataCount; i++)
	{
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(5, 10);
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);
}