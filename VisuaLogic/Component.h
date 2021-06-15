#pragma once
#include "Visuals.h"
#include "Node.h"

class Component : public Visuals
{
private:
	CPoint mPos;
	bool mState;

public:
	// ctor
	Component();
	Component(const CPoint iPos, const bool iState, const int iType);

	// getters
	CPoint getPos() const;
	bool getState() const;
	
	// setters
	void setPos(const CPoint iPos);
	void setState(const bool iState);

	// virtual methods
	virtual void Draw(CDC& dc) = 0;
	virtual void Move(const CPoint iPos) = 0;
	virtual bool IsInside(const CPoint mousePos) const = 0;
};

