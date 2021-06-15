#include "pch.h"
#include "Recta.h"

IMPLEMENT_SERIAL(Recta, CObject, 1)

Recta::Recta(const CPoint iStartPos) : Shape(iStartPos, iStartPos, 7)
{
	// nothing to do here
}

Recta::Recta() : Shape(CPoint(0, 0), CPoint(0, 0), 7)
{
	// and also here
}

void Recta::Serialize(CArchive& ar)
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

void Recta::Draw(CDC& dc)
{
	CPen* oldPen = dc.GetCurrentPen();
	CPen linePen;
	dc.SelectStockObject(HOLLOW_BRUSH);
	linePen.CreatePen(PS_SOLID, 2, RGB(255, 150, 50));
	dc.SelectObject(linePen);

	dc.Rectangle(getStartPos().x, getStartPos().y, getEndPos().x, getEndPos().y);
	dc.SelectObject(oldPen);
}