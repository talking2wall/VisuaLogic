#include "pch.h"
#include "Visuals.h"

int Visuals::sCount = 0;

int Visuals::getCount()
{
	return sCount;
}

Visuals::Visuals(int iType) : mType(iType)
{
	mId = ++sCount;
}

Visuals::~Visuals()
{
	--sCount;
}

int Visuals::getId() const
{
	return mId;
}

int Visuals::getType() const
{
	return mType;
}