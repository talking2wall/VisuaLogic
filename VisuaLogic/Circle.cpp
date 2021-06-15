#include "pch.h"
#include "Circle.h"

IMPLEMENT_SERIAL(Circle, CObject, 1)

Circle::Circle(const CPoint iStartPos) : Shape(iStartPos, iStartPos, 6)
{
	// nothing to do here
}

Circle::Circle() : Shape(CPoint(0, 0), CPoint(0, 0), 6)
{
	// and also here
}

void Circle::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << getStartPos() << getEndPos();
	}
	else
	{
		CPoint pos;
		ar >> pos;
		setStartPos(pos);
		ar >> pos;
		setEndPos(pos);
	}
}

void Circle::Draw(CDC& dc)
{
	CPen* oldPen = dc.GetCurrentPen();
	CPen linePen;
	dc.SelectStockObject(HOLLOW_BRUSH);
	linePen.CreatePen(PS_SOLID, 2, RGB(255, 150, 50));
	dc.SelectObject(linePen);
	
	dc.Ellipse(getStartPos().x, getStartPos().y, getEndPos().x, getEndPos().y);
	dc.SelectObject(oldPen);
}