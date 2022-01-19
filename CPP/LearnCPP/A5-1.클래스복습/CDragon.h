#pragma once

class CWeapon {
public :
	virtual void attack() = 0;
	void drop();
};

class CGun : public CWeapon
{
public:
	virtual void attack() {}
};
