#pragma once
class Node : public CObject
{
	DECLARE_SERIAL(Node)

private:
	CPoint mPos;
	bool mState = false;
	Node* mInfoNode;

public:
	// ctor
	Node();
	Node(CPoint iPos, bool iState, bool initInfoNode);

	// dtor
	~Node();

	// methods
	void Draw(CDC& dc);
	void Move(const CPoint iPos);
	bool IsInside(const CPoint mousePos);
	void ChangeState();

	// getters
	Node* getInfoNode() const;
	Node* getNode();
	bool getState() const;
	CPoint getPos() const;

	// setters
	void setState(bool iState);
	void turnOn();
	void turnOff();
	void setInfoNode(Node* iInfoNode);

	// serialization
	void Serialize(CArchive& ar);
};