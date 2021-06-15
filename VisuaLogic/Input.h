#pragma once
#include "Visuals.h"
#include "Node.h"

class Input : public Visuals
{
	DECLARE_SERIAL(Input)

private:
	CPoint mPos;
	Node* mNode;

public:
	// ctor
	Input();
	Input(CPoint iPos, bool iState);

	// dtor
	~Input();
	
	// getter
	Node* getNode() const;

	// setter
	void ChangeState();

	// methods
	void Draw(CDC& dc);
	void Move(const CPoint iPos);
	bool IsInside(const CPoint mousePos) const;

	// serialization
	void Serialize(CArchive& ar);
};

