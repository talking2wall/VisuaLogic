
// MFCApplication3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "Visuals.h"
#include "Node.h"
#include "Input.h"
#include "Output.h"
#include "Wire.h"
#include "OR_Gate.h"
#include "AND_Gate.h"
#include "Circle.h"
#include "Recta.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Global Variables
CDC* pDC;
bool gEditMode = false;
bool gWireMode = false;
int gActiveComponentsCount = 0;
int gClickCount = 0;
CPoint gMousePos;
CPoint gRightClickMousePos;
Node* gConNodes[2] = { NULL, NULL }; // using to connect nodes

// CMFCApplication3Dlg dialog
CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent), Visuals(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_INPUT, &CMFCApplication3Dlg::PopUpMenu_Input)
	ON_COMMAND(ID_OUTPUT, &CMFCApplication3Dlg::PopUpMenu_Output)
	ON_COMMAND(ID_OR_GATE, &CMFCApplication3Dlg::PopUpMenu_OR_Gate)
	ON_COMMAND(ID_AND_GATE, &CMFCApplication3Dlg::PopUpMenu_AND_Gate)
	ON_COMMAND(ID_DRAW_CIRCLE, &CMFCApplication3Dlg::PopUpMenu_DrawCircle)
	ON_COMMAND(ID_DRAW_RECT, &CMFCApplication3Dlg::PopUpMenu_DrawRect)
	ON_COMMAND(ID_PREV, &CMFCApplication3Dlg::PopUpMenu_Prev)
	ON_COMMAND(ID_DELETE, &CMFCApplication3Dlg::PopUpMenu_Delete)
	ON_COMMAND(ID_DELETE_ALL, &CMFCApplication3Dlg::PopUpMenu_DeleteAll)
	ON_COMMAND(ID_SAVE_PROJ, &CMFCApplication3Dlg::PopUpMenu_SaveProj)
	ON_COMMAND(ID_LOAD_PROJ, &CMFCApplication3Dlg::PopUpMenu_LoadProj)
	ON_WM_MOUSEMOVE()
	ON_WM_MOVING()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	
END_MESSAGE_MAP()


// CMFCApplication3Dlg message handlers

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawVisuals();

		CDialogEx::OnPaint();
	}
}

