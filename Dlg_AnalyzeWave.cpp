// Dlg_AnalyzeWave.cpp : 实现文件
//

#include "stdafx.h"
#include "TestErrorStream.h"
#include "Dlg_AnalyzeWave.h"
#include "afxdialogex.h"
#include "BasicOperation.h"


// CDlg_AnalyzeWave 对话框
UINT m_edt_DelayValue;
UINT nSeriesStorage[1000000];
CPoint nDrawPlace[1000000];
UINT nLengthnSeriesStorage;




IMPLEMENT_DYNAMIC(CDlg_AnalyzeWave, CDialogEx)

	CDlg_AnalyzeWave::CDlg_AnalyzeWave(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_AnalyzeWave::IDD, pParent)
{

}


CDlg_AnalyzeWave::~CDlg_AnalyzeWave()
{
}


void CDlg_AnalyzeWave::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HOR_DELTA, m_HorDelta);
	DDX_Control(pDX, IDC_EDIT_VER_DELTA, m_Edit_VerDelta);
	DDX_Control(pDX, IDC_EDIT_X_BEGIN, m_Edit_XBegin);
	DDX_Control(pDX, IDC_EDIT_Y_BEGIN, m_Edit_YBegin);
	DDX_Control(pDX, IDC_SPIN1, m_SPin_horDel);
	DDX_Control(pDX, IDC_SPIN2, m_SPin_VerDel);
	DDX_Control(pDX, IDC_SPIN3, m_SPin_XBeg);
	DDX_Control(pDX, IDC_SPIN4, m_SPin_YBeg);
	DDX_Control(pDX, IDC_EDIT_BEG, m_Edit_Beg);
	DDX_Control(pDX, IDC_EDIT_END, m_Edit_End);
	DDX_Control(pDX, IDC_EDIT_LEFT, m_Edit_Left);
	DDX_Control(pDX, IDC_EDIT_RIGHT, m_Edit_Right);
	DDX_Control(pDX, IDC_EDIT_TOP, m_Edit_Top);
	DDX_Control(pDX, IDC_EDIT_BOTTOM, m_Edit_Bottom);
	DDX_Control(pDX, IDC_CHECK_COORDINATE, m_Check_Coordinate);
}


BEGIN_MESSAGE_MAP(CDlg_AnalyzeWave, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WANT_WAVE, &CDlg_AnalyzeWave::OnBnClickedButtonWantWave)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlg_AnalyzeWave::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CDlg_AnalyzeWave::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CDlg_AnalyzeWave::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CDlg_AnalyzeWave::OnDeltaposSpin4)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CDlg_AnalyzeWave::OnBnClickedButtonOutput)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlg_AnalyzeWave::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CDlg_AnalyzeWave 消息处理程序


void CDlg_AnalyzeWave::OnBnClickedButtonWantWave()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlg_AnalyzeWave::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlg_AnalyzeWave::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlg_AnalyzeWave::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlg_AnalyzeWave::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlg_AnalyzeWave::Create(HWND hd)
{
	CDialog::Create(CDlg_AnalyzeWave::IDD);
	ShowWindow(SW_SHOW);

	m_SPin_horDel.SetBuddy(GetDlgItem(IDC_EDIT_HOR_DELTA));
	m_SPin_VerDel.SetBuddy(GetDlgItem(IDC_EDIT_VER_DELTA));
	m_SPin_XBeg  .SetBuddy(GetDlgItem(IDC_EDIT_X_BEGIN));
	m_SPin_YBeg  .SetBuddy(GetDlgItem(IDC_EDIT_Y_BEGIN));
	m_SPin_horDel.SetRange32(-10000, 10000);
	m_SPin_VerDel.SetRange32(-10000, 10000);
	m_SPin_XBeg  .SetRange32(-10000, 10000);
	m_SPin_YBeg  .SetRange32(-10000, 10000);
	m_SPin_horDel.SetBase(10);
	m_SPin_VerDel.SetBase(10);
	m_SPin_XBeg  .SetBase(10);
	m_SPin_YBeg  .SetBase(10);
	nLengthnSeriesStorage = 0;
	out_hd = hd;
	nPointerDlgSketch = (UINT)this;

	CString cs;
	cs.Format(L"%d", 50);
	m_Edit_Left.SetWindowTextW(cs);
	cs.Format(L"%d", 1050);
	m_Edit_Right.SetWindowTextW(cs);
	cs.Format(L"%d", 100);
	m_Edit_Top.SetWindowTextW(cs);
	cs.Format(L"%d", 500);
	m_Edit_Bottom.SetWindowTextW(cs);
}


