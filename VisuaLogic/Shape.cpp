#include "pch.h"
#include "Shape.h"

Shape::Shape() : Visuals(0)
{
	mStartPos = CPoint(0, 0);
	mEndPos = CPoint(0, 0);
}

Shape::Shape(const CPoint iStartPos, const CPoint iEndPos, const int iType) : Visuals(iType)
{
	mStartPos = iStartPos;
	mEndPos = iEndPos;
}

CPoint Shape::getStartPos() const
{
	return mStartPos;
}

CPoint Shape::getEndPos() const
{
	return mEndPos;
}

void Shape::setStartPos(const CPoint iStartPos)
{
	mStartPos = iStartPos;
}

void Shape::setEndPos(const CPoint iEndPos)
{
	mEndPos = iEndPos;
}

void Shape::Move(const CPoint iPos)
{
	mEndPos = iPos;
}

bool Shape::IsInside(const CPoint mousePos) const
{
	CPoint P1(mStartPos.x, mStartPos.y);
	CPoint P2(mEndPos.x, mEndPos.y);

	if ((P1.x <= mousePos.x && mousePos.x <= P2.x || P1.x >= mousePos.x && mousePos.x >= P2.x) &&
		(P1.y <= mousePos.y && mousePos.y <= P2.y || P1.y >= mousePos.y && mousePos.y >= P2.y))
	{
		return true;
	}
	return false;
}