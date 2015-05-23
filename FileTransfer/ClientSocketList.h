#pragma once

class CClientSocketList
{
public:
	BOOL Sends(CClientSocket *);
	BOOL Add(CClientSocket *);
	CClientSocket * Head;
	CClientSocketList(void);
	virtual ~CClientSocketList(void);
};
