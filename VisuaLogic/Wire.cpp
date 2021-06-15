#include "pch.h"
#include "Wire.h"

Wire::Wire(const CPoint& iStartPos) : Shape(iStartPos, iStartPos, 5)
{
	// nothing to do here
}

void Wire::Draw(CDC& dc)
{
	CPoint startPos = getStartPos();
	CPoint endPos = getEndPos();

	dc.Ellipse(startPos.x - 2, startPos.y - 2, startPos.x + 2, startPos.y + 2);
	dc.MoveTo(startPos);
	dc.LineTo(endPos);
	dc.Ellipse(endPos.x - 2, endPos.y - 2, endPos.x + 2, endPos.y + 2);
}