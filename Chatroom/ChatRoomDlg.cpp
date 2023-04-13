// ChatRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include"Inc.h"
#include"Resource.h"

#define MAX_BUF_SIZE 1024

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRoomDlg dialog

CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatRoomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ListenSock=INVALID_SOCKET;
	m_ConnectSock=INVALID_SOCKET;
	m_hListenThread=NULL;
	m_hConnectThred=NULL;
	m_bIsServer=-1;
	bShutDown=false;
	//{{AFX_DATA_INIT(CChatRoomDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatRoomDlg)
	DDX_Control(pDX, IDC_EDIT4, m_MsgEdit);
	DDX_Control(pDX, IDC_BUTTON5, m_stopServer);
	DDX_Control(pDX, IDC_BUTTON4, m_startServer);
	DDX_Control(pDX, IDC_BUTTON3, m_stopClient);
	DDX_Control(pDX, IDC_BUTTON2, m_sentMassage);
	DDX_Control(pDX, IDC_BUTTON1, m_connectClient);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CChatRoomDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRoomDlg message handlers

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,TEXT("可爱的小何"));
	SetDlgItemText(IDC_EDIT2,TEXT("106.55.161.177"));
	SetDlgItemText(IDC_EDIT3,TEXT("8889"));
	SetDlgItemText(IDC_EDIT6,TEXT("8889"));
	m_stopClient.EnableWindow(false);
	m_sentMassage.EnableWindow(false);
	m_stopServer.EnableWindow(false);
	ShowMsg(_T("程序启动成功！"));
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatRoomDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CChatRoomDlg::ShowMsg(CString strMsg)
{
	m_MsgEdit.SetSel(-1,-1);
	m_MsgEdit.ReplaceSel(strMsg+_T("\r\n"));
}

void CChatRoomDlg::RemoveClientFromArray(CClientItem in_Item)
{
	for(int idx=0;idx<m_ClientArray.GetSize();idx++){
		CClientItem tItem=m_ClientArray.GetAt(idx);
		if(tItem.m_Socket==in_Item.m_Socket&&
			tItem.hThread==in_Item.hThread&&
			tItem.m_strIp==in_Item.m_strIp){
			m_ClientArray.RemoveAt(idx);
		}
	}
}

void CChatRoomDlg::SendClientsMsg(CString strMsg,CClientItem *pNotSend){
	TCHAR szBuf[MAX_BUF_SIZE]={0};
	strcpy(szBuf,strMsg);
	for(INT_PTR idx=0;idx<m_ClientArray.GetSize();idx++){
		if(!pNotSend||pNotSend->m_Socket!=m_ClientArray.GetAt(idx).m_Socket||
			pNotSend->m_strIp!=m_ClientArray.GetAt(idx).m_strIp||
			pNotSend->hThread!=m_ClientArray.GetAt(idx).hThread){
			send(m_ClientArray.GetAt(idx).m_Socket,(char *)szBuf,_tcslen(szBuf)*sizeof(TCHAR),0);
		}
	}
}

void CChatRoomDlg::StopClient(){
	bShutDown=true;
	DWORD dwRet=WaitForSingleObject(m_hConnectThred,1000);
	if(dwRet!=WAIT_OBJECT_0){
		TerminateThread(m_hConnectThred,-1);
		closesocket(m_ConnectSock);
	}
	m_hConnectThred=NULL;
	m_ConnectSock=INVALID_SOCKET;
	m_bIsServer=-1;
	bShutDown=false;
}

void CChatRoomDlg::StopServer(){
	UINT nCount =m_ClientArray.GetSize();
	HANDLE *m_pHandles=new HANDLE[nCount+1];
	m_pHandles[0]=m_hListenThread;
	for(int idx=0;idx < nCount;idx++){
		m_pHandles[idx+1]=m_ClientArray.GetAt(idx).hThread;
	}
	bShutDown=true;
	DWORD dwRet=WaitForMultipleObjects(nCount+1,m_pHandles,true,1000);
	if(dwRet!=WAIT_OBJECT_0){
		for(INT_PTR i=0;i<m_ClientArray.GetSize();i++){
			TerminateThread(m_ClientArray.GetAt(i).hThread,-1);
		closesocket(m_ClientArray.GetAt(i).m_Socket);
	}
	TerminateThread(m_hListenThread,-1);
		closesocket(m_ListenSock);
	}
	delete[] m_pHandles;
	m_hListenThread=NULL;
	m_ListenSock=INVALID_SOCKET;
	m_bIsServer=-1;
	bShutDown=true;
}



void CChatRoomDlg::OnButton1() 
{
		m_stopClient.EnableWindow(true);
	m_sentMassage.EnableWindow(true);
	m_connectClient.EnableWindow(false);
	m_hConnectThred=CreateThread(NULL,0,ConnectThreadFunc,this,0,NULL);
}

void CChatRoomDlg::OnButton2() 
{
		CString strMsg2;
	CString strMsg1;
	CString strMsg;
	GetDlgItemText(IDC_EDIT5,strMsg2);

	if(m_bIsServer==true){
		strMsg=_T("服务器： >")+strMsg2;
		ShowMsg(strMsg);
		SendClientsMsg(strMsg);
	}
	else if(m_bIsServer==false){
		GetDlgItemText(IDC_EDIT1,strMsg1);
		CString strTmp=strMsg1+_T("客户端：>")+strMsg2;
		ShowMsg(strTmp);
		int iSend=send(m_ConnectSock,(char*)strMsg2.GetBuffer(0),strMsg2.GetLength()*sizeof(TCHAR),0);
		SendClientsMsg(strTmp);
		strMsg.ReleaseBuffer();
	}
	SetDlgItemText(IDC_EDIT5,_T(""));
}

void CChatRoomDlg::OnButton3() 
{
		m_stopClient.EnableWindow(false);
	m_sentMassage.EnableWindow(false);
	m_connectClient.EnableWindow(true);
	StopClient();
	ShowMsg(_T("停止客户端成功！"));
}

void CChatRoomDlg::OnButton4() 
{
	m_stopServer.EnableWindow(true);
	m_startServer.EnableWindow(false);
	m_sentMassage.EnableWindow(true);
	m_hListenThread=CreateThread(NULL,0,ListenThreadFunc,this,0,NULL);
	
}

void CChatRoomDlg::OnButton5() 
{
	m_stopServer.EnableWindow(false);
	m_startServer.EnableWindow(true);
	StopServer();
	ShowMsg(_T("停止服务器端成功！"));
	
}


void CChatRoomDlg::OnChangeEdit5() 
{
		CString strMsg;
	GetDlgItemText(IDC_EDIT5,strMsg);
	if(strMsg.IsEmpty()){
		m_sentMassage.EnableWindow(false);
	}else{
	m_sentMassage.EnableWindow(true);
	}
	
}
