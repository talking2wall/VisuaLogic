#pragma once
#include "Node.h"
#include "Component.h"

class AND_Gate : public Component
{
	DECLARE_SERIAL(AND_Gate)

private:
	Node* mCons[3]; // member connections

	// private method
	void computeResult();

public:
	// ctor
	AND_Gate();
	AND_Gate(const CPoint& iPos);

	// dtor
	~AND_Gate();

	// methods
	void Draw(CDC& dc);
	void Move(const CPoint iPos);
	Node* getNode(const int iNodeIndex) const;
	bool IsInside(const CPoint mousePos) const;

	// serialization
	void Serialize(CArchive& ar);
};