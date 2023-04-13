#pragma once
class CChatRoomDlg;
DWORD WINAPI ListenThreadFunc(LPVOID pParam);
DWORD WINAPI ClientThreadProc(LPVOID IpParameter);
DWORD WINAPI ConnectThreadFunc(LPVOID pParam);
BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut=100,BOOL bRead=false);

class CClientItem{
public:
	CString m_strIp;
	SOCKET m_Socket;
	CString m_username;
	HANDLE hThread;
	CChatRoomDlg *m_pMainWnd;
	CClientItem(){
		m_pMainWnd=NULL;
		m_Socket=INVALID_SOCKET;
		hThread=NULL;
	}
};