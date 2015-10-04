#pragma once

// VisualizerPropPage.h : Declaration of the CVisualizerPropPage property page class.


// CVisualizerPropPage : See VisualizerPropPage.cpp for implementation.

class CVisualizerPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVisualizerPropPage)
	DECLARE_OLECREATE_EX(CVisualizerPropPage)

// Constructor
public:
	CVisualizerPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_VISUALIZER };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

