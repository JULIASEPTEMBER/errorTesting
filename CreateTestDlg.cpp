// CreateTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestErrorStream.h"
#include "CreateTestDlg.h"
#include "afxdialogex.h"
#include "AnalyzeItem.h"
#include "BasicOperation.h"


// CCreateTestDlg 对话框
CAnalyzeItem m_AnalyzeItem;
#define MAX_CAPABLE   100000
BYTE Global_buf[MAX_CAPABLE];

IMPLEMENT_DYNAMIC(CCreateTestDlg, CDialogEx)


	CCreateTestDlg::CCreateTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCreateTestDlg::IDD, pParent)
{

}

CCreateTestDlg::~CCreateTestDlg()
{
}

void CCreateTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ERRORNAME, m_Edit_Name);
	DDX_Control(pDX, IDC_EDIT_TYPE, m_Edit_Type);
	DDX_Control(pDX, IDC_EDIT_PORT_IN, m_Edit_Port_In);
	DDX_Control(pDX, IDC_EDIT_PORT_OUT, m_Edit_PortOut);
	DDX_Control(pDX, IDC_EDIT_OUT, m_Edit_Out);
}


BEGIN_MESSAGE_MAP(CCreateTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PUSH, &CCreateTestDlg::OnBnClickedButtonPush)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CCreateTestDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_PUSH2, &CCreateTestDlg::OnBnClickedButtonPush2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCreateTestDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CCreateTestDlg::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CCreateTestDlg 消息处理程序


void CCreateTestDlg::OnBnClickedButtonPush()
{
	using namespace Operation;
	static LinklistHead* pRemTail;
	if(pRemTail == 0)
		pRemTail = (LinklistHead*)Global_buf;
	WCHAR *wc;
	UINT nLen;
	LinklistHead* pGet;


	//////////////////////////////////////////////////////////////////////////////////seek for the name space 
	nLen = m_Edit_Name.GetWindowTextLengthW();
	wc = new WCHAR [nLen + 1];
	m_Edit_Name.GetWindowTextW(wc, nLen + 1);

	pGet = m_AnalyzeItem.SearchBuffer((LinklistHead*)Global_buf, (BYTE*)wc, sizeof(WCHAR) * ( nLen + 1 ), NAME_TYPE);
	if(pGet)
	{
		pGet = m_AnalyzeItem.SeekTailOfCurrent(pGet);
	}
	else
	{
		pRemTail = m_AnalyzeItem.InsertItem(pRemTail, (BYTE*)wc, (1 + nLen) * sizeof(WCHAR));
		m_AnalyzeItem.SetCurrentItemType(pRemTail, NAME_TYPE);
		pGet = pRemTail;

	}
	delete wc;
	//////////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////output the formulation of analyzing 
	LinklistHead* pInput;
	nLen = m_Edit_Port_In.GetWindowTextLengthW();
	if(nLen)
	{
		wc = new WCHAR[nLen + 1];
		m_Edit_Port_In.GetWindowTextW(wc, nLen + 1);

		pInput = m_AnalyzeItem.InsertItem(pGet, (BYTE*)wc, (1 + nLen) * sizeof(WCHAR));
		m_AnalyzeItem.SetCurrentItemType(pInput, INPUT_TYPE);

		if(pGet == pRemTail)
		{
			pRemTail = pInput;
			pGet = pRemTail;
		}
	delete wc;
	}

	

	//////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////output the formulation of analyzing 
	nLen = m_Edit_PortOut.GetWindowTextLengthW();
	if(nLen)
	{
		wc = new WCHAR[nLen + 1];
		m_Edit_PortOut.GetWindowTextW(wc, nLen + 1);

		pInput = m_AnalyzeItem.InsertItem(pGet, (BYTE*)wc, (1 + nLen) * sizeof(WCHAR));
		m_AnalyzeItem.SetCurrentItemType(pInput, OUTPUT_TYPE);

		if(pGet == pRemTail)
		{
			pRemTail = pInput;
			pGet = pRemTail;
		}
	delete wc;
	}
	//////////////////////////////////////////////////////////////////////////////////





	//CEdit m_Edit_Name;
	//CEdit m_Edit_Type;
	//CEdit m_Edit_Port_In;
	//CEdit m_Edit_PortOut; 

	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::OnBnClickedButtonRemove()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::OnBnClickedButtonPush2()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CCreateTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_AnalyzeItem.Create(Global_buf, MAX_CAPABLE);
	m_AnalyzeItem.EnableOutput(&m_Edit_Out);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CCreateTestDlg::Create()
{
	CDialog::Create(CCreateTestDlg::IDD);

	ShowWindow(SW_SHOW);
}


void CCreateTestDlg::OnBnClickedButtonSave()
{ 
	m_AnalyzeItem.SaveInPath(L"want\This\LinklistBuf.lt");
	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::OnBnClickedButtonRead()
{ 
	m_AnalyzeItem.readInPath(L"want\This\LinklistBuf.lt");
	// TODO: 在此添加控件通知处理程序代码
}
