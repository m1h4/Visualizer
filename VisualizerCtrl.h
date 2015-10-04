#pragma once

#include "Audio.h"

// VisualizerCtrl.h : Declaration of the CVisualizerCtrl ActiveX Control class.


// CVisualizerCtrl : See VisualizerCtrl.cpp for implementation.

class CVisualizerCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVisualizerCtrl)

// Constructor
public:
	CVisualizerCtrl();
	virtual ~CVisualizerCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	DECLARE_OLECREATE_EX(CVisualizerCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CVisualizerCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVisualizerCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CVisualizerCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

// Event maps
	DECLARE_EVENT_MAP()

protected:
	CComPtr<IAnalyzed>	m_Analyzed;
	CAudio				m_Audio;

// Implementation
protected:
	VARIANT_BOOL Initialize(LONG resolution,VARIANT_BOOL blur);
	VARIANT_BOOL Uninitialize(void);
	VARIANT_BOOL SetVisualization(LONG index);
	LONG GetVisualizationCount(void);
	BSTR GetVisualizationName(LONG index);
	LONG GetVisualization(void);
	LONG PackColor(BYTE alpha, BYTE red, BYTE green, BYTE blue);
	BYTE UnpackColorAlpha(LONG color);
	BYTE UnpackColorRed(LONG color);
	BYTE UnpackColorGreen(LONG color);
	BYTE UnpackColorBlue(LONG color);
	LONG GetColorBackground(void);
	VARIANT_BOOL SetColorBackground(LONG color);
	LONG GetColorTop(void);
	VARIANT_BOOL SetColorTop(LONG color);
	LONG GetColorTopEnd(void);
	VARIANT_BOOL SetColorTopEnd(LONG color);
	LONG GetColorBottom(void);
	VARIANT_BOOL SetColorBottom(LONG color);
	LONG GetColorBottomEnd(void);
	VARIANT_BOOL SetColorBottomEnd(LONG color);
	LONG GetColorPeak(void);
	VARIANT_BOOL SetColorPeak(LONG color);
};

