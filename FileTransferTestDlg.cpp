
// FileTransferTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FileTransferTest.h"
#include "FileTransferTestDlg.h"
#include "afxdialogex.h"

#include <ws2tcpip.h>

#include "../../Common/Functions.h"

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


// CFileTransferTestDlg 대화 상자



CFileTransferTestDlg::CFileTransferTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILETRANSFERTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTransferTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_RUN_CLIENT, m_button_run_client);
	DDX_Control(pDX, IDC_BUTTON_RUN_SERVER, m_button_run_server);
	DDX_Control(pDX, IDC_CHECK_SINGLE_PC, m_check_single_pc);
	DDX_Control(pDX, IDC_STATIC_GUIDE, m_static_guide);
	DDX_Control(pDX, IDC_EDIT_MY_IP, m_edit_my_ip);
	DDX_Control(pDX, IDC_EDIT_TARGET_IP, m_edit_target_ip);
	DDX_Control(pDX, IDC_EDIT_MY_TICKET_NUM, m_edit_my_ticket_num);
	DDX_Control(pDX, IDC_EDIT_TARGET_TICKET_NUM, m_edit_target_ticket_num);
}

BEGIN_MESSAGE_MAP(CFileTransferTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_SINGLE_PC, &CFileTransferTestDlg::OnBnClickedCheckSinglePC)
	ON_BN_CLICKED(IDC_BUTTON_RUN_CLIENT, &CFileTransferTestDlg::OnBnClickedButtonRunClient)
	ON_BN_CLICKED(IDC_BUTTON_RUN_SERVER, &CFileTransferTestDlg::OnBnClickedButtonRunServer)
	ON_BN_CLICKED(IDOK, &CFileTransferTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileTransferTestDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFileTransferTestDlg 메시지 처리기

BOOL CFileTransferTestDlg::OnInitDialog()
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
	m_my_ip = get_my_ip();

	bool run_single_pc = theApp.GetProfileInt(_T("setting"), _T("run single pc"), true);
	m_check_single_pc.SetCheck(run_single_pc ? BST_CHECKED : BST_UNCHECKED);
	OnBnClickedCheckSinglePC();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFileTransferTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileTransferTestDlg::OnPaint()
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
HCURSOR CFileTransferTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileTransferTestDlg::OnBnClickedCheckSinglePC()
{
	int run_single_mode = m_check_single_pc.GetCheck();
	theApp.WriteProfileInt(_T("setting"), _T("run single pc"), run_single_mode);
	m_button_run_client.EnableWindow(run_single_mode != BST_CHECKED);
	m_static_guide.SetWindowText(run_single_mode ? RUN_SINGLE_MODE : RUN_DUAL_MODE);

	m_edit_my_ip.EnableWindow(run_single_mode != BST_CHECKED);
	m_edit_my_ticket_num.EnableWindow(run_single_mode != BST_CHECKED);
	m_edit_target_ip.EnableWindow(run_single_mode != BST_CHECKED);
	m_edit_target_ticket_num.EnableWindow(run_single_mode != BST_CHECKED);
}


void CFileTransferTestDlg::OnBnClickedButtonRunClient()
{
	CString path = get_exe_directory() + _T("\\nFTDClient.exe");

	if (get_process_running_count(path))
	{
		kill_process_by_fullpath(get_exe_directory() + _T("\\nFTDServer.exe"));
		kill_process_by_fullpath(path);
	}

	ShellExecute(NULL, _T("open"), path, _T("-l 443"), 0, SW_SHOWMINIMIZED);

	m_edit_my_ip.SetWindowText(m_my_ip);
	m_edit_my_ticket_num.SetWindowText(i2S(random19937(100000, 999999)));
}


void CFileTransferTestDlg::OnBnClickedButtonRunServer()
{
	CString path = get_exe_directory() + _T("\\nFTDServer.exe");

	if (get_process_running_count(path))
	{
		kill_process_by_fullpath(get_exe_directory() + _T("\\nFTDServer.exe"));
		kill_process_by_fullpath(path);
	}

	CString target_ip = get_my_ip();
	int ticket_num = random19937(100000, 999999);

	if (m_check_single_pc.GetCheck() == BST_CHECKED)
	{
		CString client_path = get_exe_directory() + _T("\\nFTDClient.exe");
		ShellExecute(NULL, _T("open"), client_path, _T("-l 443"), 0, SW_SHOWMINIMIZED);
	}
	else
	{
		m_edit_target_ip.GetWindowText(target_ip);
		target_ip.Trim();
		if (target_ip.IsEmpty())
			return;

		CString str;
		m_edit_target_ticket_num.GetWindowText(str);
		str.Trim();
		if (str.IsEmpty())
			return;

		ticket_num = _ttoi(str);
	}

	CString param;
	param.Format(_T("-c -viewermode -statisticsmode %s 443 %d C4BDE5622FFF865173239111 \"SCPARK-KOINO-LG\" \"apple\" 1 bdb4d55fbba98e29875f38018651492645520607 192.168.74.1 192.168.74.1 1"),
		target_ip,
		ticket_num);

	ShellExecute(NULL, _T("open"), path, param, 0, SW_SHOWNORMAL);
}


void CFileTransferTestDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CFileTransferTestDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