void CDlg_AnalyzeWave::InsertDatas(int nHeight)
{
	nSeriesStorage[nLengthnSeriesStorage] = nHeight;
	nLengthnSeriesStorage ++;

	HDC dc;
	CString cs;
	dc = ::GetDC(out_hd);
	cs.Format(L"%d         ", nHeight);


	::TextOutW(dc, 10, 10, cs, cs.GetLength() );
	::ReleaseDC(out_hd, dc);
	cs.Format(L"%d", nLengthnSeriesStorage);
	m_Edit_End.SetWindowTextW(cs);
	OnBnClickedButtonOutput();
}


void CDlg_AnalyzeWave::SketchOutput()
{

	HDC dc;
	RECT rtGet, rtFull;
	float pX, pY;

	dc = ::GetDC(out_hd);
	::TextOutW(dc, 10, 10, L"sketchFigure", sizeof(L"sketchFigure") / sizeof(WCHAR) - 1);

	m_stRender.rt.left   = CBasicOperation::GetIntFromEdit(&m_Edit_Left);
	m_stRender.rt.right  = CBasicOperation::GetIntFromEdit(&m_Edit_Right);
	m_stRender.rt.top    = CBasicOperation::GetIntFromEdit(&m_Edit_Top);
	m_stRender.rt.bottom = CBasicOperation::GetIntFromEdit(&m_Edit_Bottom);
	m_stRender.nFrom = CBasicOperation::GetIntFromEdit(&m_Edit_Beg);
	m_stRender.nTo = CBasicOperation::GetIntFromEdit(&m_Edit_End);

	GenerateStructRender();

	rtGet = m_stRender.rt;
	rtGet.bottom += 5;
	rtGet.right  += 5;
	rtGet.left   -= 5;
	rtGet.top    -= 5;

	::GetClientRect(out_hd, &rtFull);
	HBRUSH hbr= CreateSolidBrush(RGB(255,255,255));
	::FillRect(dc, &rtFull, hbr);

	::DeleteObject(hbr);
	hbr= CreateSolidBrush(RGB(230,230,230));
	::FillRect(dc, &rtGet, hbr);

	pX = m_stRender.rt.left + m_stRender.fXScale * 0;
	pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[m_stRender.nFrom] - m_stRender.nMin);
	::MoveToEx(dc, (int)pX, (int)pY, 0);
	nDrawPlace[m_stRender.nFrom] = CPoint(pX, pY);
	for(int i = m_stRender.nFrom; i < m_stRender.nTo; i ++)
	{
		pX = m_stRender.rt.left + m_stRender.fXScale * (i - m_stRender.nFrom);
		pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[(i)] - m_stRender.nMin);
		nDrawPlace[i] = CPoint(pX, pY);
		::LineTo(dc, (int)pX, (int)pY);
	}
	::DeleteObject(hbr);
	::ReleaseDC(out_hd, dc);
}


void CDlg_AnalyzeWave::OnBnClickedButtonOutput()
{
	FillBufferInBitmap();
	//SketchOutput();
	// TODO: 在此添加控件通知处理程序代码
}


void CDlg_AnalyzeWave::GenerateStructRender()
{
	m_stRender.fDisplaceX = 0;
	m_stRender.fDisplaceY = 0;
	m_stRender.fXScale = (float)(m_stRender.rt.right - m_stRender.rt.left) / (float)(m_stRender.nTo - m_stRender.nFrom); 
	m_stRender.nMax = nSeriesStorage[m_stRender.nFrom];
	m_stRender.nMin = nSeriesStorage[m_stRender.nFrom];
	m_stRender.nMaxID = m_stRender.nMinID = m_stRender.nFrom;
	for(int i = m_stRender.nFrom; i < m_stRender.nTo; i ++)
	{
		if(m_stRender.nMax < nSeriesStorage[i])
		{
			m_stRender.nMax = nSeriesStorage[i];
			m_stRender.nMaxID = i;
		}
		if(m_stRender.nMin > nSeriesStorage[i])
		{
			m_stRender.nMin = nSeriesStorage[i];
			m_stRender.nMinID = i;
		}
	}
	m_stRender.fYScale = (float)(m_stRender.rt.bottom - m_stRender.rt.top) / (float)(m_stRender.nMax - m_stRender.nMin);
}


