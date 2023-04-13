#include"stdafx.h"
#include"ChatRoomDlg.h"
#include"Inc.h"
#include"Resource.h"
#define MAX_BUF_SIZE 1024
#include <AtlConv.h>
#include <afxpriv.h>
#include <atlbase.h>
#include "windows.h"
#include<string.h>


DWORD WINAPI ConnectThreadFunc(LPVOID pParam){
		CChatRoomDlg *pChatRoom=(CChatRoomDlg *)pParam;
	ASSERT(pChatRoom!=NULL);
	pChatRoom->m_ConnectSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(pChatRoom->m_ConnectSock==INVALID_SOCKET){
		AfxMessageBox(_T("�½�Socketʧ�ܣ�"));
		return false;
	}
	CString strServIp;
	pChatRoom->GetDlgItemText(IDC_EDIT2,strServIp);
	int iPort=pChatRoom->GetDlgItemInt(IDC_EDIT3);
	if(iPort<=0||iPort>65535){
		AfxMessageBox(_T("�˿ڷǷ�"));
		closesocket(pChatRoom->m_ConnectSock);
		return true;
	}
	char szIpAddr[16]={0};
	USES_CONVERSION;
	strcpy(szIpAddr,strServIp.GetBuffer(strServIp.GetLength()));

	sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(szIpAddr);
	server.sin_port=htons(iPort);
	if(connect(pChatRoom->m_ConnectSock,(struct sockaddr*)&server,sizeof(struct sockaddr))==SOCKET_ERROR){
		AfxMessageBox(_T("����ʧ�ܣ������ԣ�"));
		closesocket(pChatRoom->m_ConnectSock);
		return true;
	}
	pChatRoom->m_bIsServer=false;

	pChatRoom->ShowMsg(_T("ϵͳ��Ϣ�����ӷ������ɹ���"));

	while(true&&!(pChatRoom->bShutDown)){
		if(SOCKET_Select(pChatRoom->m_ConnectSock)){
			TCHAR szBuf[MAX_BUF_SIZE]={0};
			int iRet=recv(pChatRoom->m_ConnectSock,(char*)szBuf,MAX_BUF_SIZE,0);
			if(iRet>0){
				pChatRoom->ShowMsg(szBuf);
			}
			else{
				pChatRoom->ShowMsg(_T("�����ҷ�����ֹͣ�����������ӣ�"));
				break;
			}
		}
		Sleep(500);
	}
closesocket(pChatRoom->m_ConnectSock);
		return true;
}
