#pragma once
#include "afxdialogex.h"


// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_image;
	void SetOverlay(CPoint center, int radius);
private:
    void DrawOverlay(CDC& dc) const;
    CPoint m_overlayCenter{ 0, 0 };
    int m_overlayRadius = 0;
    bool m_hasOverlay = false;
public:

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void InitImage();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
