#include "pch.h"
#include "Visuals.h"
#include "Node.h"
#include "Input.h"

IMPLEMENT_SERIAL(Input, CObject, 1)

Input::Input(CPoint iPos, bool iState) : Visuals(1)
{
	mPos = iPos;
	mNode = new Node(iPos, iState, true);
}

Input::Input() : Visuals(1)
{
	mPos = CPoint(0, 0);
	mNode = new Node(CPoint(0, 25), 1, true);
}

Input::~Input()
{
	if (mNode != NULL)
	{
		delete mNode;
		mNode = NULL;
	}
}

void Input::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPos << mNode->getState();
	}
	else
	{
		bool iState;
		ar >> mPos >> iState;
		mNode->setState(iState);
		mNode->Move(CPoint(mPos.x, mPos.y + 25));
	}
}

Node* Input::getNode() const
{
	return mNode;
}

void Input::ChangeState()
{
	mNode->ChangeState();
}

bool Input::IsInside(const CPoint mousePos) const
{
	CPoint P1(mPos.x + 15, mPos.y + 15);
	CPoint P2(mPos.x - 15, mPos.y - 15);

	if ((P1.x <= mousePos.x && mousePos.x <= P2.x || P1.x >= mousePos.x && mousePos.x >= P2.x) &&
		(P1.y <= mousePos.y && mousePos.y <= P2.y || P1.y >= mousePos.y && mousePos.y >= P2.y))
	{
		return true;
	}
	return false;
}

void Input::Draw(CDC& dc)
{
	CBrush brush;

	// draw line
	dc.MoveTo(mPos.x, mPos.y);
	dc.LineTo(mPos.x, mPos.y + 25);

	if (mNode->getState())
		brush.CreateSolidBrush(RGB(0, 255, 0));
	else
		brush.CreateSolidBrush(RGB(255, 0, 0));

	dc.SelectObject(brush);
	dc.Ellipse(mPos.x - 15, mPos.y - 15, mPos.x + 15, mPos.y + 15);

	mNode->Draw(dc); // draw base node
}

void Input::Move(const CPoint iPos)
{
	mPos = iPos;
	mNode->Move(CPoint(iPos.x, iPos.y + 25)); // move base node
}