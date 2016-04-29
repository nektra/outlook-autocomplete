

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IConnect,0xD73EB608,0xA239,0x453C,0xAD,0x65,0x27,0xF5,0xF1,0x51,0x12,0xCA);


MIDL_DEFINE_GUID(IID, LIBID_NktOlAutoCompleteLib,0x26370930,0x2ABF,0x4EA0,0x8F,0xA2,0x5C,0x3A,0xFF,0xC3,0xAF,0xB2);


MIDL_DEFINE_GUID(CLSID, CLSID_Connect,0x3F645CBC,0x81F4,0x4E85,0xB9,0x86,0x91,0x2A,0xB5,0xE6,0xB9,0x40);


MIDL_DEFINE_GUID(IID, IID_IRibbonCallback,0xCE895442,0x9981,0x4315,0xAA,0x85,0x4B,0x9A,0x5C,0x77,0x39,0xD8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



