
// MFCApplication3Dlg.h : header file
//

#pragma once
#include "Visuals.h"
#define GRID_SIZE 25

// CMFCApplication3Dlg dialog
class CMFCApplication3Dlg : public CDialogEx, public Visuals
{
public:
	// standard constructor
	CMFCApplication3Dlg(CWnd* pParent = nullptr);

	// Dialog Data
	#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
	#endif

	// Custom variables
	CTypedPtrArray<CObArray, Visuals*> figs;

	// Custom methods
	void DrawGrid(CDC& pDc, const CRect winSize);
	void DrawVisuals();
	CPoint* GetClosestPointToMouse(const CPoint& mouse);
	void ConnectNodes();

	// Buttons methods
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void PopUpMenu_Input();
	afx_msg void PopUpMenu_Output();
	afx_msg void PopUpMenu_OR_Gate();
	afx_msg void PopUpMenu_AND_Gate();
	afx_msg void PopUpMenu_DrawCircle();
	afx_msg void PopUpMenu_DrawRect();
	afx_msg void PopUpMenu_Prev();
	afx_msg void PopUpMenu_Delete();
	afx_msg void PopUpMenu_DeleteAll();
	afx_msg void PopUpMenu_SaveProj();
	afx_msg void PopUpMenu_LoadProj();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
