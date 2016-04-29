

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Fri Apr 29 13:31:38 2016
 */
/* Compiler settings for OlAutoComplete.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "OlAutoComplete_i.h"

#define TYPE_FORMAT_STRING_SIZE   21                                
#define PROC_FORMAT_STRING_SIZE   37                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _OlAutoComplete_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } OlAutoComplete_MIDL_TYPE_FORMAT_STRING;

typedef struct _OlAutoComplete_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } OlAutoComplete_MIDL_PROC_FORMAT_STRING;

typedef struct _OlAutoComplete_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } OlAutoComplete_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const OlAutoComplete_MIDL_TYPE_FORMAT_STRING OlAutoComplete__MIDL_TypeFormatString;
extern const OlAutoComplete_MIDL_PROC_FORMAT_STRING OlAutoComplete__MIDL_ProcFormatString;
extern const OlAutoComplete_MIDL_EXPR_FORMAT_STRING OlAutoComplete__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IConnect_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IConnect_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRibbonCallback_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRibbonCallback_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const OlAutoComplete_MIDL_PROC_FORMAT_STRING OlAutoComplete__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure ButtonClicked */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ribbonControl */

/* 24 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 30 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const OlAutoComplete_MIDL_TYPE_FORMAT_STRING OlAutoComplete__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x20400 ),	/* 132096 */
/*  8 */	NdrFcShort( 0x0 ),	/* 0 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 14 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x0,		/* 0 */
			0x46,		/* 70 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IConnect, ver. 0.0,
   GUID={0xD73EB608,0xA239,0x453C,{0xAD,0x65,0x27,0xF5,0xF1,0x51,0x12,0xCA}} */

#pragma code_seg(".orpc")
static const unsigned short IConnect_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IConnect_ProxyInfo =
    {
    &Object_StubDesc,
    OlAutoComplete__MIDL_ProcFormatString.Format,
    &IConnect_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IConnect_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    OlAutoComplete__MIDL_ProcFormatString.Format,
    &IConnect_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IConnectProxyVtbl = 
{
    0,
    &IID_IConnect,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IConnect_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IConnectStubVtbl =
{
    &IID_IConnect,
    &IConnect_ServerInfo,
    7,
    &IConnect_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Standard interface: __MIDL_itf_OlAutoComplete_0000_0002, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IRibbonCallback, ver. 0.0,
   GUID={0xCE895442,0x9981,0x4315,{0xAA,0x85,0x4B,0x9A,0x5C,0x77,0x39,0xD8}} */

#pragma code_seg(".orpc")
static const unsigned short IRibbonCallback_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IRibbonCallback_ProxyInfo =
    {
    &Object_StubDesc,
    OlAutoComplete__MIDL_ProcFormatString.Format,
    &IRibbonCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRibbonCallback_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    OlAutoComplete__MIDL_ProcFormatString.Format,
    &IRibbonCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRibbonCallbackProxyVtbl = 
{
    &IRibbonCallback_ProxyInfo,
    &IID_IRibbonCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRibbonCallback::ButtonClicked */
};


static const PRPC_STUB_FUNCTION IRibbonCallback_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRibbonCallbackStubVtbl =
{
    &IID_IRibbonCallback,
    &IRibbonCallback_ServerInfo,
    8,
    &IRibbonCallback_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    OlAutoComplete__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x8000253, /* MIDL Version 8.0.595 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _OlAutoComplete_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IConnectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRibbonCallbackProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _OlAutoComplete_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IConnectStubVtbl,
    ( CInterfaceStubVtbl *) &_IRibbonCallbackStubVtbl,
    0
};

PCInterfaceName const _OlAutoComplete_InterfaceNamesList[] = 
{
    "IConnect",
    "IRibbonCallback",
    0
};

const IID *  const _OlAutoComplete_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _OlAutoComplete_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _OlAutoComplete, pIID, n)

int __stdcall _OlAutoComplete_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _OlAutoComplete, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _OlAutoComplete, 2, *pIndex )
    
}

const ExtendedProxyFileInfo OlAutoComplete_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _OlAutoComplete_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _OlAutoComplete_StubVtblList,
    (const PCInterfaceName * ) & _OlAutoComplete_InterfaceNamesList,
    (const IID ** ) & _OlAutoComplete_BaseIIDList,
    & _OlAutoComplete_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

