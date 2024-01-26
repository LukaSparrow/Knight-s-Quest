#include "GameOver.h"

GameOver::GameOver(float width, float height)
{
	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	gameOver[0].setString(L"					  Koniec gry!\nNiestety nie udało Ci się przejść do kolejnego poziomu.");
	gameOver[0].setLineSpacing(1.5);
	gameOver[0].setFont(font);
	gameOver[0].setStyle(Text::Bold);
	gameOver[0].setOutlineColor(Color::Black);
	gameOver[0].setOutlineThickness(2);
	gameOver[0].setFillColor(Color::Yellow);
	gameOver[0].setCharacterSize(50);
	FloatRect textRect = gameOver[0].getLocalBounds();
	gameOver[0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	gameOver[0].setPosition(width / 2.0f, height - 500);

	gameOver[1].setString(L"Wczytaj punkt kontrolny");
	gameOver[1].setFont(font);
	gameOver[1].setStyle(Text::Bold);
	gameOver[1].setOutlineColor(Color::Black);
	gameOver[1].setOutlineThickness(2);
	gameOver[1].setFillColor(Color::Red);
	gameOver[1].setCharacterSize(40);
	textRect = gameOver[1].getLocalBounds();
	gameOver[1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	gameOver[1].setPosition(width / 2.0f, height - 350);

	gameOver[2].setString(L"Menu główne");
	gameOver[2].setFont(font);
	gameOver[2].setStyle(Text::Bold);
	gameOver[2].setOutlineColor(Color::Black);
	gameOver[2].setOutlineThickness(2);
	gameOver[2].setFillColor(Color::White);
	gameOver[2].setCharacterSize(40);
	textRect = gameOver[2].getLocalBounds();
	gameOver[2].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	gameOver[2].setPosition(width / 2.0f, height - 275);

	optionSelected = 1;
}

GameOver::~GameOver()
{
}

void GameOver::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(gameOver[i]);
	}
}

void GameOver::MoveUp()
{
	if (optionSelected >= 0)
	{
		gameOver[optionSelected].setFillColor(Color::White);
		optionSelected--;
		if (optionSelected == 0)
		{
			optionSelected = 2;
		}
		gameOver[optionSelected].setFillColor(Color::Red);
	}
}

void GameOver::MoveDown()
{
	if (optionSelected <= 3)
	{
		gameOver[optionSelected].setFillColor(Color::White);
		optionSelected++;
		if (optionSelected == 3)
		{
			optionSelected = 1;
		}
		gameOver[optionSelected].setFillColor(Color::Red);
	}
}

int GameOver::MouseSelect(int x, int y)
{
	for (int i = 1; i < 3; i++)
	{
		if (x >= gameOver[i].getPosition().x - gameOver[i].getLocalBounds().width / 2 && x <= gameOver[i].getPosition().x + gameOver[i].getLocalBounds().width / 2 && y >= gameOver[i].getPosition().y - gameOver[i].getLocalBounds().height / 2 && y <= gameOver[i].getPosition().y + gameOver[i].getLocalBounds().height / 2)
		{
			gameOver[1].setFillColor(Color::White);
			gameOver[2].setFillColor(Color::White);
			optionSelected = i;
			gameOver[optionSelected].setFillColor(Color::Red);
			return 1;
		}
	}
	return 0;
}