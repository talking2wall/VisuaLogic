#pragma once
#include "Shape.h"

class Recta : public Shape
{
	DECLARE_SERIAL(Recta)

public:
	// ctor
	Recta();
	Recta(const CPoint iPos);

	// method
	void Draw(CDC& dc);

	// serialization
	void Serialize(CArchive& ar);
};