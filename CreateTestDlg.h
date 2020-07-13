#pragma once
#include "afxwin.h"


// CCreateTestDlg 对话框
namespace Operation{
	static const UINT NAME_TYPE = 1, INPUT_TYPE = 2, OUTPUT_TYPE = 3;//folder relationship while the bigger one has lower priority 
};

class CCreateTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateTestDlg)

public:
	CCreateTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateTestDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TESTERROR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPush();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButtonPush2();
	CEdit m_Edit_Name;
	CEdit m_Edit_Type;
	CEdit m_Edit_Port_In;
	CEdit m_Edit_PortOut;
	

	virtual BOOL OnInitDialog();
	void Create();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonRead();
	CEdit m_Edit_Out;
};
