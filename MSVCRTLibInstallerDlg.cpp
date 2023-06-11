
// MSVCRTLibInstallerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MSVCRTLibInstaller.h"
#include "MSVCRTLibInstallerDlg.h"
#include "afxdialogex.h"

#include "MsiManager.h"

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


// CMSVCRTLibInstallerDlg 대화 상자



CMSVCRTLibInstallerDlg::CMSVCRTLibInstallerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MSVCRTLIBINSTALLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMSVCRTLibInstallerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_CHECK1, m_btnVc2015);
	DDX_Control(pDX, IDC_CHECK4, m_btnVc2013);
	DDX_Control(pDX, IDC_CHECK3, m_btnVc2012);
	DDX_Control(pDX, IDC_CHECK2, m_btnVc2010);
	DDX_Control(pDX, IDC_CHECK5, m_btnVc2008);
	DDX_Control(pDX, IDC_CHECK6, m_btnVc2005);
}

BEGIN_MESSAGE_MAP(CMSVCRTLibInstallerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMSVCRTLibInstallerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMSVCRTLibInstallerDlg 메시지 처리기

BOOL CMSVCRTLibInstallerDlg::OnInitDialog()
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

void CMSVCRTLibInstallerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMSVCRTLibInstallerDlg::OnPaint()
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
HCURSOR CMSVCRTLibInstallerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
 * 설치 해야할 전체 갯수를 가져오는 기능.
 * 
 * \return - 설치해야하는 인스톨 갯수
 */
int CMSVCRTLibInstallerDlg::GetInstallCount()
{
	int nCount = 0;

	if (m_btnVc2015.GetCheck() == BST_CHECKED) nCount++;
	if (m_btnVc2013.GetCheck() == BST_CHECKED) nCount++;
	if (m_btnVc2012.GetCheck() == BST_CHECKED) nCount++;
	if (m_btnVc2010.GetCheck() == BST_CHECKED) nCount++;
	if (m_btnVc2008.GetCheck() == BST_CHECKED) nCount++;
	if (m_btnVc2005.GetCheck() == BST_CHECKED) nCount++;

	return nCount;
}

void CMSVCRTLibInstallerDlg::InstallAll()
{
	int nCountInstall = GetInstallCount();

	// VS2005
	m_Vc2005.SetInstallURLx86(L"https://download.microsoft.com/download/1/E/4/1E4D029E-1D34-4CA8-B269-2CFEB91BD066/vcredist_x86.EXE");
	m_Vc2005.SetInstallURLx64(L"https://download.microsoft.com/download/1/E/4/1E4D029E-1D34-4CA8-B269-2CFEB91BD066/vcredist_x64.EXE");
	m_Vc2005.SetArguments(static_cast<int>(eInstallType::eQuiet));

	// VS2008
	m_Vc2008.SetInstallURLx86(L"https://download.microsoft.com/download/5/D/8/5D8C65CB-C849-4025-8E95-C3966CAFD8AE/vcredist_x86.exe");
	m_Vc2008.SetInstallURLx64(L"https://download.microsoft.com/download/5/D/8/5D8C65CB-C849-4025-8E95-C3966CAFD8AE/vcredist_x64.exe");
	m_Vc2008.SetArguments(static_cast<int>(eInstallType::eQuiet));


	// VS2010
	m_Vc2010.SetInstallURLx86(L"https://download.microsoft.com/download/1/6/5/165255E7-1014-4D0A-B094-B6A430A6BFFC/vcredist_x86.exe");
	m_Vc2010.SetInstallURLx64(L"https://download.microsoft.com/download/1/6/5/165255E7-1014-4D0A-B094-B6A430A6BFFC/vcredist_x64.exe");
	m_Vc2010.SetArguments(
		static_cast<int>(eInstallType::eQuiet) |
		static_cast<int>(eInstallType::eNoRestart)
	);

	// VS2012
	m_Vc2012.SetInstallURLx86(L"https://download.microsoft.com/download/1/6/B/16B06F60-3B20-4FF2-B699-5E9B7962F9AE/VSU_4/vcredist_x86.exe");
	m_Vc2012.SetInstallURLx64(L"https://download.microsoft.com/download/1/6/B/16B06F60-3B20-4FF2-B699-5E9B7962F9AE/VSU_4/vcredist_x64.exe");
	m_Vc2012.SetArguments(
		static_cast<int>(eInstallType::eInstall) |
		static_cast<int>(eInstallType::eQuiet) |
		static_cast<int>(eInstallType::eNoRestart)
	);

	// VS2013
	m_Vc2013.SetInstallURLx86(L"https://aka.ms/highdpimfc2013x86enu");
	m_Vc2013.SetInstallURLx64(L"https://aka.ms/highdpimfc2013x64enu");
	m_Vc2013.SetArguments(
		static_cast<int>(eInstallType::eInstall) |
		static_cast<int>(eInstallType::eQuiet) |
		static_cast<int>(eInstallType::eNoRestart)
	);

	// VS2015
	m_Vc2015.SetInstallURLx86(L"https://aka.ms/vs/17/release/vc_redist.x86.exe");
	m_Vc2015.SetInstallURLx64(L"https://aka.ms/vs/17/release/vc_redist.x64.exe");
	m_Vc2015.SetArguments(
		static_cast<int>(eInstallType::eInstall) |
		static_cast<int>(eInstallType::eQuiet) |
		static_cast<int>(eInstallType::eNoRestart)
	);


	Install(&m_btnVc2005, &m_Vc2005);
	Install(&m_btnVc2008, &m_Vc2008);
	Install(&m_btnVc2010, &m_Vc2010);
	Install(&m_btnVc2012, &m_Vc2012);
	Install(&m_btnVc2013, &m_Vc2013);
	Install(&m_btnVc2015, &m_Vc2015);

}

BOOL CMSVCRTLibInstallerDlg::Install(CButton* pButton, IMSVCVersion * inst)
{
	

	BOOL  bResult = FALSE;

	if (pButton->GetCheck() == BST_CHECKED)
	{
		bResult = inst->Install();
	}

	return bResult;
}



void CMSVCRTLibInstallerDlg::OnBnClickedButton1()
{
	InstallAll();
}
