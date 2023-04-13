#include"stdafx.h"
#include"ChatRoomDlg.h"
#include"Resource.h"
#define MAX_BUF_SIZE 1024

BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket,&fdset);
	nTimeOut=nTimeOut>1000?1000:nTimeOut;
	tv.tv_sec =0;
    tv.tv_usec=nTimeOut;

	int iRet=0;
	if(bRead){
		iRet=select(0,&fdset,NULL,NULL,&tv);
	}else{
		iRet=select(0,NULL,&fdset,NULL,&tv);
	}

	if(iRet<=0){
		return false;
	}else if(FD_ISSET(hSocket,&fdset)){
		return true;
	}
	return false;
}

DWORD WINAPI ListenThreadFunc(LPVOID pParam)
{
	CChatRoomDlg *pChatRoom=(CChatRoomDlg *)pParam;
	ASSERT(pChatRoom!=NULL);
	pChatRoom->m_ListenSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(pChatRoom->m_ListenSock==INVALID_SOCKET){
		AfxMessageBox(_T("新建Socket失败！"));
		return false;
	}
	int iPort=pChatRoom->GetDlgItemInt(IDC_EDIT6);
	if(iPort<=0||iPort>65535){
		AfxMessageBox(_T("端口非法"));
		closesocket(pChatRoom->m_ListenSock);
	}
	sockaddr_in service;
	service.sin_family=AF_INET;
	service.sin_addr.s_addr=INADDR_ANY;
	service.sin_port=htons(iPort);
	if(bind(pChatRoom->m_ListenSock,(sockaddr*)&service,sizeof(sockaddr_in))==SOCKET_ERROR){
		AfxMessageBox(_T("绑定端口失败！"));
		closesocket(pChatRoom->m_ListenSock);
	}
	if(listen(pChatRoom->m_ListenSock,5)==SOCKET_ERROR){
		AfxMessageBox(_T("监听失败！"));
		closesocket(pChatRoom->m_ListenSock);
	}
	pChatRoom->m_bIsServer=true;

	while(true&&!(pChatRoom->bShutDown)){
		if(SOCKET_Select(pChatRoom->m_ListenSock,100,true)){
			sockaddr_in clientAddr;
	int iLen=sizeof(sockaddr_in);
	SOCKET accSock=accept(pChatRoom->m_ListenSock,(struct sockaddr*)&clientAddr,&iLen);
	if(accSock ==INVALID_SOCKET){
		continue;
	}
	CClientItem tItem;
	tItem.m_Socket=accSock;
	tItem.m_pMainWnd=pChatRoom;
	tItem.m_strIp=inet_ntoa(clientAddr.sin_addr);
	tItem.m_username=pChatRoom->GetDlgItemInt(IDC_EDIT1);

	INT_PTR idx=pChatRoom->m_ClientArray.Add(tItem);
	tItem.hThread=CreateThread(NULL,0,ClientThreadProc,&(pChatRoom->m_ClientArray.ElementAt(idx)),CREATE_SUSPENDED,NULL);
	pChatRoom->m_ClientArray.ElementAt(idx).hThread=tItem.hThread;
	ResumeThread(tItem.hThread);


	Sleep(100);
		}
	}
}

DWORD WINAPI ClientThreadProc(LPVOID IpParameter)
{
	CString strMsg;
	CClientItem m_ClientItem=*(CClientItem*)IpParameter;
	while(true){
		if(SOCKET_Select(m_ClientItem.m_Socket,100,true)){
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet=recv(m_ClientItem.m_Socket,(char*)szBuf,MAX_BUF_SIZE,0);
			if(iRet>0){
				strMsg=szBuf;
				strMsg=_T("客户端:")+m_ClientItem.m_strIp+_T(">")+strMsg;
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->SendClientsMsg(strMsg, &m_ClientItem);
			}
			else{
				strMsg=_T("客户端:")+m_ClientItem.m_strIp+_T("离开了聊天室！");
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->RemoveClientFromArray(m_ClientItem);
				break;
			}
		}Sleep(500);
	}
	return true;
}