// AnalyzeItem.cpp : 实现文件
//

#include "stdafx.h"
#include "TestErrorStream.h"
#include "AnalyzeItem.h"


// CAnalyzeItem

IMPLEMENT_DYNAMIC(CAnalyzeItem, CWnd)
	CAnalyzeItem::CAnalyzeItem()
	: nCapableLength(0)
	, nCurrentPos(0)
	, globalHead(0)
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
	pFeedBack = (LinklistHead*)(((BYTE*)globalHead ) + nCurrentPos);
	pFeedBack->last = from;
	pFeedBack->next = from->next;
	pFeedBack->nLength = nLen;

	from->next = pFeedBack;

	if(from->next)
		from->next->last = pFeedBack;
	BYTE* btBeg;
	btBeg = (((BYTE*)globalHead ) + nCurrentPos + sizeof(LinklistHead));
	for(int i = 0 ;i < nLen; i++)
	{
		btBeg[i] = bt[i];
	}
	pFeedBack += nLen + sizeof(LinklistHead);
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
}


LinklistHead* CAnalyzeItem::SeekTailOfCurrent(LinklistHead* Current)
{
	LinklistHead* pFeedback;
	pFeedback = Current;
	pFeedback = pFeedback->next;
	while(pFeedback)
	{
		if(pFeedback->type <= Current->type)
		{
			pFeedback = pFeedback->last;
			break;
		}
		pFeedback = pFeedback->next;
	}
	return pFeedback ? pFeedback : Current;

}
