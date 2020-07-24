
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持






#include <afxsock.h>            // MFC 套接字扩展



//三、	控制代码
//    信号	           代码	    描述	
const BYTE CTL_SD	    =0x53;	//帧开始	
const BYTE CTL_ED	    =0x45;	//帧结束			
const BYTE CTL_ACK	    =0x41;	//确认	
const BYTE CTL_ACKP	    =0x42;  //数据包包确认
const BYTE CTL_NAK	    =0x4E;	//不能确认

//四、	功能码
//    命令	            代码	描述
const BYTE FC_CONNECT	=0x00;	//建立与设备的连接
const BYTE FC_DISCONN	=0x01;	//断开与设备的连接
const BYTE FC_RUN	    =0x02;	//设备运行
const BYTE FC_STOP	    =0x03;	//设备停止
const BYTE FC_IL_WRITE	=0x04;	//写入指令表文件
const BYTE FC_IL_READ	=0x05;	//读出指令表文件
const BYTE FC_IL_DATA	=0x06;	//指令表数据

const BYTE FC_TX_DATA	=0x0f;  //传送数据

const BYTE FC_GET_BIT	=0x10;	//获取位元件
const BYTE FC_SET_BIT	=0x11;	//设置位元件
const BYTE FC_GET_WORD	=0x12;	//获取位元件组、字元件
const BYTE FC_SET_WORD	=0x13;	//设置位元件组、字元件
const BYTE FC_DBG_START	=0x20;	//开始监控
const BYTE FC_DBG_END	=0x21;	//停止监控
const BYTE FC_DBG_RUN_TO=0x22;	//运行至指定处









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


extern UINT nGlobalThread;

struct OUTPUT_SENDMSG_COM{

	UINT nType;
	UINT nLen;
	BYTE* buffer;
};

#define MSG_SEND				1
#define MSG_POP_INFO			2//SEND THE MOUSE MOVE DATA FROM VIEW CLASS. THE SKETCH DLG WILL GET THE DETAIL
#define MSG_COORDINATE			3//Drawing according to coordinate 


extern UINT nPointerViewHWND;

typedef int (CALLBACK* PLCIDECALLBACK)(int *pInfo);//


extern UINT nPointerView;

extern UINT nPointerDlgSketch;
















