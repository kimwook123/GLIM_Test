
// GLIMTestDlgDlg.h: 헤더 파일
//
#include "CDlgImage.h"

#pragma once


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
	void drawCross(CPoint ptCenter, int size);
	void drawYellowCircle(CPoint ptCenter, int size);

	CPoint findCenter(unsigned char* fm);
	BOOL isInCircle(int i,int j,int nCenterX,int nCenterY,int nRadius);
	int Circle_size_set;
	afx_msg void OnDestroy();
	CListBox findCenter_x;
	CListBox findCenter_y;
};
