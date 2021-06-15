#pragma once
#include "Visuals.h"

class Shape : public Visuals
{
	CPoint mStartPos;
	CPoint mEndPos;

public:
	// ctor
	Shape();
	Shape(const CPoint iStartPos, const CPoint iEndPos, const int iType);

	// getters
	CPoint getStartPos() const;
	CPoint getEndPos() const;

	//setters
	void setStartPos(const CPoint iStartPos);
	void setEndPos(const CPoint iEndPos);

	// methods
	void Move(const CPoint iPos);
	bool IsInside(const CPoint mousePos) const;
};