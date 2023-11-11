
// MFC_Study_appDlg.h: 헤더 파일
//

#pragma once


// CMFCStudyappDlg 대화 상자
class CMFCStudyappDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validImagePos(int x, int y);
// 생성입니다.
public:
	CMFCStudyappDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

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
	afx_msg void OnBnClickedBtnImg();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void moveRect();
	afx_msg void OnBnClickedBtnAct();
	void DrawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	BOOL isInCircle(int i,int j,int nCenterX,int nCenterY,int nRadius);
};
