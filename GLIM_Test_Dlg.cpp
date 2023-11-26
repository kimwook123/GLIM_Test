
// MFC_Study_appDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIM_Test_Dlg.h"
#include "GLIM_Test.h"
#include "afxdialogex.h"

#include <math.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") // 콘솔창 띄우기.

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCStudyappDlg 대화 상자

CGLIMTestDlg::CGLIMTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_STUDY_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, findCenter_x);
	DDX_Control(pDX, IDC_LIST2, findCenter_y);
}

BEGIN_MESSAGE_MAP(CGLIMTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SET_BUTTON, &CGLIMTestDlg::OnBnClickedSetButton)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGLIMTestDlg 메시지 처리기

BOOL CGLIMTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	int Width = 800;
	int Height = 440;
	MoveWindow(0, 0, Width, Height);
	m_pDlgImage = new CDlgImage; // 자식 클래스에 이미지를 생성하기 위한 객체 생성
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(10, 0, 600, 350);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGLIMTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGLIMTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGLIMTestDlg::DrawCircle(int nRadius, unsigned char* fm) // 원 그리는 함수
{
	int nWidth  = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch  = m_pDlgImage->m_image.GetPitch();

	memset(fm, 0xff, nWidth * nHeight); // 그릴 때마다 도화지 초기화하기

	int nSttX = rand() % nWidth;
	int nSttY = rand() % nHeight;

	if (nSttX + (nRadius * 2) > nWidth)
		nSttX = nSttX - (nSttX + (nRadius * 2) - nWidth);
	if (nSttY + (nRadius * 2) > nHeight)
		nSttY = nSttY - (nSttY + (nRadius * 2) - nHeight);

	TRACE("nRadius: %d, (%d, %d)\n", nRadius, nSttX, nSttY);

	for (int j = nSttY; j < nSttY + nRadius * 2; j++)
	{
		for (int i = nSttX; i < nSttX + nRadius * 2; i++)
		{
			if (isInCircle(i, j, nSttX + nRadius, nSttY + nRadius, nRadius))
				fm[j * nPitch + i] = 0x00;
		}
	}

	CClientDC dc(m_pDlgImage);
	m_pDlgImage->m_image.Draw(dc, 0, 0);
}

BOOL CGLIMTestDlg::isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX    = x - nCenterX+0.5;
	double dY    = y - nCenterY+0.5;
	double dDist = dX * dX + dY * dY;

	if ((nRadius * nRadius) - (nRadius * 3) < dDist && dDist < (nRadius * nRadius) + nRadius)
	{
		bRet = true;
	}

	return bRet;
}

void CGLIMTestDlg::OnBnClickedSetButton()
{
	int nRadius = GetDlgItemInt(IDC_STATIC);
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();

	if (nRadius > m_pDlgImage->m_image.GetHeight())
	{
		CString msg;
		msg.Format(_T("%d보다 작은 값을 입력하세요."), m_pDlgImage->m_image.GetHeight());
		AfxMessageBox(msg);
		return;
	}

	DrawCircle(nRadius, fm);
	CPoint ptCenter = findCenter(fm);
	drawCross(ptCenter, nRadius);
	drawYellowCircle(ptCenter, nRadius);
}

CPoint CGLIMTestDlg::findCenter(unsigned char* fm)
{
	int nWidth  = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch  = m_pDlgImage->m_image.GetPitch();

	CRect rect(0, 0, nWidth, nHeight);
	int nSumX  = 0; // x 좌표 수
	int nSumY  = 0; // t 좌표 수
	int nCount = 0; // 총 좌표 개수

	int nCenterX = 0;
	int nCenterY = 0;

	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] != 0xff)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	if (nCount == 0) // 분모가 0일 경우, 예외 처리
	{
		AfxMessageBox(_T("Count Error detected!!"));
		nCenterX = nCenterY = 0;
	}
	else
	{
		nCenterX = nSumX / nCount;
		nCenterY = nSumY / nCount;
	}

	// findCenter_x에 대한 처리
	findCenter_x.ResetContent();  // 리스트 초기화

	CString centerXText;
	centerXText.Format(_T("%d"), nCenterX);
	findCenter_x.AddString(centerXText);

	// findCenter_y에 대한 처리
	findCenter_y.ResetContent();  // 리스트 초기화

	CString centerYText;
	centerYText.Format(_T("%d"), nCenterY);
	findCenter_y.AddString(centerYText);

	TRACE("sum : (%d, %d)\tcount: %d\tcenter: (%d, %d)\n", nSumX, nSumY, nCount, nCenterX, nCenterY);
	return CPoint(nCenterX, nCenterY);
}

void CGLIMTestDlg::drawCross(CPoint ptCenter, int size) // 중심에 십자가 그리는 함수
{
	CClientDC dc(m_pDlgImage);

	int nCenterX = ptCenter.x;
	int nCenterY = ptCenter.y;

	int nLineLength = size / 10;

	if (nLineLength < 5)
	{
		nLineLength = 5;
	}

	dc.MoveTo(nCenterX - nLineLength, nCenterY);
	dc.LineTo(nCenterX + nLineLength + 1, nCenterY);

	dc.MoveTo(nCenterX, nCenterY - nLineLength);
	dc.LineTo(nCenterX, nCenterY + nLineLength + 1);
}

void CGLIMTestDlg::drawYellowCircle(CPoint ptCenter, int size) // 원 외곽에 노란 표시선 그리는 함수
{
	CClientDC dc(m_pDlgImage);

	CBrush brush;
	brush.CreateStockObject(NULL_BRUSH);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0xff, 0xff, 0x00));
	CPen* pOldPen = dc.SelectObject(&pen);

	int nSpace = 10;
	dc.Ellipse(ptCenter.x - size - nSpace, ptCenter.y - size - nSpace,
		       ptCenter.x + size + nSpace, ptCenter.y + size + nSpace);

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldPen);
}

void CGLIMTestDlg::OnDestroy() // new delete
{
	CDialogEx::OnDestroy();

	delete m_pDlgImage;
	m_pDlgImage = nullptr;
}
