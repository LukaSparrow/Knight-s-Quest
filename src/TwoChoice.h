#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class TwoChoice
{
public:
	TwoChoice(float width, float height);

	int optionSelected;
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int MouseSelect(int x, int y);
	Text twoChoice[3];

	~TwoChoice();

private:
	Font font;
};