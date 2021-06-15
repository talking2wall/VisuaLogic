#pragma once
#include "Node.h"
#include "Component.h"

class OR_Gate : public Component
{
	DECLARE_SERIAL(OR_Gate)

private:
	Node* mCons[3]; // member connections
	
	// private method
	void computeResult();

public:
	// ctor
	OR_Gate();
	OR_Gate(const CPoint& iPos);

	// dtor
	~OR_Gate();

	// methods
	void Draw(CDC& dc);
	void Move(const CPoint iPos);
	Node* getNode(const int iNodeIndex) const;
	bool IsInside(const CPoint mousePos) const;

	// serialization
	void Serialize(CArchive& ar);
};