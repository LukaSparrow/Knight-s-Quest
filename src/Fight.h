#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Fight
{
public:
	Fight(float width, float height, Player* player, Player* enemy);

	int optionSelected;
	string enemyAvatarSrc;
	void draw(RenderWindow& window, Player* player, Player* enemy, Sound* sword, Sound* potion);
	void update(Player* player, Player* enemy);
	int MouseSelect(int x, int y);
	bool skip;
	Text fight[14];

	~Fight();

private:
	Font font;
	RectangleShape playerHPbar;
	RectangleShape playerHPbar2;
	RectangleShape enemyHPbar;
	RectangleShape enemyHPbar2;
};