void CMFCApplication3Dlg::DrawVisuals()
{
	CDC MemDC;
	CRect winSize;
	CBitmap MemBitmap;

	GetClientRect(&winSize);

	pDC = GetDC();
	MemDC.CreateCompatibleDC(pDC);//Create a memory DC compatible with the target DC---MemDC
	MemBitmap.CreateCompatibleBitmap(pDC, winSize.Width(), winSize.Height());//Create a bitmap based on the target DC
	MemDC.SelectObject(&MemBitmap);//Select the bitmap into the memory DC

	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowOrg(0, 0);//Set the origin
	MemDC.SetWindowExt(winSize.Width(), winSize.Height());//Set the window size, that is, the size of the drawing area
	MemDC.SetViewportExt(winSize.right, winSize.bottom);
	MemDC.SetViewportOrg(0, 0);

	MemDC.FillSolidRect(winSize, RGB(255, 255, 255));//Background fill

	CPen newPen;
	newPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//Create a pen
	MemDC.SelectObject(newPen);//Select the pen

	// Drawing methods
	DrawGrid(MemDC, winSize);

	// MemDC Style
	CPen linePen;
	linePen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	MemDC.SelectObject(linePen);
	CFont myFont;
	myFont.CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SelectObject(&myFont);

	////////////////////////////////////////////
	
	for (int i = 0; i < figs.GetCount(); i++)
	{
		switch (figs[i]->getType())
		{
			case 1: // Input
			{
				Input* pInput = dynamic_cast<Input*>(figs[i]);
				if (pInput != NULL)
					pInput->Draw(MemDC);
			} break;

			case 2: // Output
			{
				Output* pOutput = dynamic_cast<Output*>(figs[i]);
				if (pOutput != NULL)
					pOutput->Draw(MemDC);
			} break;

			case 3: // OR_Gate
			{
				OR_Gate* pOR_Gate = dynamic_cast<OR_Gate*>(figs[i]);
				if (pOR_Gate != NULL)
					pOR_Gate->Draw(MemDC);
			} break;

			case 4: // AND_Gate
			{
				AND_Gate* pAND_Gate = dynamic_cast<AND_Gate*>(figs[i]);
				if (pAND_Gate != NULL)
					pAND_Gate->Draw(MemDC);
			} break;

			case 5: // Wire
			{
				Wire* pWire = dynamic_cast<Wire*>(figs[i]);
				if (pWire != NULL)
					pWire->Draw(MemDC);
			} break;

			case 6: // Circle
			{
				Circle* pCircle = dynamic_cast<Circle*>(figs[i]);
				if (pCircle != NULL)
					pCircle->Draw(MemDC);
			} break;

			case 7: // Recta
			{
				Recta* pRecta = dynamic_cast<Recta*>(figs[i]);
				if (pRecta != NULL)
					pRecta->Draw(MemDC);
			} break;
		}
	}

	///////////////////////////////////////////

	pDC->BitBlt(winSize.left, winSize.top, winSize.Width(), winSize.Height(), &MemDC, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
}

void CMFCApplication3Dlg::PopUpMenu_Input()
{
	gEditMode = true;
	figs.Add(new Input(gMousePos, 1));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_Output()
{
	gEditMode = true;
	figs.Add(new Output(gMousePos));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_OR_Gate()
{
	gEditMode = true;
	figs.Add(new OR_Gate(gMousePos));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_AND_Gate()
{
	gEditMode = true;
	figs.Add(new AND_Gate(gMousePos));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_DrawCircle()
{
	gEditMode = true;
	gRightClickMousePos = gMousePos;
	figs.Add(new Circle(gMousePos));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_DrawRect()
{
	gEditMode = true;
	gRightClickMousePos = gMousePos;
	figs.Add(new Recta(gMousePos));
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_Prev()
{
	if (figs.GetCount() > 0)
	{
		figs.RemoveAt(figs.GetCount() - 1);
		DrawVisuals();
	}
}
void CMFCApplication3Dlg::PopUpMenu_Delete()
{
	for (int i = figs.GetCount() - 1; i >= 0; i--)
	{
		switch (figs[i]->getType())
		{
		case 1: // Input
		{
			Input* pInput = dynamic_cast<Input*>(figs[i]);
			if (pInput != NULL && pInput->IsInside(gMousePos))
			{
				pInput->getNode()->turnOff();
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 2: // Output
		{
			Output* pOutput = dynamic_cast<Output*>(figs[i]);
			if (pOutput != NULL && pOutput->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 3: // OR_Gate
		{
			OR_Gate* pOR_Gate = dynamic_cast<OR_Gate*>(figs[i]);
			if (pOR_Gate != NULL && pOR_Gate->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 4: // AND_Gate
		{
			AND_Gate* pAND_Gate = dynamic_cast<AND_Gate*>(figs[i]);
			if (pAND_Gate != NULL && pAND_Gate->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 5: // Wire
		{
			Wire* pWire = dynamic_cast<Wire*>(figs[i]);
			if (pWire != NULL && pWire->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 6: // Circle
		{
			Circle* pCircle = dynamic_cast<Circle*>(figs[i]);
			if (pCircle != NULL && pCircle->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;

		case 7: // Recta
		{
			Recta* pRecta = dynamic_cast<Recta*>(figs[i]);
			if (pRecta != NULL && pRecta->IsInside(gMousePos))
			{
				figs.RemoveAt(i);
				DrawVisuals();
				return;
			}
		} break;
		}
	}
}
void CMFCApplication3Dlg::PopUpMenu_DeleteAll()
{
	figs.RemoveAll();
	DrawVisuals();
}
void CMFCApplication3Dlg::PopUpMenu_SaveProj()
{
	CTypedPtrArray<CObArray, Visuals*> figsNoWires;

	for (int i = 0; i < figs.GetCount(); i++)
	{
		Wire* pWire;
		pWire = dynamic_cast<Wire*>(figs[i]);
		if (pWire == NULL)
			figsNoWires.Add(figs[i]);
	}

	CFileDialog dlg(FALSE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		figsNoWires.Serialize(ar);
		ar.Close();
		file.Close();
	}
}
void CMFCApplication3Dlg::PopUpMenu_LoadProj()
{
	figs.RemoveAll();

	CFileDialog dlg(TRUE, _T(".figs"), NULL, 0, _T("Figures (*.figs)|*.figs|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		figs.Serialize(ar);
		ar.Close();
		file.Close();
		DrawVisuals();
	}
}

void CMFCApplication3Dlg::DrawGrid(CDC& pDC, const CRect winSize)
{
	const int height = winSize.Height();
	const int width = winSize.Width();

	// Changing pen & saving old pen pointer
	CPen newPen;
	newPen.CreatePen(PS_DOT, 1, RGB(52, 150, 235));
	CPen* oldPen = pDC.SelectObject(&newPen);
	pDC.SelectObject(&newPen);

	for (int i = 0; i <= width / GRID_SIZE; i++) // horizontal lines (---)
	{
		pDC.MoveTo(GRID_SIZE * i, 0);
		pDC.LineTo(GRID_SIZE * i, height);
	}

	for (int i = 0; i <= height / GRID_SIZE; i++) // vertical lines ( | )
	{
		pDC.MoveTo(0, GRID_SIZE * i);
		pDC.LineTo(width, GRID_SIZE * i);
	}

	// switching back to the old pen
	pDC.SelectObject(oldPen);
}

CPoint* CMFCApplication3Dlg::GetClosestPointToMouse(const CPoint& mouse)
{
	CRect winSize;
	GetWindowRect(&winSize);

	CPoint* pointOnGraph = new CPoint(0, 0);

	if (mouse.x % GRID_SIZE > GRID_SIZE / 2)
	{
		pointOnGraph->x = mouse.x + (GRID_SIZE - mouse.x % GRID_SIZE);
	}
	else
	{
		pointOnGraph->x = mouse.x - mouse.x % GRID_SIZE;
	}

	if (mouse.y % GRID_SIZE > GRID_SIZE / 2)
	{
		pointOnGraph->y = mouse.y + (GRID_SIZE - mouse.y % GRID_SIZE);
	}
	else
	{
		pointOnGraph->y = mouse.y - mouse.y % GRID_SIZE;
	}

	return pointOnGraph;
}

void CMFCApplication3Dlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// get current right-click position
	gRightClickMousePos = gMousePos;

	// remove wire
	if (gWireMode == true)
	{
		figs.RemoveAt(figs.GetCount() - 1);
		gClickCount = 0;
		gWireMode = false;
		DrawVisuals();
	}
	else
	{
		ClientToScreen(&point);

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU2));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pWndPopupOwner);
	}
}

HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	// The system calls this function to obtain the cursor to display while the user drags
	//  the minimized window.
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	gMousePos = *GetClosestPointToMouse(point);
	int currentVisual = figs.GetCount() - 1;

	if (gEditMode || gWireMode)
	{
		switch (figs[currentVisual]->getType())
		{
			case 1: // Input
			{
				Input* pInput = dynamic_cast<Input*>(figs[currentVisual]);
				if (pInput != NULL)
					pInput->Move(gMousePos);
			} break;

			case 2: // Output
			{
				Output* pOutput = dynamic_cast<Output*>(figs[currentVisual]);
				if (pOutput != NULL)
					pOutput->Move(gMousePos);
			} break;

			case 3: // OR_Gate
			{
				OR_Gate* pOR_Gate = dynamic_cast<OR_Gate*>(figs[currentVisual]);
				if (pOR_Gate != NULL)
					pOR_Gate->Move(gMousePos);
			} break;

			case 4: // AND_Gate
			{
				AND_Gate* pAND_Gate = dynamic_cast<AND_Gate*>(figs[currentVisual]);
				if (pAND_Gate != NULL)
					pAND_Gate->Move(gMousePos);
			} break;

			case 5: // Wire
			{
				Wire* pWire = dynamic_cast<Wire*>(figs[currentVisual]);
				if (pWire != NULL)
					pWire->Move(gMousePos);
			} break;

			case 6: // Circle
			{
				Circle* pCircle = dynamic_cast<Circle*>(figs[currentVisual]);
				if (pCircle != NULL)
					pCircle->Move(gMousePos);
			} break;

			case 7: // Recta
			{
				Recta* pRecta = dynamic_cast<Recta*>(figs[currentVisual]);
				if (pRecta != NULL)
					pRecta->Move(gMousePos);
			} break;
		}
		DrawVisuals();
	}

	__super::OnMouseMove(nFlags, point);
}

void CMFCApplication3Dlg::ConnectNodes()
{
	if (gConNodes[0]->getInfoNode() != NULL || gConNodes[1]->getInfoNode() != NULL)
	{
		if (gConNodes[0]->getInfoNode() == NULL)
			gConNodes[0]->setInfoNode(gConNodes[1]);
		else
			gConNodes[1]->setInfoNode(gConNodes[0]);

		gActiveComponentsCount++;
	}
}

void CMFCApplication3Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (gEditMode)
	{
		gEditMode = false;
	}
	else
	{
		for (int i = 0; i < figs.GetCount(); i++)
		{
			switch (figs[i]->getType())
			{
			case 1: // Input
			{
				Input* pInput = dynamic_cast<Input*>(figs[i]);
				if (pInput != NULL)
				{
					if (pInput->getNode()->IsInside(gMousePos) == true)
					{
						gConNodes[gClickCount] = pInput->getNode();

						if (gClickCount == 1)
						{
							TRACE("Input, connecting.\n");
							gWireMode = false;
							ConnectNodes();
							gClickCount = 0;
							DrawVisuals();
						}
						else
						{
							TRACE("Input\n");
							gClickCount = 1;

							// wire
							gWireMode = true;
							figs.Add(new Wire(gMousePos));
						}
						break;
					}
				}
			} break;

			case 2: // Output
			{
				Output* pOutput = dynamic_cast<Output*>(figs[i]);
				if (pOutput != NULL)
				{
					for (int j = 0; j < 8; j++)
					{
						if (pOutput->getNode(j)->IsInside(gMousePos) == true)
						{
							gConNodes[gClickCount] = pOutput->getNode(j);

							if (gClickCount == 1)
							{
								TRACE("Output [%d], connecting.\n", j);
								gWireMode = false;
								ConnectNodes();
								gClickCount = 0;
								DrawVisuals();
							}
							else
							{
								TRACE("Output [%d].\n", j);
								gClickCount = 1;

								// wire
								gWireMode = true;
								figs.Add(new Wire(gMousePos));
							}
							break;
						}
					}
				}
			} break;

			case 3: // OR_Gate
			{
				OR_Gate* pOR_Gate = dynamic_cast<OR_Gate*>(figs[i]);
				if (pOR_Gate != NULL)
				{
					for (int j = 0; j < 3; j++)
					{
						if (pOR_Gate->getNode(j)->IsInside(gMousePos) == true)
						{
							gConNodes[gClickCount] = pOR_Gate->getNode(j);

							if (gClickCount == 1)
							{
								TRACE("OR_Gate [%d], connecting.\n", j);
								gWireMode = false;
								ConnectNodes();
								gClickCount = 0;
								DrawVisuals();
							}
							else
							{
								TRACE("OR_Gate [%d].\n", j);
								gClickCount = 1;

								// wire
								gWireMode = true;
								figs.Add(new Wire(gMousePos));
							}
							break;
						}
					}
				}
			} break;

			case 4: // AND_Gate
			{
				AND_Gate* pAND_Gate = dynamic_cast<AND_Gate*>(figs[i]);
				if (pAND_Gate != NULL)
				{
					for (int j = 0; j < 3; j++)
					{
						if (pAND_Gate->getNode(j)->IsInside(gMousePos) == true)
						{
							gConNodes[gClickCount] = pAND_Gate->getNode(j);

							if (gClickCount == 1)
							{
								TRACE("AND_Gate [%d], connecting.\n", j);
								gWireMode = false;
								ConnectNodes();
								gClickCount = 0;
								DrawVisuals();
							}
							else
							{
								TRACE("AND_Gate [%d].\n", j);
								gClickCount = 1;

								// wire
								gWireMode = true;
								figs.Add(new Wire(gMousePos));
							}
							break;
						}
					}
				}
			} break;
			}
		}

		for (int i = 0; i < figs.GetCount(); i++)
		{
			Input* pInput = dynamic_cast<Input*>(figs[i]);
			if (pInput != NULL)
			{
				if (pInput->IsInside(gMousePos) == true)
				{
					pInput->ChangeState();
					DrawVisuals();
					break;
				}
			}
		}

		for (int i = 0; i < gActiveComponentsCount; i++)
			DrawVisuals();
	}

	__super::OnLButtonUp(nFlags, point);
}	