void CDlg_AnalyzeWave::OnBnClickedButtonClear()
{
	nLengthnSeriesStorage = 0;
	FillBufferInBitmap();
	// TODO: 在此添加控件通知处理程序代码
}


void CDlg_AnalyzeWave::SketchCoordinate(CPoint pt)
{
	if(m_Check_Coordinate.GetCheck())
	{
		SketchOutput();
		HDC dc; 
		float pX, pY;
		CPoint point;

		dc = ::GetDC(out_hd);
		::TextOutW(dc, 10, 50, L"sketchFigure", sizeof(L"sketchFigure") / sizeof(WCHAR) - 1);



		pX = m_stRender.rt.left + m_stRender.fXScale * 0;
		pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[m_stRender.nFrom] - m_stRender.nMin);
		::MoveToEx(dc, (int)pX, (int)pY, 0);
		nDrawPlace[m_stRender.nFrom] = CPoint(pX, pY);

		for(int i = m_stRender.nFrom; i < m_stRender.nTo; i ++)
		{
			pX = m_stRender.rt.left + m_stRender.fXScale * (i - m_stRender.nFrom);
			pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[(i)] - m_stRender.nMin);
			nDrawPlace[i] = CPoint(pX, pY);
			::LineTo(dc, (int)pX, (int)pY);
		}

		for(int i = m_stRender.nFrom + 1; i < m_stRender.nTo; i ++)
		{
			if(HeightInLine(nDrawPlace + i - 1, pt.y, &point))
			{

				::Ellipse(dc, point.x - 5, point.y - 5, point.x + 5, point.y + 5);
				::SetPixel(dc, point.x, point.y, 0xffffff);
			}
		}
		::ReleaseDC(out_hd, dc);
	}
}


int CDlg_AnalyzeWave::HeightInLine(CPoint* ptLine, int nHeight, CPoint* pt)
{



	if((ptLine[0].y - nHeight) * (ptLine[1].y - nHeight) <= 0)
	{
		CPoint ptBeg;
		float x0, y0, x1, y1, x, y, k;
		x0 = ptLine[0].x;
		y0 = ptLine[0].y;
		x1 = ptLine[1].x;
		y1 = ptLine[1].y;
		y = nHeight;
		k = (x1 - x0) / (y1 - y0);
		x = k * (y - y0) + x0;
		pt[0] = CPoint(x, y);
		return 1;
	}
	return 0;
}


void CDlg_AnalyzeWave::FillBufferInBitmap()
{
	CDC *pDC;

	pDC = new CDC;
	
	HDC dc;

	dc = ::GetDC(out_hd);

	pDC->Attach(dc);

	CPoint ptCenter;

	CRect rect,ellipseRect;

	::GetClientRect(out_hd, &rect);
	//GetClientRect(&rect);

	ptCenter = rect.CenterPoint();

	CDC dcMem;                                                  //用于缓冲作图的内存DC

	CBitmap bmp;                                                 //内存中承载临时图象的位图

	dcMem.CreateCompatibleDC(pDC);               //依附窗口DC创建兼容内存DC

	bmp.CreateCompatibleBitmap(&dcMem,rect.Width(),rect.Height());//创建兼容位图

	dcMem.SelectObject(&bmp);                          //将位图选择进内存DC

	dcMem.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，不然会是黑色

	OutputFigure(&dcMem); 

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//将内存DC上的图象拷贝到前台

	dcMem.DeleteDC();                                       //删除DC

	bmp.DeleteObject();                                        //删除位图

	::ReleaseDC(out_hd, dc);

	delete pDC;
}


