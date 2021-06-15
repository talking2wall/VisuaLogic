#include "pch.h"
#include "Component.h"

Component::Component(const CPoint iPos, const bool iState, const int iType) : Visuals(iType)
{
	mPos = iPos;
	mState = iState;
}

Component::Component() : Visuals(0)
{
	mPos = CPoint(0, 0);
	mState = false;
}

CPoint Component::getPos() const
{
	return mPos;
}

bool Component::getState() const
{
	return mState;
}

void Component::setPos(const CPoint iPos)
{
	mPos = iPos;
}

void Component::setState(const bool iState)
{
	mState = iState;
}