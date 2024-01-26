#include "TwoChoice.h"

TwoChoice::TwoChoice(float width, float height)
{
	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	//Komunikat
	twoChoice[0].setString("");
	twoChoice[0].setFont(font);
	twoChoice[0].setFillColor(Color::White);
	twoChoice[0].setOutlineColor(Color::Black);
	twoChoice[0].setLineSpacing(1.2);
	twoChoice[0].setOutlineThickness(3);
	twoChoice[0].setCharacterSize(30);
	FloatRect textRect = twoChoice[0].getLocalBounds();
	twoChoice[0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	twoChoice[0].setPosition(300 + width / 2.0f, height - 700);

	//Opcja 1
	twoChoice[1].setString("");
	twoChoice[1].setFont(font);
	twoChoice[1].setFillColor(Color::Red);
	twoChoice[1].setOutlineColor(Color::Black);
	twoChoice[1].setOutlineThickness(2);
	twoChoice[1].setCharacterSize(30);
	textRect = twoChoice[1].getLocalBounds();
	twoChoice[1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	twoChoice[1].setPosition(300 + width / 2.0f, height - 250);

	//Opcja 2
	twoChoice[2].setString("");
	twoChoice[2].setFont(font);
	twoChoice[2].setFillColor(Color::White);
	twoChoice[2].setOutlineColor(Color::Black);
	twoChoice[2].setOutlineThickness(2);
	twoChoice[2].setCharacterSize(30);
	textRect = twoChoice[2].getLocalBounds();
	twoChoice[2].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	twoChoice[2].setPosition(300 + width / 2.0f, height - 200);

	optionSelected = 1;
}

TwoChoice::~TwoChoice()
{
}

void TwoChoice::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(twoChoice[i]);
	}
}

void TwoChoice::MoveUp()
{
	if (optionSelected >= 1)
	{
		twoChoice[optionSelected].setFillColor(Color::White);
		optionSelected--;
		if (optionSelected == 0)
		{
			optionSelected = 2;
		}
		twoChoice[optionSelected].setFillColor(Color::Red);
	}
}

void TwoChoice::MoveDown()
{
	if (optionSelected <= 2)
	{
		twoChoice[optionSelected].setFillColor(Color::White);
		optionSelected++;
		if (optionSelected == 3)
		{
			optionSelected = 1;
		}
		twoChoice[optionSelected].setFillColor(Color::Red);
	}
}

int TwoChoice::MouseSelect(int x, int y)
{
	for (int i = 1; i < 3; i++)
	{
		if (x >= twoChoice[i].getPosition().x - twoChoice[i].getLocalBounds().width / 2.0f && x <= twoChoice[i].getPosition().x + twoChoice[i].getLocalBounds().width / 2.0f && y >= twoChoice[i].getPosition().y - twoChoice[i].getLocalBounds().height / 2.0f && y <= twoChoice[i].getPosition().y + twoChoice[i].getLocalBounds().height / 2.0f)
		{
			twoChoice[1].setFillColor(Color::White);
			twoChoice[2].setFillColor(Color::White);
			optionSelected = i;
			twoChoice[optionSelected].setFillColor(Color::Red);
			return 1;
		}
	}
	return 0;
}