void CDlg_AnalyzeWave::OutputFigure(CDC* cdc)
{
	 
	RECT rtGet, rtFull;
	float pX, pY;
	CBrush brOt;

	  

	m_stRender.rt.left   = CBasicOperation::GetIntFromEdit(&m_Edit_Left);
	m_stRender.rt.right  = CBasicOperation::GetIntFromEdit(&m_Edit_Right);
	m_stRender.rt.top    = CBasicOperation::GetIntFromEdit(&m_Edit_Top);
	m_stRender.rt.bottom = CBasicOperation::GetIntFromEdit(&m_Edit_Bottom);
	m_stRender.nFrom     = CBasicOperation::GetIntFromEdit(&m_Edit_Beg);
	m_stRender.nTo       = CBasicOperation::GetIntFromEdit(&m_Edit_End);

	GenerateStructRender();

	rtGet = m_stRender.rt;
	rtGet.bottom += 5;
	rtGet.right  += 5;
	rtGet.left   -= 5;
	rtGet.top    -= 5;

	::GetClientRect(out_hd, &rtFull);

	brOt.CreateSolidBrush(0xffffff);
	cdc->FillRect(&rtFull, &brOt);

	brOt.DeleteObject();
	brOt.CreateSolidBrush(0xeeeeee);

	cdc->FillRect(&rtGet, &brOt);

	pX = m_stRender.rt.left + m_stRender.fXScale * 0;
	pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[m_stRender.nFrom] - m_stRender.nMin);
	cdc->MoveTo((int)pX, (int)pY);
	//::MoveToEx(dc, (int)pX, (int)pY, 0);
	nDrawPlace[m_stRender.nFrom] = CPoint(pX, pY);
	for(int i = m_stRender.nFrom; i < m_stRender.nTo; i ++)
	{
		pX = m_stRender.rt.left + m_stRender.fXScale * (i - m_stRender.nFrom);
		pY = m_stRender.rt.bottom - m_stRender.fYScale * (nSeriesStorage[(i)] - m_stRender.nMin);
		nDrawPlace[i] = CPoint(pX, pY);
	cdc->LineTo((int)pX, (int)pY);
		//::LineTo(dc, (int)pX, (int)pY);
	}
	brOt.DeleteObject();
//	::DeleteObject(hbr);
	//::ReleaseDC(out_hd, dc);
}


void CDlg_AnalyzeWave::OutputFigure_Particular(CDC* cdc, CPoint pt)
{
	
		OutputFigure(cdc);
		HDC dc; 
		float pX, pY;
		CPoint point;
		CBrush brOt;
		
		for(int i = m_stRender.nFrom + 1; i < m_stRender.nTo; i ++)
		{
			if(HeightInLine(nDrawPlace + i - 1, pt.y, &point))
			{

				cdc->Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
			}
		} 
}


void CDlg_AnalyzeWave::OutputFigure_Particular_Original(CPoint pt)
{
	
	if(!m_Check_Coordinate.GetCheck())
	{
	CDC *pDC;

	pDC = new CDC;
	
	HDC dc;

	dc = ::GetDC(out_hd);

	pDC->Attach(dc);

	CPoint ptCenter;

	CRect rect,ellipseRect;

	::GetClientRect(out_hd, &rect);
	//GetClientRect(&rect);

	ptCenter = rect.CenterPoint();

	CDC dcMem;                                                  //用于缓冲作图的内存DC

	CBitmap bmp;                                                 //内存中承载临时图象的位图

	dcMem.CreateCompatibleDC(pDC);               //依附窗口DC创建兼容内存DC

	bmp.CreateCompatibleBitmap(&dcMem,rect.Width(),rect.Height());//创建兼容位图

	dcMem.SelectObject(&bmp);                          //将位图选择进内存DC

	dcMem.FillSolidRect(rect,pDC->GetBkColor());//按原来背景填充客户区，不然会是黑色

	OutputFigure_Particular(&dcMem, pt); 

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//将内存DC上的图象拷贝到前台

	dcMem.DeleteDC();                                       //删除DC

	bmp.DeleteObject();                                        //删除位图

	::ReleaseDC(out_hd, dc);

	delete pDC;
	}
}
