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
	int GetSorageLength();// get the length
	void TransformToSave();//transform the linklist pointer 
	void Anti_TransformToSave();//back transform the linklist 
	void EnableOutput(CEdit* edit);//let the output buffer can send into a edit ctrl
	CEdit* otEdit;//output the edit
	CString csOutput;//output stream
	void TestOutAll();// seek all info 
	void SaveInPath(CString cs);//transform to a file type and save it in particular path
	void readInPath(CString cs);//get buffer in file and transform them into linklist
};


