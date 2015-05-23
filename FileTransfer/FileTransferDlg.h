// FileTransferDlg.h : 头文件
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// CFileTransferDlg 对话框
class CFileTransferDlg : public CDialog
{
// 构造
public:
	CSocket m_sock, m_sock2;
	CString strFileSaveName;
	int quite;

	struct FILE_NAME{
	DWORD nFileSize;
	char cFileName[256];
	}fileInfo;

	CFileTransferDlg(CWnd* pParent = NULL);	// 标准构造函数
	void OnClose();

// 对话框数据
	enum { IDD = IDD_FILETRANSFER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonsent();
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonTest();
	CButton mButtonTest;
	afx_msg void OnBnClickedButtonSave();
	CProgressCtrl mProgressSave;
	afx_msg void OnBnClickedCancel();
};
