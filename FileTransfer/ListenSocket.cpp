#include "StdAfx.h"
#include "ListenSocket.h"

CListenSocket::CListenSocket(void)
{
}

CListenSocket::~CListenSocket(void)
{
}

void CListenSocket::OnAccept(int nErrorCode)
{
	CClientSocket *tmp = new CClientSocket(&CCSL);
	Accept(*tmp);
	CCSL.Add(tmp);
	CSocket::OnAccept(nErrorCode);
}