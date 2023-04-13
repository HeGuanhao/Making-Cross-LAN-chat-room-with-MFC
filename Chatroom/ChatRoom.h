// ChatRoom.h : main header file for the CHATROOM application
//

#if !defined(AFX_CHATROOM_H__7A9D4488_D726_4CD5_A19D_7B0D92B16A44__INCLUDED_)
#define AFX_CHATROOM_H__7A9D4488_D726_4CD5_A19D_7B0D92B16A44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatRoomApp:
// See ChatRoom.cpp for the implementation of this class
//

class CChatRoomApp : public CWinApp
{
public:
	CChatRoomApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRoomApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatRoomApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOM_H__7A9D4488_D726_4CD5_A19D_7B0D92B16A44__INCLUDED_)
