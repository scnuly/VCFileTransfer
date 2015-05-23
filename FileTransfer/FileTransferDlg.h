// FileTransferDlg.h : ͷ�ļ�
//
#pragma once
#include "afxwin.h"
#include "afxcmn.h"



// CFileTransferDlg �Ի���
class CFileTransferDlg : public CDialog
{
// ����
public:
	CSocket m_sock, m_sock2;
	CString strFileSaveName;
	int quite;

	struct FILE_NAME{
	DWORD nFileSize;
	char cFileName[256];
	}fileInfo;

	CFileTransferDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void OnClose();

// �Ի�������
	enum { IDD = IDD_FILETRANSFER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
