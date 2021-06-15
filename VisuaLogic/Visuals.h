#pragma once
class Visuals : public CObject
{
public:
	// visuals counter
	static int sCount;
	static int getCount();

	// getter
	int getId() const;
	int getType() const;

	// ctor
	Visuals(int iType);
	~Visuals();
	
private:
	int mId;
	const int mType;
};