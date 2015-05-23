#pragma once
#include "afxsock.h"

#include "ClientSocketList.h"

class CListenSocket :
	public CSocket
{
public:
	CClientSocketList CCSL;
	CListenSocket(void);
	virtual ~CListenSocket(void);

public:
	virtual void OnAccept(int nErrorCode);
};
