
// GLIMTestDlgDlg.h: 헤더 파일
//
#pragma once
#include "CDlgImage.h"


// GLIMTestDlgDlg 대화 상자
class CGLIMTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CGLIMTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_STUDY_APP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetButton();
	void DrawCircle(int nRadius, unsigned char* fm);
	bool FindCenter(const unsigned char* pixels, CPoint& center) const;
	afx_msg void OnDestroy();
	CListBox findCenter_x;
	CListBox findCenter_y;
};
