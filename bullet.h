#pragma once
class bullet
{
private:
	int x, y;
	bool shooted;

public:
	bullet();
	bullet(int, int);
	~bullet();
	void moveUp();
	int getLocationX();
	int getLocationY();
	void destroyBullet();
	bool isShooted();
};

