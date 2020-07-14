// AnalyzeItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TestErrorStream.h"
#include "AnalyzeItem.h"
#include "BasicOperation.h"

#define ENABLE_OUTPUT    1

// CAnalyzeItem

IMPLEMENT_DYNAMIC(CAnalyzeItem, CWnd)
	CAnalyzeItem::CAnalyzeItem()
	: nCapableLength(0)
	, nCurrentPos(0)
	, globalHead(0)
	, otEdit(0)
	, csOutput(L"")
{

}

CAnalyzeItem::~CAnalyzeItem()
{
}


BEGIN_MESSAGE_MAP(CAnalyzeItem, CWnd)
END_MESSAGE_MAP()



// CAnalyzeItem 消息处理程序


void CAnalyzeItem::Create(BYTE* buff, UINT nMax)
{
	globalHead = (LinklistHead*)buff;
	nCapableLength = nMax;
	nCurrentPos = 0;


	globalHead->last = 0;
	globalHead->next = 0;
	globalHead->nLength = 0;
	globalHead->type = 0; 
}


LinklistHead* CAnalyzeItem::InsertItem(LinklistHead* from, BYTE* bt, UINT nLen)
{
	if(nCapableLength <= nCurrentPos + nLen + sizeof(LinklistHead) || from == 0)
		return 0;

	LinklistHead* pFeedBack;
	pFeedBack = (LinklistHead*)(((BYTE*)globalHead) + nCurrentPos);
	if(pFeedBack != globalHead)
	{
		pFeedBack->last = from;
		pFeedBack->next = from->next; 
		if(from->next)
		from->next->last = pFeedBack;
		pFeedBack->last->next = pFeedBack;
	}
	pFeedBack->nLength = nLen;



	BYTE* btBeg;
	btBeg = (((BYTE*)globalHead ) + nCurrentPos + sizeof(LinklistHead));
	for(int i = 0 ;i < nLen; i++)
	{
		btBeg[i] = bt[i];
	}
	//pFeedBack += globalHead + sizeof(LinklistHead);
	nCurrentPos += nLen + sizeof(LinklistHead);

#ifdef ENABLE_OUTPUT

	TestOutAll();
#endif
	return pFeedBack;
}


LinklistHead* CAnalyzeItem::SearchBuffer(LinklistHead* from, BYTE* bt, UINT nLen, UINT Type)
{
	if(nCapableLength <= nCurrentPos + nLen + sizeof(LinklistHead))
		return 0;
	LinklistHead* pFeedBack;
	LinklistHead* pThis;
	UINT nCheckSame;
	pThis = from ? from : globalHead;
	BYTE* btCurrent;
	while(pThis)
	{
		if(Type == pThis->type)
		{
			nCheckSame = 0;
			btCurrent = ((BYTE*)pThis) + sizeof(LinklistHead);
			for(int i = 0 ;i < nLen; i ++)
			{
				if(btCurrent[i] == bt[i])
					nCheckSame ++;
				else break;
			}
			if(nCheckSame == nLen)
			{
				return pThis;
			}
		}
		pThis = pThis->next;
	}

	return 0;
}


void CAnalyzeItem::SetCurrentItemType(LinklistHead* current, UINT nType)
{
	current->type = nType;
#ifdef ENABLE_OUTPUT

	TestOutAll();
#endif
}


LinklistHead* CAnalyzeItem::SeekTailOfCurrent(LinklistHead* Current)
{
	LinklistHead* pFeedback, *pLast;
	pFeedback = Current;
	pLast = Current;
	pFeedback = pFeedback->next;
	while(pFeedback)
	{
		if(pFeedback->type <= Current->type)
		{
			pFeedback = pFeedback->last;
			break;
		}
		pLast = pFeedback;
		pFeedback = pFeedback->next;
	}
	return pFeedback ? pFeedback : pLast;

}


int CAnalyzeItem::GetSorageLength()
{
	return nCurrentPos; 
}


void CAnalyzeItem::TransformToSave()
{
	LinklistHead* pThis;
	pThis = globalHead;
	while(pThis)
	{
		if(pThis->last)
		{
			pThis->last->next = (LinklistHead*)((UINT)pThis->last->next - (UINT)globalHead);
			pThis->last = (LinklistHead*)((UINT)pThis->last - (UINT)globalHead);
		}
		pThis = pThis->next;
	}
}


void CAnalyzeItem::Anti_TransformToSave()
{
	LinklistHead* pThis;
	pThis = globalHead;
	while(pThis)
	{
		if(pThis->next)
		{
			pThis->next = (LinklistHead*)((UINT)pThis->next + (UINT)globalHead);
			pThis->next->last = (LinklistHead*)((UINT)pThis->next->last + (UINT)globalHead);
		}
		pThis = pThis->next;
	}
}


void CAnalyzeItem::EnableOutput(CEdit* edit)
{
	otEdit = edit;
}


void CAnalyzeItem::TestOutAll()
{
	if(!otEdit)return;
	LinklistHead* pThis;
	CString cs;

	csOutput = L"";
	pThis = globalHead;

	while(pThis)
	{
		cs.Format(L"InsertItem  This: %d Last: %d next: %d type: %d info: ", (UINT)pThis, (UINT)pThis->last, (UINT)pThis->next, pThis->type);
		csOutput += cs;
		csOutput += (WCHAR*)((BYTE*)(pThis + 1));
		csOutput += L"\r\n";
		pThis = pThis->next;
		otEdit->SetWindowTextW(csOutput);
	}
}


void CAnalyzeItem::SaveInPath(CString cs)
{
	if(!nCurrentPos)return;

	TransformToSave();
	CBasicOperation::SaveFile_InPath(cs, (BYTE*)globalHead, nCurrentPos);
	Anti_TransformToSave();
}


void CAnalyzeItem::readInPath(CString cs)
{
	CBasicOperation::ReadFile_InPath(cs, (BYTE*)globalHead, nCurrentPos);
	Anti_TransformToSave();

#ifdef ENABLE_OUTPUT
	TestOutAll();
#endif
}


int CAnalyzeItem::GetNearHeadBrench(LinklistHead* pSeek, LinklistHead** pGet)
{
	LinklistHead* pThis;
	UINT nLevel =  pSeek->type;
	pThis = pSeek;
	while(pThis)
	{
		if(pThis->type < nLevel)
		{
			*pGet = pThis;
			return 1;
		}
		pThis =  pThis->last;
	}
	return 0;
}
