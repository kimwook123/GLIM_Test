
// MFC_Study_appDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIM_Test_Dlg.h"
#include "GLIM_Test.h"
#include "afxdialogex.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

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
	m_pDlgImage = nullptr;
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
	m_pDlgImage = new CDlgImage(this);
	if (!m_pDlgImage->Create(IDD_CDlgImage, this) || m_pDlgImage->m_image.IsNull())
	{
		AfxMessageBox(_T("이미지 창을 만들 수 없습니다."));
		delete m_pDlgImage;
		m_pDlgImage = nullptr;
		EndDialog(IDCANCEL);
		return TRUE;
	}
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

void CGLIMTestDlg::DrawCircle(int radius, unsigned char* pixels)
{
    const int width = m_pDlgImage->m_image.GetWidth();
    const int height = m_pDlgImage->m_image.GetHeight();
    const int pitch = m_pDlgImage->m_image.GetPitch();

    // CImage 행 간격에는 정렬용 여백이 있을 수 있고, 상하 방향에 따라 음수일 수 있습니다.
    for (int y = 0; y < height; ++y)
        memset(pixels + y * pitch, 0xff, width);

    // 원 전체가 이미지 안에 들어가도록 중심을 선택합니다.
    const int centerX = radius + rand() % (width - 2 * radius);
    const int centerY = radius + rand() % (height - 2 * radius);
    const int thickness = 2;
    const int inner = (radius - thickness) * (radius - thickness);
    const int outer = radius * radius;

    for (int y = centerY - radius; y <= centerY + radius; ++y)
    {
        for (int x = centerX - radius; x <= centerX + radius; ++x)
        {
            if (x < 0 || y < 0 || x >= width || y >= height)
                continue;
            const int dx = x - centerX;
            const int dy = y - centerY;
            const int distance2 = dx * dx + dy * dy;
            if (distance2 >= inner && distance2 <= outer)
                pixels[y * pitch + x] = 0;
        }
    }
    TRACE(_T("radius: %d, actual center: (%d, %d)\n"), radius, centerX, centerY);
}

void CGLIMTestDlg::OnBnClickedSetButton()
{
    if (!m_pDlgImage || m_pDlgImage->m_image.IsNull())
        return;

    BOOL valid = FALSE;
    const UINT input = GetDlgItemInt(IDC_EDIT_RADIUS, &valid, FALSE);
    const int maxRadius = (std::min)(m_pDlgImage->m_image.GetWidth(),
                                     m_pDlgImage->m_image.GetHeight()) / 2 - 1;
    if (!valid || input < 2 || input > static_cast<UINT>(maxRadius))
    {
        CString message;
        message.Format(_T("반지름을 2~%d 사이의 정수로 입력하세요."), maxRadius);
        AfxMessageBox(message);
        GetDlgItem(IDC_EDIT_RADIUS)->SetFocus();
        return;
    }

    auto* pixels = static_cast<unsigned char*>(m_pDlgImage->m_image.GetBits());
    if (!pixels)
        return;
    DrawCircle(static_cast<int>(input), pixels);

    CPoint center;
    if (!FindCenter(pixels, center))
    {
        AfxMessageBox(_T("원의 중심을 계산할 수 없습니다."));
        return;
    }

    CString value;
    value.Format(_T("%d"), center.x);
    findCenter_x.ResetContent();
    findCenter_x.AddString(value);
    value.Format(_T("%d"), center.y);
    findCenter_y.ResetContent();
    findCenter_y.AddString(value);

    m_pDlgImage->SetOverlay(center, static_cast<int>(input));
}

bool CGLIMTestDlg::FindCenter(const unsigned char* pixels, CPoint& center) const
{
    const int width = m_pDlgImage->m_image.GetWidth();
    const int height = m_pDlgImage->m_image.GetHeight();
    const int pitch = m_pDlgImage->m_image.GetPitch();
    long long sumX = 0;
    long long sumY = 0;
    long long count = 0;
    for (int y = 0; y < height; ++y)
    {
        const unsigned char* row = pixels + y * pitch;
        for (int x = 0; x < width; ++x)
        {
            if (row[x] == 0xff)
                continue;
            sumX += x;
            sumY += y;
            ++count;
        }
    }
    if (count == 0)
        return false;
    center = CPoint(static_cast<int>((sumX + count / 2) / count),
                    static_cast<int>((sumY + count / 2) / count));
    TRACE(_T("pixel count: %lld, detected center: (%d, %d)\n"), count, center.x, center.y);
    return true;
}

void CGLIMTestDlg::OnDestroy()
{
    CDialogEx::OnDestroy();
    delete m_pDlgImage;
    m_pDlgImage = nullptr;
}
