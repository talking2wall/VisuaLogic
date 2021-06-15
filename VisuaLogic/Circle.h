#pragma once
#include "Shape.h"

class Circle : public Shape
{
	DECLARE_SERIAL(Circle)

public:
	// ctor
	Circle();
	Circle(const CPoint iPos);

	// method
	void Draw(CDC& dc);

	// serialization
	void Serialize(CArchive& ar);
};