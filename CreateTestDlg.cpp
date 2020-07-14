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
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CCreateTestDlg::OnBnClickedButtonRun)
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



	//////////////////////////////////////////////////////////////////////////////////input the formulation of analyzing 
	LinklistHead* pInput;
	BYTE *btTrans = 0;
	UINT nGetTrans;
	nLen = m_Edit_Port_In.GetWindowTextLengthW();
	wc = 0;
	if(nLen)
	{
		wc  = new WCHAR[nLen + 1];
		m_Edit_Port_In.GetWindowTextW(wc, nLen + 1);
		

		CString cs, csOutput;
		btTrans = new BYTE[nLen / 2];
		if(CBasicOperation::TransformToHex(wc, btTrans, nGetTrans))
		{
			for(int i = 0; i < nGetTrans; i ++)
			{
				if(btTrans[i] < 16)
					csOutput += L"0";
				cs.Format(L"%x", btTrans[i]);
				csOutput += cs;
				
			}
				nLen = csOutput.GetLength();
				wcscpy(wc, csOutput);
		}
		if(btTrans)
		delete btTrans;
		pInput = m_AnalyzeItem.InsertItem(pGet, (BYTE*)wc, (1 + nLen) * sizeof(WCHAR));
		m_AnalyzeItem.SetCurrentItemType(pInput, INPUT_TYPE);

		if(pGet == pRemTail)
		{
			pRemTail = pInput;
			pGet = pRemTail;
		}
		if(wc)
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
	CString cs, csot;
	for(int i = '0' ; i < 'z'; i ++)
	{
		cs.Format(L"-%c, %x\r\n", i, i); csot += cs;
	}
	m_Edit_Out.SetWindowTextW(csot);
	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::OnBnClickedButtonRead()
{ 
	m_AnalyzeItem.readInPath(L"want\This\LinklistBuf.lt");
	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::OnBnClickedButtonRun()
{
	CString cs = L"aa   01   ff ea FF ";
	UINT nLen = cs.GetLength();
	BYTE bt[100];
	CBasicOperation::TransformToHex(cs, bt, nLen);
	CString csGo;
	csGo.Format(L"%x, %x, %x",0xff, 0xaa, 0xbb);
	MessageBox(csGo);
	// TODO: 在此添加控件通知处理程序代码
}


void CCreateTestDlg::CheckInfo_SendBack(BYTE *bt, UINT nLen)
{
	using namespace Operation;
	static BYTE Save[1000];
	static UINT nSaveLen, flag, nGetLen;
	CString csOutput, cs;
	WCHAR wcOutput[1000];
	LinklistHead* pGet, *pParBr;
	BYTE btOutput[1000];
	UINT nLenOutput = 0;

	for(int i = 0 ;i < nLen; i ++)
	{
		switch(flag)
		{
		case 0:
			flag = bt[i] == 0xaa ? 1 : 0;
			break;
		case 1:
			flag = bt[i] == 0x55 ? 2 : 0;
			break;
		case 2:
			flag = 3;
			nSaveLen = 0;
			nGetLen = bt[i];
			break;
		case 3:
			if(bt[i] < 16)csOutput += L"0";
			cs.Format(L"%x", bt[i]); csOutput += cs;
			Save[nSaveLen] = bt[i];
			nSaveLen ++;
			if(nSaveLen == nGetLen)
			{
				flag = 4;
			}
			break; 
		case 4:
			if(bt[i] == 0x0d)
			{
				wcscpy(wcOutput, csOutput);
				pGet = m_AnalyzeItem.SearchBuffer((LinklistHead*)Global_buf, (BYTE*)wcOutput, csOutput.GetLength() * sizeof(WCHAR), INPUT_TYPE);
				if(pGet)
				{
					if(m_AnalyzeItem.GetNearHeadBrench(pGet, &pParBr))
					{
						cs = (WCHAR*)(pParBr + 1);
						//MessageBox(cs);
						if(pGet->next && pGet->next->type == OUTPUT_TYPE)
						{
							pGet = pGet->next;
							cs = (WCHAR*)(pGet + 1);
							//MessageBox(cs);
							if(CBasicOperation::TransformToHex(cs, btOutput, nLenOutput))
							{
								OUTPUT_SENDMSG_COM ot;
								ot.nType =  MSG_SEND;
								ot.nLen = nLenOutput;
								ot.buffer = btOutput;
								Funname((int*)&ot);
							}
						}
					}
				}
			}
			flag = 0;
			break;
		}
	}

}


int CALLBACK CCreateTestDlg::ExchangeData(int hhv, PLCIDECALLBACK pFC, void *pParam)//
{

Funname = pFC;                     // 
return 0;
}
