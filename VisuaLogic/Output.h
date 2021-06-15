#pragma once
#include "Visuals.h"
#include "Node.h"

class Output : public Visuals
{
	DECLARE_SERIAL(Output)

private:
	CPoint mPos;
	Node* cons[8];

public:
	// ctor
	Output(const CPoint iPos);
	Output();

	// dtor
	~Output();

	// getter
	Node* getNode(const int iNodeIndex) const;

	// methods
	void Draw(CDC& dc) const; // can't be const because of "Node.h" -> Draw()
	void Move(const CPoint iPos);
	bool IsInside(const CPoint mousePos) const;

	// serialization
	void Serialize(CArchive& ar);
};

