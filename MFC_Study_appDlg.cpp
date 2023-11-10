
// MFC_Study_appDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_Study_app.h"
#include "MFC_Study_appDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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



CMFCStudyappDlg::CMFCStudyappDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_STUDY_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCStudyappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCStudyappDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMG, &CMFCStudyappDlg::OnBnClickedBtnImg)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMFCStudyappDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCStudyappDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACT, &CMFCStudyappDlg::OnBnClickedBtnAct)
END_MESSAGE_MAP()


// CMFCStudyappDlg 메시지 처리기

BOOL CMFCStudyappDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCStudyappDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCStudyappDlg::OnPaint()
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
HCURSOR CMFCStudyappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCStudyappDlg::OnBnClickedBtnImg()
{
	int nWidth = 640;
	int nHeight = 480;
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
			m_image.SetColorTable(0, 256, rgb); // 흑백처리
		}
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 번째 포인터를 가져온다.

	memset(fm, 0xff, nWidth*nHeight); // 사이즈를 지정하여 이미지를 조절할 수 있다. memset 쓸 때 m_image.Create 부분의 nHeight를 -로 바꿔주면 된다. 

	//for (int j = 0; j < nHeight; j++) // 세로 nHeight 수 만큼의 픽셀
	//{
	//	for (int i = 0; i < nWidth; i++) // 가로 nWidth 수 만큼의 픽셀
	//	{
	//		fm[j * nPitch + i] = j % 255; // 이미지 밝기값 조절, 모든 이미지 조절
	//	}
	//}

	//fm[12 * nPitch + 16] = 0; // 해당 픽셀 위치 칠하기 nHeight * nPitch + nWidth
	//fm[0 * nPitch + 0] = 128;
	//fm[0 * nPitch + 1] = 128;
	//for (int j = 0; j < nHeight / 2; j++)
	//{
	//	for (int i = 0; i < nWidth / 2; i++)
	//	{
	//		fm[j * nPitch + i] = 128;
	//	}
	//}

	UpdateDisplay();
	// 이미지를 그린다.
}

CString g_strFileImage = (_T("C:\\image\\save.bmp")); // 전역 변수로 선언한 것.
void CMFCStudyappDlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage); // 경로에 이미지 파일을 저장한다.
}


void CMFCStudyappDlg::OnBnClickedBtnLoad()
{
	if (m_image != NULL)
	{
		m_image.Destroy();
	}

	m_image.Load(g_strFileImage); // 경로의 이미지 파일을 가져온다.

	UpdateDisplay();
}

void CMFCStudyappDlg::UpdateDisplay() // 그냥 화면 업데이트 로직 따로 뺀 것.
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CMFCStudyappDlg::moveRect()
{
	static int nSttX = 0;
	static int nSttY = 0;

	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 번째 포인터를 가져온다.

	memset(fm, 0xff, nWidth * nHeight);

	for (int j = nSttY; j < nSttY+48;j++)
	{
		for (int i = nSttX; i < nSttX+64; i++)
		{
			if (validImagePos(i, j))
			{
				fm[j * nPitch + i] = nGray;
			}
		}
	}
	nSttX++;
	nSttY++;
	UpdateDisplay();
}

void CMFCStudyappDlg::OnBnClickedBtnAct()
{
	for (int i = 0; i < 100; i++)
	{
		moveRect();
		Sleep(10);
	}
}

BOOL CMFCStudyappDlg::validImagePos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}
