#include "pch.h"
#include "Node.h"

IMPLEMENT_SERIAL(Node, CObject, 1)

Node::Node(CPoint iPos, bool iState, bool initInfoNode)
{
	mState = iState;
	mPos = iPos;

	if (initInfoNode)
		mInfoNode = this;
	else
		mInfoNode = NULL;
}

Node::Node()
{
	mPos = CPoint(0, 0);
	mState = false;
	mInfoNode = NULL;
}

Node::~Node()
{
	if (mInfoNode != NULL)
	{
		delete mInfoNode;
		mInfoNode = NULL;
	}
}

void Node::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
		ar << mPos << mState;
	else
		ar >> mPos >> mState;
}

CPoint Node::getPos() const
{
	return mPos;
}

Node* Node::getInfoNode() const
{
	return mInfoNode;
}

Node* Node::getNode()
{
	return this;
}

void Node::setState(bool iState)
{
	mState = iState;
}

void Node::setInfoNode(Node* iInfoNode)
{
	mInfoNode = iInfoNode;
	mState = iInfoNode->mState;
}

void Node::Draw(CDC& dc)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	dc.SelectObject(brush);
	dc.Rectangle(mPos.x + 4, mPos.y + 4, mPos.x - 4, mPos.y - 4);

	if (mInfoNode != NULL)
		mState = mInfoNode->mState;
}

void Node::ChangeState()
{
	mState = !mState;
}

bool Node::IsInside(const CPoint mousePos)
{
	CPoint P1(mPos.x + 2, mPos.y + 2);
	CPoint P2(mPos.x - 2, mPos.y - 2);

	if ((P1.x <= mousePos.x && mousePos.x <= P2.x || P1.x >= mousePos.x && mousePos.x >= P2.x) &&
		(P1.y <= mousePos.y && mousePos.y <= P2.y || P1.y >= mousePos.y && mousePos.y >= P2.y))
	{
		return true;
	}
	return false;
}

void Node::Move(const CPoint iPos)
{
	mPos = iPos;
}

bool Node::getState() const
{
	return mState;
}

void Node::turnOn()
{
	mState = true;
}

void Node::turnOff()
{
	mState = false;
}