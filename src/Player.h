#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Player
{
public:
	Player(float width, float height);

	int progress;
	int difficulty;
	int attack;
	int defense;
	int maxHP;
	int HP;
	int gold;
	int exp;
	int level;
	int opt;
	int goldFound;
	int expEarned;
	int potions;

	void draw(RenderWindow& window);
	void update();
	Text player[12];

	~Player();

private:
	RectangleShape playerHPbar;
	RectangleShape playerHPbar2;
	RectangleShape playerExpBar;
	RectangleShape playerExpBar2;
	Font font;
};