// ChatRoomDlg.h : header file
//

#if !defined(AFX_CHATROOMDLG_H__78500AF5_6FF0_4522_876F_6A9C5FB2DD9E__INCLUDED_)
#define AFX_CHATROOMDLG_H__78500AF5_6FF0_4522_876F_6A9C5FB2DD9E__INCLUDED_

#define IDD_CHATROOM_DIALOG             102
#include"Inc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatRoomDlg dialog

class CChatRoomDlg : public CDialog
{
// Construction
public:
	CChatRoomDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRoomDlg)
	enum { IDD = IDD_CHATROOM_DIALOG };
	CEdit	m_MsgEdit;
	CButton	m_stopServer;
	CButton	m_startServer;
	CButton	m_stopClient;
	CButton	m_sentMassage;
	CButton	m_connectClient;
	//}}AFX_DATA
	SOCKET m_ListenSock;
	HANDLE m_hListenThread;
	HANDLE m_hConnectThred;
	SOCKET m_ConnectSock;
	int m_bIsServer;
	bool bShutDown;
	CArray <CClientItem,CClientItem>m_ClientArray;
	void ShowMsg(CString strMsg);
	void RemoveClientFromArray(CClientItem in_Item);
	void SendClientsMsg(CString strMsg,CClientItem *pNotSend=NULL);
	void StopClient();
	void StopServer();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatRoomDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnChangeEdit5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMDLG_H__78500AF5_6FF0_4522_876F_6A9C5FB2DD9E__INCLUDED_)
