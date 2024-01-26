#include "Options.h"

Options::Options(float width, float height)
{

	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	//Fullscreen?
	options[0][0].setFont(font);
	options[0][0].setStyle(Text::Bold);
	options[0][0].setOutlineColor(Color::Black);
	options[0][0].setOutlineThickness(2);
	options[0][0].setFillColor(Color::Yellow);
	options[0][0].setString(L"Dźwięk");
	options[0][0].setCharacterSize(40);
	FloatRect textRect = options[0][0].getLocalBounds();
	options[0][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[0][0].setPosition(width / 2.0f, height - 700);

	options[1][0].setFont(font);
	options[1][0].setStyle(Text::Bold);
	options[1][0].setOutlineColor(Color::Black);
	options[1][0].setOutlineThickness(1);
	options[1][0].setFillColor(Color::Red);
	options[1][0].setString(L"Włączony");
	options[1][0].setCharacterSize(30);
	textRect = options[1][0].getLocalBounds();
	options[1][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[1][0].setPosition(width / 2.0f - 100, height - 600);

	options[1][1].setFont(font);
	options[1][1].setStyle(Text::Bold);
	options[1][1].setOutlineColor(Color::Black);
	options[1][1].setOutlineThickness(1);
	options[1][1].setFillColor(Color::White);
	options[1][1].setString(L"Wyłączony");
	options[1][1].setCharacterSize(30);
	textRect = options[1][1].getLocalBounds();
	options[1][1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[1][1].setPosition(width / 2.0f + 100, height - 600);
	//Fullscreen?

	//Difficulty?
	options[2][0].setFont(font);
	options[2][0].setStyle(Text::Bold);
	options[2][0].setFillColor(Color::Yellow);
	options[2][0].setOutlineColor(Color::Black);
	options[2][0].setOutlineThickness(2);
	options[2][0].setString(L"Poziom trudności");
	options[2][0].setCharacterSize(40);
	textRect = options[2][0].getLocalBounds();
	options[2][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[2][0].setPosition(width / 2.0f, height - 500);

	options[3][0].setFont(font);
	options[3][0].setStyle(Text::Bold);
	options[3][0].setFillColor(Color::White);
	options[3][0].setOutlineColor(Color::Black);
	options[3][0].setOutlineThickness(1);
	options[3][0].setString(L"Łatwy");
	options[3][0].setCharacterSize(30);
	textRect = options[3][0].getLocalBounds();
	options[3][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[3][0].setPosition(width / 2.0f - 150, height - 400);

	options[3][1].setFont(font);
	options[3][1].setStyle(Text::Bold);
	options[3][1].setFillColor(Color::White);
	options[3][1].setOutlineColor(Color::Black);
	options[3][1].setOutlineThickness(1);
	options[3][1].setString("Normalny");
	options[3][1].setCharacterSize(30);
	textRect = options[3][1].getLocalBounds();
	options[3][1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[3][1].setPosition(width / 2.0f, height - 400);

	options[3][2].setFont(font);
	options[3][2].setStyle(Text::Bold);
	options[3][2].setFillColor(Color::White);
	options[3][2].setOutlineColor(Color::Black);
	options[3][2].setOutlineThickness(1);
	options[3][2].setString("Trudny");
	options[3][2].setCharacterSize(30);
	textRect = options[3][2].getLocalBounds();
	options[3][2].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[3][2].setPosition(width / 2.0f + 150, height - 400);
	//Difficulty?

	//Apply? //Return?
	options[4][0].setFont(font);
	options[4][0].setStyle(Text::Bold);
	options[4][0].setFillColor(Color::Yellow);
	options[4][0].setOutlineColor(Color::Black);
	options[4][0].setOutlineThickness(2);
	options[4][0].setString("Wstecz");
	options[4][0].setCharacterSize(30);
	textRect = options[4][0].getLocalBounds();
	options[4][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	options[4][0].setPosition(width / 2.0f, height - 300);

	string diff = "Normalny";
	currentDifficulty.setString(L"Aktualny poziom trudności: " + diff);
	currentDifficulty.setFont(font);
	currentDifficulty.setStyle(Text::Bold);
	currentDifficulty.setFillColor(Color::Yellow);
	currentDifficulty.setOutlineColor(Color::Black);
	currentDifficulty.setOutlineThickness(1);
	currentDifficulty.setCharacterSize(15);
	textRect = currentDifficulty.getLocalBounds();
	currentDifficulty.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	currentDifficulty.setPosition(width / 2.0f, height - 100);

	currentSound.setString(L"Aktualny stan dźwięku: Włączony");
	currentSound.setFont(font);
	currentSound.setStyle(Text::Bold);
	currentSound.setFillColor(Color::Yellow);
	currentSound.setOutlineColor(Color::Black);
	currentSound.setOutlineThickness(1);
	currentSound.setCharacterSize(15);
	textRect = currentSound.getLocalBounds();
	currentSound.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	currentSound.setPosition(width / 2.0f, height - 80);

	optionSelected = 1;
	valueSelected = 0;
}

Options::~Options()
{
}

void Options::difficultyUpdate(const wchar_t* diff)
{
	currentDifficulty.setString(diff);
}

void Options::soundUpdate(const wchar_t* snd)
{
	currentSound.setString(snd);
}

void Options::draw(RenderWindow& window)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			window.draw(options[i][j]);
		}
	}
	window.draw(currentDifficulty);
	window.draw(currentSound);
}

void Options::MoveUp()
{
	if (optionSelected >= 1)
	{
		if (optionSelected == 4)
		{
			options[optionSelected][valueSelected].setFillColor(Color::Yellow);
		}
		else
		{
			options[optionSelected][valueSelected].setFillColor(Color::White);
		}
		if (optionSelected == 3 && valueSelected == 2)
		{
			valueSelected = 1;
		}
		if (optionSelected == 4)
		{
			optionSelected--;
		}
		else
		{
			optionSelected -= 2;
		}
		if (optionSelected <= -1)
		{
			optionSelected = 4;
		}
		options[optionSelected][valueSelected].setFillColor(Color::Red);
	}
}

void Options::MoveDown()
{
	if (optionSelected <= 4)
	{
		if (optionSelected == 4)
		{
			options[optionSelected][valueSelected].setFillColor(Color::Yellow);
		}
		else
		{
			options[optionSelected][valueSelected].setFillColor(Color::White);
		}
		if (optionSelected == 3 && (valueSelected == 2 || valueSelected == 1))
		{
			valueSelected = 0;
		}
		if (optionSelected == 3)
		{
			optionSelected++;
		}
		else
		{
			optionSelected += 2;
		}
		if (optionSelected >= 5)
		{
			optionSelected = 1;
		}
		options[optionSelected][valueSelected].setFillColor(Color::Red);
	}
}

void Options::MoveSide(String side)
{
	switch (optionSelected)
	{
		case 1:
			if (valueSelected <= 1)
			{
				options[optionSelected][valueSelected].setFillColor(Color::White);
				if (valueSelected == 0)
				{
					valueSelected = 1;
				}
				else
				{
					valueSelected = 0;
				}
				options[optionSelected][valueSelected].setFillColor(Color::Red);
			}
			break;
		case 3:
			if (valueSelected <= 2)
			{
				options[optionSelected][valueSelected].setFillColor(Color::White);
				if (side == "right")
				{
					valueSelected++;
				}
				else
				{
					valueSelected--;
				}
				if (valueSelected == 3)
				{
					valueSelected = 0;
				}
				if (valueSelected == -1)
				{
					valueSelected = 2;
				}
				options[optionSelected][valueSelected].setFillColor(Color::Red);
			}
			break;
		case 4:
			valueSelected = 0;
		default: break;
	}
}

int Options::MouseSelect(int x, int y)
{
	int correction = 15;
	if (x > correction && y > correction)
	{
		for (int i = 1; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != 2)
				{
					if (x >= options[i][j].getPosition().x - options[i][j].getLocalBounds().width / 2 - correction && x <= options[i][j].getPosition().x + options[i][j].getLocalBounds().width / 2 + correction && y >= options[i][j].getPosition().y - options[i][j].getLocalBounds().height / 2 - correction && y <= options[i][j].getPosition().y + options[i][j].getLocalBounds().height / 2 + correction)
					{
						options[1][0].setFillColor(Color::White);
						options[1][1].setFillColor(Color::White);
						options[3][0].setFillColor(Color::White);
						options[3][1].setFillColor(Color::White);
						options[3][2].setFillColor(Color::White);
						options[4][0].setFillColor(Color::Yellow);
						optionSelected = i;
						valueSelected = j;
						options[optionSelected][valueSelected].setFillColor(Color::Red);
						return 1;
					}
				}
			}
		}
		return 0;
	}
	return 0;
}
