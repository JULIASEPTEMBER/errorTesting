#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlg_AnalyzeWave 对话框
struct st_Render
{
	RECT rt;//fill the figure
	UINT nFrom, nTo;
	float fXScale, fYScale;
	float fDisplaceX, fDisplaceY;
	UINT nMax, nMin, nMaxID, nMinID;

};

class CDlg_AnalyzeWave : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_AnalyzeWave)

public:
	CDlg_AnalyzeWave(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_AnalyzeWave();

	// 对话框数据
	enum { IDD = IDD_DIALOG_OUTPUT_WAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWantWave();
	CEdit m_HorDelta;
	CEdit m_Edit_VerDelta;
	CEdit m_Edit_XBegin;
	CEdit m_Edit_YBegin;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
	void Create(HWND hd);
	CSpinButtonCtrl m_SPin_horDel;
	CSpinButtonCtrl m_SPin_VerDel;
	CSpinButtonCtrl m_SPin_XBeg;
	CSpinButtonCtrl m_SPin_YBeg;
	void InsertDatas(int nHeight);//insert data to the series
	HWND out_hd;
	void SketchOutput();//output those buffer through a st_Render filter
	afx_msg void OnBnClickedButtonOutput();
	st_Render m_stRender;
	void GenerateStructRender();//change the struct other variable 
	CEdit m_Edit_Beg;
	CEdit m_Edit_End;
	afx_msg void OnBnClickedButtonClear();
	CEdit m_Edit_Left;
	CEdit m_Edit_Right;
	CEdit m_Edit_Top;
	CEdit m_Edit_Bottom;
	CButton m_Check_Coordinate;
	void SketchCoordinate(CPoint pt);
	int HeightInLine(CPoint* ptLine, int nHeight, CPoint* pt);//return the correct point while the pt pointer was not zero 
	void FillBufferInBitmap();//bitmap  output
	void OutputFigure(CDC* cdc);//output a figure 
	void OutputFigure_Particular(CDC* cdc, CPoint pt);//output a figure 
	void OutputFigure_Particular_Original(CPoint pt);//output a figure 
};
