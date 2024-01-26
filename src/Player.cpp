#include "Player.h"

Player::Player(float width, float height)
{

	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	player[0].setString(L"Statystyki");
	player[0].setStyle(Text::Bold);
	player[0].setFont(font);
	player[0].setFillColor(Color::Yellow);
	player[0].setOutlineColor(Color::Black);
	player[0].setOutlineThickness(1);
	player[0].setCharacterSize(40);
	FloatRect textRect = player[0].getLocalBounds();
	player[0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[0].setPosition(width / 2.0f, height - 750);

	player[11].setString(L"Ekwipunek");
	player[11].setStyle(Text::Bold);
	player[11].setFont(font);
	player[11].setFillColor(Color::Yellow);
	player[11].setOutlineColor(Color::Black);
	player[11].setOutlineThickness(1);
	player[11].setCharacterSize(40);
	textRect = player[11].getLocalBounds();
	player[11].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[11].setPosition(width / 2.0f, height - 250);

	player[1].setString(L"Punkty zdrowia: " + to_string(HP));
	player[1].setFont(font);
	player[1].setFillColor(Color::White);
	player[1].setOutlineColor(Color::Black);
	player[1].setOutlineThickness(1);
	player[1].setCharacterSize(30);
	textRect = player[1].getLocalBounds();
	player[1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[1].setPosition(width / 2.0f, height - 600);

	player[2].setString(L"Maks. zdrowie: " + to_string(maxHP));
	player[2].setFont(font);
	player[2].setFillColor(Color::White);
	player[2].setOutlineColor(Color::Black);
	player[2].setOutlineThickness(1);
	player[2].setCharacterSize(30);
	textRect = player[2].getLocalBounds();
	player[2].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[2].setPosition(width / 2.0f, height - 550);

	player[3].setString(L"Atak: " + to_string(attack));
	player[3].setFont(font);
	player[3].setFillColor(Color::White);
	player[3].setOutlineColor(Color::Black);
	player[3].setOutlineThickness(1);
	player[3].setCharacterSize(30);
	textRect = player[3].getLocalBounds();
	player[3].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[3].setPosition(width / 2.0f, height - 500);

	player[4].setString(L"Obrona: " + to_string(attack));
	player[4].setFont(font);
	player[4].setFillColor(Color::White);
	player[4].setOutlineColor(Color::Black);
	player[4].setOutlineThickness(1);
	player[4].setCharacterSize(30);
	textRect = player[4].getLocalBounds();
	player[4].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[4].setPosition(width / 2.0f, height - 450);

	player[5].setString(L"Poziom: " + to_string(level));
	player[5].setFont(font);
	player[5].setFillColor(Color::White);
	player[5].setOutlineColor(Color::Black);
	player[5].setOutlineThickness(1);
	player[5].setCharacterSize(30);
	textRect = player[5].getLocalBounds();
	player[5].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[5].setPosition(width / 2.0f, height - 400);

	player[6].setString(L"Złoto: " + to_string(gold));
	player[6].setFont(font);
	player[6].setFillColor(Color::White);
	player[6].setOutlineColor(Color::Black);
	player[6].setOutlineThickness(1);
	player[6].setCharacterSize(30);
	textRect = player[6].getLocalBounds();
	player[6].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[6].setPosition(width / 2.0f, height - 300);

	player[7].setString(L"Aktualny poziom trudności: Normalny");
	player[7].setFont(font);
	player[7].setFillColor(Color::White);
	player[7].setOutlineColor(Color::Black);
	player[7].setOutlineThickness(1);
	player[7].setCharacterSize(15);
	textRect = player[7].getLocalBounds();
	player[7].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[7].setPosition(width / 2.0f, height - 50);

	playerHPbar.setFillColor(Color::Black);
	playerHPbar.setOutlineColor(Color(50, 50, 50, 255));
	playerHPbar.setOutlineThickness(2);
	playerHPbar.setSize(Vector2f(250, 25));
	playerHPbar.setPosition(25, 250);

	playerHPbar2.setFillColor(Color::Green);
	playerHPbar2.setSize(Vector2f(250, 25));
	playerHPbar2.setPosition(25, 250);

	playerExpBar.setFillColor(Color::Black);
	playerExpBar.setOutlineColor(Color(50, 50, 50, 255));
	playerExpBar.setOutlineThickness(2);
	playerExpBar.setSize(Vector2f(250, 25));
	playerExpBar.setPosition(25, 550);

	playerExpBar2.setFillColor(Color::Yellow);
	playerExpBar2.setSize(Vector2f(250, 25));
	playerExpBar2.setPosition(25, 550);

	player[8].setFont(font);
	player[8].setStyle(Text::Bold);
	player[8].setFillColor(Color::White);
	player[8].setOutlineColor(Color::Black);
	player[8].setOutlineThickness(2);
	player[8].setCharacterSize(20);
	textRect = player[8].getLocalBounds();
	player[8].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[8].setPosition(150, 258);

	player[9].setFont(font);
	player[9].setStyle(Text::Bold);
	player[9].setFillColor(Color::White);
	player[9].setOutlineColor(Color::Black);
	player[9].setOutlineThickness(2);
	player[9].setCharacterSize(20);
	textRect = player[9].getLocalBounds();
	player[9].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[9].setPosition(150, 558);

	player[10].setFont(font);
	player[10].setFillColor(Color::White);
	player[10].setOutlineColor(Color::Black);
	player[10].setOutlineThickness(1);
	player[10].setCharacterSize(30);
	textRect = player[10].getLocalBounds();
	player[10].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	player[10].setPosition(150, 700);
}

Player::~Player()
{
}

void Player::draw(RenderWindow& window)
{
	window.draw(playerHPbar);
	window.draw(playerHPbar2);
	window.draw(playerExpBar);
	window.draw(playerExpBar2);
	for (int i = 0; i < 12; i++)
	{
		window.draw(player[i]);
	}
}

void Player::update()
{
	player[1].setString(L"Punkty zdrowia: " + to_string(HP));
	player[1].setOrigin(player[1].getLocalBounds().width / 2.0f, player[1].getLocalBounds().height / 2.0f);
	player[1].setPosition(150, 300);

	player[2].setString(L"Maks. zdrowie: " + to_string(maxHP));
	player[2].setOrigin(player[2].getLocalBounds().width / 2.0f, player[2].getLocalBounds().height / 2.0f);
	player[2].setPosition(150, 350);

	player[3].setString(L"Atak: " + to_string(attack));
	player[3].setOrigin(player[3].getLocalBounds().width / 2.0f, player[3].getLocalBounds().height / 2.0f);
	player[3].setPosition(150, 400);

	player[4].setString(L"Obrona: " + to_string(defense));
	player[4].setOrigin(player[4].getLocalBounds().width / 2.0f, player[4].getLocalBounds().height / 2.0f);
	player[4].setPosition(150, 450);

	player[5].setString(L"Poziom: " + to_string(level));
	player[5].setOrigin(player[5].getLocalBounds().width / 2.0f, player[5].getLocalBounds().height / 2.0f);
	player[5].setPosition(150, 500);

	player[6].setString(L"Złoto: " + to_string(gold));
	player[6].setOrigin(player[6].getLocalBounds().width / 2.0f, player[6].getLocalBounds().height / 2.0f);
	player[6].setPosition(150, 700);

	player[10].setString(L"Mikstury zdrowia: " + to_string(potions));
	player[10].setOrigin(player[10].getLocalBounds().width / 2.0f, player[10].getLocalBounds().height / 2.0f);
	player[10].setPosition(150, 750);

	player[7].setOrigin(player[7].getLocalBounds().width / 2.0f, player[7].getLocalBounds().height / 2.0f);
	player[7].setPosition(150, 850);

	player[8].setString(to_string(HP) + "/" + to_string(maxHP));
	player[8].setOrigin(player[8].getLocalBounds().width / 2.0f, player[8].getLocalBounds().height / 2.0f);
	player[8].setPosition(150, 258);

	player[9].setString(to_string(exp) + "/1000");
	player[9].setOrigin(player[9].getLocalBounds().width / 2.0f, player[9].getLocalBounds().height / 2.0f);
	player[9].setPosition(150, 558);

	playerHPbar2.setSize(Vector2f(((float)HP / (float)maxHP) * 250, 25));
	playerExpBar2.setSize(Vector2f((float)exp / 1000 * 250, 25));
}