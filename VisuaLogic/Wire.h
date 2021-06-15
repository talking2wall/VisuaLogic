#pragma once
#include "Shape.h"

class Wire : public Shape
{
public:
	// ctor
	Wire(const CPoint& iStartPos);

	// method
	void Draw(CDC& dc);
};