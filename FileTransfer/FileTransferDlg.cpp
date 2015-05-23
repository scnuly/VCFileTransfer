// FileTransferDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileTransfer.h"
#include "FileTransferDlg.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT Thread_Server(LPVOID lpParam);

CEvent hEvent;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFileTransferDlg 对话框




CFileTransferDlg::CFileTransferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileTransferDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_TEST, mButtonTest);
	DDX_Control(pDX, IDC_PROGRESS1, mProgressSave);
}

BEGIN_MESSAGE_MAP(CFileTransferDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONSENT, &CFileTransferDlg::OnBnClickedButtonsent)
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CFileTransferDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CFileTransferDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFileTransferDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDCANCEL, &CFileTransferDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CFileTransferDlg 消息处理程序

BOOL CFileTransferDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	mProgressSave.SetPos(0);
	CWinThread *pThread = AfxBeginThread(Thread_Server, this);
	quite = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileTransferDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileTransferDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileTransferDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFileTransferDlg::OnBnClickedButtonsent()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(_T("Test1"));
}

void CFileTransferDlg::OnBnClickedButtonopen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE, NULL, NULL, 4, _T("Image Files (*.jpg)|*.jpg|All Files (*.*)|*.*||"), NULL);
	
	if(dlgFile.DoModal())
	{
		
	}
}

void CFileTransferDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	//mButtonTest.EnableWindow(FALSE);

	//CWinThread *pThread = AfxBeginThread(Thread_Server, this);

	//mButtonTest.EnableWindow(TRUE);
}

UINT Thread_Server(LPVOID lpParam)
{
	CFileTransferDlg *dlg = (CFileTransferDlg *)lpParam;
	CSocket Serversock;
	CSocket Clientsock;

	if(!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
	}

	//CFile logErrorfile;
	//if(!logErrorfile.Open(_T("d:/log_error.txt"), CFile::modeCreate|CFile::modeReadWrite))
	//{
	//	return 0;
	//}

	//create
	if(!Serversock.Create(6348))
	{
		CString str;
		str.Format(_T("socket create failed: %d"), GetLastError());
		AfxMessageBox(str);
	}

	//listen
	if(!Serversock.Listen(10))
	{
		CString str;
		str.Format(_T("socket listen failed: %d"), GetLastError());
		AfxMessageBox(str);
	}

	while(1)
	{
		if(Serversock.Accept(Clientsock))
		{
			if(dlg->quite == 1)
			{
				Clientsock.Close();
				Serversock.Close();
				break;
			}
			//WIN32_FIND_DATA ffd;
			(dlg->GetDlgItem(IDC_BUTTON_TEST))->EnableWindow(FALSE);
			Clientsock.Receive(&(dlg->fileInfo), 4 + 256);
 
			wchar_t pwstr[256];
			//android device UTF8 to PC unicode
			MultiByteToWideChar(CP_UTF8, 0, dlg->fileInfo.cFileName, -1, pwstr, 128);
			//MultiByteToWideChar(CP_ACP, 0, dlg->fileInfo.cFileName, -1, pwstr, 20);
			CString receiveName;
			receiveName.Format(_T("%s"), pwstr);
			dlg->mProgressSave.SetRange(0, 100);

			(dlg->GetDlgItem(IDC_BUTTON_SAVE))->SetWindowTextW(receiveName);
			(dlg->GetDlgItem(IDC_BUTTON_SAVE))->EnableWindow(TRUE);
			WaitForSingleObject(hEvent.m_hObject, INFINITE);
			CloseHandle(hEvent);

			CFile file;
			file.Open(dlg->strFileSaveName, CFile::modeCreate|CFile::modeWrite);
			dlg->mProgressSave.SetPos(0);

			int flag = 0;
			Clientsock.Send(&flag, 4);

			UINT nSize = 0;
			UINT nData = 0;
			char szBuff[1024];
			
			while(nSize < dlg->fileInfo.nFileSize)
			{
				nData = Clientsock.Receive(szBuff, 1024);
				file.Write(szBuff, nData);
				nSize += nData;
				dlg->mProgressSave.SetPos(nSize * 100 / dlg->fileInfo.nFileSize);
			}
			dlg->mProgressSave.SetPos(100);

			Clientsock.Close();
			Serversock.Close();
			file.Close();

			AfxMessageBox(_T("File receive successful"));
			(dlg->GetDlgItem(IDC_BUTTON_SAVE))->SetWindowTextW(_T("接收文件"));
			(dlg->GetDlgItem(IDC_BUTTON_SAVE))->EnableWindow(FALSE);
			break;
		}
	}

	
	//(dlg->GetDlgItem(IDC_BUTTON_TEST))->EnableWindow(TRUE);
	return 0;
}

void CFileTransferDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY, _T("Descripbe Files (*.cfg)|*.cfg|All Files(*.*)|*.*||"), NULL);

	if(dlgFile.DoModal())
	{
		strFileSaveName = dlgFile.GetPathName();
	}

	hEvent.SetEvent();
	
}

void CFileTransferDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CFileTransferDlg::OnClose()
{
	CSocket socket;
	socket.Socket();
	quite = 1;
	socket.Connect(_T("127.0.0.1"), 6348);
	socket.Close();
	OnCancel();
}