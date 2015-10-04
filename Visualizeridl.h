

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Nov 18 03:23:32 2007
 */
/* Compiler settings for .\Visualizer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Visualizeridl_h__
#define __Visualizeridl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVisualizer_FWD_DEFINED__
#define __IVisualizer_FWD_DEFINED__
typedef interface IVisualizer IVisualizer;
#endif 	/* __IVisualizer_FWD_DEFINED__ */


#ifndef __IVisualizerEvents_FWD_DEFINED__
#define __IVisualizerEvents_FWD_DEFINED__
typedef interface IVisualizerEvents IVisualizerEvents;
#endif 	/* __IVisualizerEvents_FWD_DEFINED__ */


#ifndef __Visualizer_FWD_DEFINED__
#define __Visualizer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Visualizer Visualizer;
#else
typedef struct Visualizer Visualizer;
#endif /* __cplusplus */

#endif 	/* __Visualizer_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __Visualizer_LIBRARY_DEFINED__
#define __Visualizer_LIBRARY_DEFINED__

/* library Visualizer */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_Visualizer;

#ifndef __IVisualizer_DISPINTERFACE_DEFINED__
#define __IVisualizer_DISPINTERFACE_DEFINED__

/* dispinterface IVisualizer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IVisualizer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("825A1EE0-97B6-4EF2-AE7C-5491649EAD16")
    IVisualizer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IVisualizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisualizer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisualizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisualizer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVisualizer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVisualizer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVisualizer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVisualizer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IVisualizerVtbl;

    interface IVisualizer
    {
        CONST_VTBL struct IVisualizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisualizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisualizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisualizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisualizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVisualizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVisualizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVisualizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IVisualizer_DISPINTERFACE_DEFINED__ */


#ifndef __IVisualizerEvents_DISPINTERFACE_DEFINED__
#define __IVisualizerEvents_DISPINTERFACE_DEFINED__

/* dispinterface IVisualizerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IVisualizerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("96A638C5-D627-4D5F-96F3-CD457773CC42")
    IVisualizerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IVisualizerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisualizerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisualizerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisualizerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVisualizerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVisualizerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVisualizerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVisualizerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IVisualizerEventsVtbl;

    interface IVisualizerEvents
    {
        CONST_VTBL struct IVisualizerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisualizerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisualizerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisualizerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisualizerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVisualizerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVisualizerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVisualizerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IVisualizerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Visualizer;

#ifdef __cplusplus

class DECLSPEC_UUID("6F398387-0A0B-42F0-A4E0-BCAF9EC88DE5")
Visualizer;
#endif
#endif /* __Visualizer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


