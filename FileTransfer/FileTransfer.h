// FileTransfer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileTransferApp:
// �йش����ʵ�֣������ FileTransfer.cpp
//

class CFileTransferApp : public CWinApp
{
public:
	CFileTransferApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileTransferApp theApp;