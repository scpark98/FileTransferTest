
// FileTransferTestDlg.h: 헤더 파일
//

#pragma once

#define RUN_SINGLE_MODE _T("[단일 PC에서 전송 테스트]\n\n")\
						_T("1.\"nFTDServer 실행\" 버튼 클릭하여 바로 테스트 가능.")

#define RUN_DUAL_MODE	_T("[다른 PC와의 전송 테스트]\n\n")\
						_T("1. 상대 PC의 임시 폴더에 배포된 파일들을 복사.\n")\
						_T("2. 상대 PC에서 이 테스트 프로그램 실행 후 \"nFTDClient 실행\" 버튼 클릭.\n")\
						_T("3. 메인 PC에서 \"상대 IP 주소\"란에 상대편 PC의 IP 주소 입력.\n")\
						_T("4. 메인 PC에서 \"상대 접속 번호\"란에 상대편 PC의 접속 번호 입력.\n")\
						_T("5. \"nFTDServer 실행\" 버튼 클릭.\n")\


// CFileTransferTestDlg 대화 상자
class CFileTransferTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CFileTransferTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CString		m_my_ip;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILETRANSFERTEST_DIALOG };
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
	afx_msg void OnBnClickedCheckSinglePC();
	CButton m_button_run_client;
	CButton m_button_run_server;
	CButton m_check_single_pc;
	afx_msg void OnBnClickedButtonRunClient();
	afx_msg void OnBnClickedButtonRunServer();
	CStatic m_static_guide;
	CEdit m_edit_my_ip;
	CEdit m_edit_target_ip;
	CEdit m_edit_my_ticket_num;
	CEdit m_edit_target_ticket_num;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
