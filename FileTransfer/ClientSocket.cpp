#include "StdAfx.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CClientSocket::CClientSocket(CClientSocketList *tmp)
{
	Front = 0;
	Next = 0;
	List = tmp;
}

CClientSocket::~CClientSocket(void)
{
}

void CClientSocket::OnReceive(int nErrorCode)
{
	List->Sends(this);
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);
}
