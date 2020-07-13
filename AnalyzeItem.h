#pragma once


// CAnalyzeItem
struct LinklistHead{
	LinklistHead* next;
	LinklistHead* last;
	UINT type;
	UINT nLength;

};


class CAnalyzeItem : public CWnd
{
	DECLARE_DYNAMIC(CAnalyzeItem)

public:
	CAnalyzeItem();
	virtual ~CAnalyzeItem();

protected:
	DECLARE_MESSAGE_MAP()
public: 
	void Create(BYTE* buff, UINT nMax);
	LinklistHead* globalHead;//original parent chain blcok
	UINT nCapableLength;//max buffer that contains the linklists 
	UINT nCurrentPos;//current soraging position 

	LinklistHead* InsertItem(LinklistHead* from, BYTE* bt, UINT nLen);//insert one item out range will return a solution name 0 
	LinklistHead* SearchBuffer(LinklistHead* from, BYTE* bt, UINT nLen, UINT Type);//search in a area check the type 
	void SetCurrentItemType(LinklistHead* current, UINT nType);//set current buffer
	LinklistHead* SeekTailOfCurrent(LinklistHead* Current);//output the tail of this buffer
};


