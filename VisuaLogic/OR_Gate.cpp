#include "pch.h"
#include "OR_Gate.h"

IMPLEMENT_SERIAL(OR_Gate, CObject, 1)

OR_Gate::OR_Gate(const CPoint& iPos) : Component(iPos, 0, 3)
{
	setPos(iPos);
	mCons[0] = new Node(CPoint(iPos.x - 25, iPos.y - 50), 0, false);
	mCons[1] = new Node(CPoint(iPos.x + 25, iPos.y - 50), 0, false);
	mCons[2] = new Node(CPoint(iPos.x, iPos.y + 50), 0, true);
}

OR_Gate::OR_Gate() : Component(CPoint(0, 0), 0, 3)
{
	mCons[0] = new Node(CPoint(- 25, - 50), 0, false);
	mCons[1] = new Node(CPoint(25, - 50), 0, false);
	mCons[2] = new Node(CPoint(0, 50), 0, true);
}

OR_Gate::~OR_Gate()
{
	for (int i = 0; i < 3; i++)
	{
		delete mCons[i];
		mCons[i] = NULL;
	}
	delete *mCons;
	*mCons = NULL;
}

void OR_Gate::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << getPos();
		for (int i = 0; i < 3; i++)
			ar << mCons[i]->getPos();
	}
	else
	{
		CPoint pos;
		ar >> pos;
		setPos(pos);
		for (int i = 0; i < 3; i++)
		{
			ar >> pos;
			mCons[i]->Move(pos);
		}
	}
}

void OR_Gate::computeResult()
{
	if (mCons[0]->getState() == true || mCons[1]->getState() == true)
		mCons[2]->setState(true);
	else
		mCons[2]->setState(false);
}

Node* OR_Gate::getNode(const int iNodeIndex) const
{
	return mCons[iNodeIndex];
}

void OR_Gate::Draw(CDC& dc)
{
	CBrush brush;

	// update result state
	computeResult();

	// set triangle color
	if (mCons[2]->getState())
		brush.CreateSolidBrush(RGB(0, 255, 0));
	else
		brush.CreateSolidBrush(RGB(255, 0, 0));

	dc.SelectObject(brush);

	// temp position variable
	CPoint pos = getPos();

	// draw legs
	dc.MoveTo(pos.x - 25, pos.y - 25);
	dc.LineTo(pos.x - 25, pos.y - 50);
	dc.MoveTo(pos.x + 25, pos.y - 25);
	dc.LineTo(pos.x + 25, pos.y - 50);
	dc.MoveTo(pos.x, pos.y + 25);
	dc.LineTo(pos.x, pos.y + 50);

	// draw triangle
	POINT vertices[] = { {pos.x - 32, pos.y - 25}, {pos.x + 32, pos.y - 25}, {pos.x, pos.y + 25} };
	dc.Polygon(vertices, 3);

	// draw nodes
	mCons[0]->Draw(dc);
	mCons[1]->Draw(dc);
	mCons[2]->Draw(dc);
}

void OR_Gate::Move(const CPoint iPos)
{
	setPos(iPos);
	mCons[0]->Move(CPoint(iPos.x - 25, iPos.y - 50));
	mCons[1]->Move(CPoint(iPos.x + 25, iPos.y - 50));
	mCons[2]->Move(CPoint(iPos.x, iPos.y + 50));
}

bool OR_Gate::IsInside(const CPoint mousePos) const
{
	CPoint pos = getPos();
	CPoint P1(pos.x - 32, pos.y - 50);
	CPoint P2(pos.x + 32, pos.y + 50);

	if ((P1.x <= mousePos.x && mousePos.x <= P2.x || P1.x >= mousePos.x && mousePos.x >= P2.x) &&
		(P1.y <= mousePos.y && mousePos.y <= P2.y || P1.y >= mousePos.y && mousePos.y >= P2.y))
	{
		return true;
	}
	return false;
}