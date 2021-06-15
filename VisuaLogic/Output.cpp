#include "pch.h"
#include "Output.h"

IMPLEMENT_SERIAL(Output, CObject, 1)

Output::Output(const CPoint iPos) : Visuals(2)
{
	mPos = iPos;

	for (int i = 0; i < 8; i++)
		cons[i] = new Node(CPoint(iPos.x - (i * 25), iPos.y), 0, false);
}

Output::Output() : Visuals(2)
{
	mPos = CPoint(0, 0);

	for (int i = 0; i < 8; i++)
		cons[i] = new Node(CPoint(mPos.x - (i * 25), mPos.y), 0, false);
}

Output::~Output()
{
	for (int i = 0; i < 8; i++)
	{
		delete cons[i];
		cons[i] = NULL;
	}
}

void Output::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPos;
		for (int i = 0; i < 8; i++)
			ar << cons[i]->getPos();
	}
	else
	{
		CPoint iPos;
		ar >> mPos;
		for (int i = 0; i < 8; i++)
		{
			ar >> iPos;
			cons[i]->Move(iPos);
		}
	}
}

bool Output::IsInside(const CPoint mousePos) const
{
	CPoint P1(mPos.x - 200, mPos.y + 50);
	CPoint P2(mPos.x + 25, mPos.y);

	if ((P1.x <= mousePos.x && mousePos.x <= P2.x || P1.x >= mousePos.x && mousePos.x >= P2.x) &&
		(P1.y <= mousePos.y && mousePos.y <= P2.y || P1.y >= mousePos.y && mousePos.y >= P2.y))
	{
		return true;
	}
	return false;
}

Node* Output::getNode(const int iNodeIndex) const
{
	return cons[iNodeIndex];
}

void Output::Draw(CDC& dc) const
{
	CBrush brush;
	CRect rect(mPos.x - 200, mPos.y + 50, mPos.x + 25, mPos.y);
	brush.CreateSolidBrush(RGB(200, 200, 200));
	dc.SelectObject(brush);
	dc.Rectangle(rect);

	int result = 0;
	int pow = 1;

	// must draw nodes first - because updates in state occurs in Draw()
	for (int i = 0; i < 8; i++)
		cons[i]->Draw(dc);

	for (int i = 0; i < 8; i++)
	{
		if (cons[i]->getState() == true)
			result += pow;

		pow *= 2;
	}

	CString str;
	str.Format(L"%3d", result);
	dc.DrawText(str, 3, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Output::Move(const CPoint iPos)
{
	mPos = iPos;

	for (int i = 0; i < 8; i++)
		cons[i]->Move(CPoint(iPos.x - (i * 25), iPos.y));
}