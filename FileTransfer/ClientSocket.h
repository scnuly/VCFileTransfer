#pragma once
#include "afxsock.h"

class CClientSocketList;

class CClientSocket :
	public CSocket
{
public:
	CClientSocket(CClientSocketList *);
	virtual ~CClientSocket(void);

public:
	CClientSocketList *List;
	CClientSocket * Front;
	CClientSocket * Next;

public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

protected:
};
