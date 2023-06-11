
// MSVCRTLibInstallerDlg.h: 헤더 파일
//

#pragma once
#include <string>
#include "IMSVCVersion.h"
#include "MSVC2005.h"
#include "MSVC2008.h"
#include "MSVC2010.h"
#include "MSVC2012.h"
#include "MSVC2013.h"
#include "MSVC2015.h"

// CMSVCRTLibInstallerDlg 대화 상자
class CMSVCRTLibInstallerDlg : public CDialogEx
{
// 생성입니다.
public:
	CMSVCRTLibInstallerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSVCRTLIBINSTALLER_DIALOG };
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

private:
	int GetInstallCount();
	void InstallAll();
	BOOL Install(CButton* pButton, IMSVCVersion* inst);

public:
	CProgressCtrl m_progress;
	afx_msg void OnBnClickedButton1();
	CButton m_btnVc2015;
	CButton m_btnVc2013;
	CButton m_btnVc2012;
	CButton m_btnVc2010;
	CButton m_btnVc2008;
	CButton m_btnVc2005;


	CMSVC2015 m_Vc2015;
	CMSVC2013 m_Vc2013;
	CMSVC2012 m_Vc2012;
	CMSVC2010 m_Vc2010;
	CMSVC2008 m_Vc2008;
	CMSVC2005 m_Vc2005;


};
