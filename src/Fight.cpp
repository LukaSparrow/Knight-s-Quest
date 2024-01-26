#include "Fight.h"
#include <chrono>
#include <math.h>
#include <thread>
#include <time.h>

Fight::Fight(float width, float height, Player* player, Player* enemy)
{
	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	fight[0].setString(L"Pomiń");
	fight[0].setFont(font);
	fight[0].setFillColor(Color::Red);
	fight[0].setOutlineColor(Color::Black);
	fight[0].setOutlineThickness(2);
	fight[0].setCharacterSize(30);
	FloatRect textRect = fight[0].getLocalBounds();
	fight[0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[0].setPosition(width / 2.0f, height - 200);

	fight[1].setString("Gracz (Poziom: " + to_string(player->level) + ")");
	fight[1].setFont(font);
	fight[1].setFillColor(Color::Red);
	fight[1].setOutlineColor(Color::Black);
	fight[1].setOutlineThickness(2);
	fight[1].setCharacterSize(30);
	textRect = fight[1].getLocalBounds();
	fight[1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[1].setPosition(width / 4.0f, height - 200);

	fight[2].setString("Zdrowie: " + to_string(player->HP) + "/" + to_string(player->maxHP));
	fight[2].setFont(font);
	fight[2].setFillColor(Color::Red);
	fight[2].setOutlineColor(Color::Black);
	fight[2].setOutlineThickness(2);
	fight[2].setCharacterSize(30);
	textRect = fight[2].getLocalBounds();
	fight[2].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[2].setPosition(width / 4.0f, height - 200);

	fight[3].setString("Atak: " + to_string(player->attack));
	fight[3].setFont(font);
	fight[3].setFillColor(Color::Red);
	fight[3].setOutlineColor(Color::Black);
	fight[3].setOutlineThickness(2);
	fight[3].setCharacterSize(30);
	textRect = fight[3].getLocalBounds();
	fight[3].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[3].setPosition(width / 4.0f, height - 200);

	fight[4].setString("Obrona: " + to_string(player->defense));
	fight[4].setFont(font);
	fight[4].setFillColor(Color::Red);
	fight[4].setOutlineColor(Color::Black);
	fight[4].setOutlineThickness(2);
	fight[4].setCharacterSize(30);
	textRect = fight[4].getLocalBounds();
	fight[4].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[4].setPosition(width / 4.0f, height - 200);

	fight[5].setString("Przeciwnik (Poziom: " + to_string(enemy->level) + ")");
	fight[5].setFont(font);
	fight[5].setFillColor(Color::Red);
	fight[5].setOutlineColor(Color::Black);
	fight[5].setOutlineThickness(2);
	fight[5].setCharacterSize(30);
	textRect = fight[5].getLocalBounds();
	fight[5].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[5].setPosition(width / 4.0f, height - 200);

	fight[6].setString("Zdrowie: " + to_string(enemy->HP) + "/" + to_string(enemy->maxHP));
	fight[6].setFont(font);
	fight[6].setFillColor(Color::Red);
	fight[6].setOutlineColor(Color::Black);
	fight[6].setOutlineThickness(2);
	fight[6].setCharacterSize(30);
	textRect = fight[6].getLocalBounds();
	fight[6].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[6].setPosition(width / 4.0f, height - 200);

	fight[7].setString("Atak: " + to_string(enemy->attack));
	fight[7].setFont(font);
	fight[7].setFillColor(Color::Red);
	fight[7].setOutlineColor(Color::Black);
	fight[7].setOutlineThickness(2);
	fight[7].setCharacterSize(30);
	textRect = fight[7].getLocalBounds();
	fight[7].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[7].setPosition(width / 4.0f, height - 200);

	fight[8].setString("Obrona: " + to_string(enemy->defense));
	fight[8].setFont(font);
	fight[8].setFillColor(Color::Red);
	fight[8].setOutlineColor(Color::Black);
	fight[8].setOutlineThickness(2);
	fight[8].setCharacterSize(30);
	textRect = fight[8].getLocalBounds();
	fight[8].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[8].setPosition(width / 4.0f, height - 200);

	fight[9].setFont(font);
	fight[9].setCharacterSize(30);

	fight[10].setFont(font);
	fight[10].setCharacterSize(30);

	fight[11].setString("");
	fight[11].setFont(font);
	fight[11].setCharacterSize(50);
	fight[11].setFillColor(Color::Yellow);
	fight[11].setOutlineColor(Color::Black);
	fight[11].setOutlineThickness(2);

	fight[12].setFont(font);
	fight[12].setCharacterSize(30);

	fight[13].setString("Mikstury zdrowia: " + to_string(player->potions));
	fight[13].setFont(font);
	fight[13].setFillColor(Color::Red);
	fight[13].setOutlineColor(Color::Black);
	fight[13].setOutlineThickness(2);
	fight[13].setCharacterSize(30);
	textRect = fight[13].getLocalBounds();
	fight[13].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	fight[13].setPosition(width / 4.0f, 675);

	optionSelected = 0;

	playerHPbar.setFillColor(Color::Black);
	playerHPbar.setOutlineColor(Color(50, 50, 50, 255));
	playerHPbar.setOutlineThickness(2);
	playerHPbar.setSize(Vector2f(400, 50));
	playerHPbar.setPosition(200, 510);

	playerHPbar2.setFillColor(Color::Green);
	playerHPbar2.setOutlineColor(Color(52, 128, 50, 255));
	playerHPbar2.setOutlineThickness(-2);
	playerHPbar2.setSize(Vector2f(400, 50));
	playerHPbar2.setPosition(200, 510);

	enemyHPbar.setFillColor(Color::Black);
	enemyHPbar.setOutlineColor(Color(50, 50, 50, 255));
	enemyHPbar.setOutlineThickness(2);
	enemyHPbar.setSize(Vector2f(400, 50));
	enemyHPbar.setPosition(1000, 510);

	enemyHPbar2.setFillColor(Color::Green);
	enemyHPbar2.setOutlineColor(Color(52, 128, 50, 255));
	enemyHPbar2.setOutlineThickness(-2);
	enemyHPbar2.setSize(Vector2f(400, 50));
	enemyHPbar2.setPosition(1000, 510);
}

Fight::~Fight()
{
}

void Fight::update(Player* player, Player* enemy)
{
	fight[1].setString("Gracz (Poziom: " + to_string(player->level) + ")");
	fight[2].setString("Zdrowie: " + to_string(player->HP) + "/" + to_string(player->maxHP));
	fight[3].setString("Atak: " + to_string(player->attack));
	fight[4].setString("Obrona: " + to_string(player->defense));
	fight[13].setString("Mikstury Zdrowia: " + to_string(player->potions));
	fight[6].setString("Zdrowie: " + to_string(enemy->HP) + "/" + to_string(enemy->maxHP));
	fight[7].setString("Atak: " + to_string(enemy->attack));
	fight[8].setString("Obrona: " + to_string(enemy->defense));
	playerHPbar2.setSize(Vector2f(400, 50));
	enemyHPbar2.setSize(Vector2f(400, 50));
}

void Fight::draw(RenderWindow& window, Player* player, Player* enemy, Sound* sword, Sound* potion)
{
	srand((unsigned)time(NULL));
	int dmg;
	//rysowanie statystyk
	int x = 1;
	for (int i = 1; i < 5; i++)
	{
		fight[i].setOrigin(fight[i].getGlobalBounds().width / 2.0f, fight[i].getGlobalBounds().height / 2.0f);
		fight[i].setPosition(1600 / 4.0f, 900 - 475 + x * 50);

		x++;
		if (i != 2)
			window.draw(fight[i]);
	}
	x = 1;
	for (int i = 5; i < 9; i++)
	{
		fight[i].setOrigin(fight[i].getGlobalBounds().width / 2.0f, fight[i].getGlobalBounds().height / 2.0f);
		fight[i].setPosition(1600 - 1600 / 4.0f, 900 - 475 + x * 50);
		x++;
		if (i != 6)
			window.draw(fight[i]);
	}
	window.draw(fight[0]);
	window.draw(fight[13]);
	//walka
	if (player->HP > 0 && enemy->HP > 0)
	{
		if (!skip)
		{
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		else
		{
			this_thread::sleep_for(chrono::milliseconds(150));
		}
		fight[9].setFillColor(Color::White);
		int dodge;
		int r = (rand() % 2) + 1;
		if (player->difficulty > 0)
		{
			//cios gracza
			dodge = rand() % 6;
			r = (rand() % 2) + 2;
			if (dodge) // bez uniku
			{
				dmg = (player->attack / 2 * r - enemy->defense / 4 - player->difficulty * enemy->level + player->level);
				if (dmg <= 0)
				{
					dmg = 1;
				}
				enemy->HP -= dmg;
				fight[9].setString("-" + to_string(dmg));
				fight[9].setOrigin(fight[9].getLocalBounds().width / 2.0f, fight[9].getLocalBounds().height / 2.0f);
				fight[9].setPosition(1200, 350);
				window.draw(fight[9]);
				fight[9].setFillColor(Color::Transparent);
				window.draw(fight[9]);
				if (!skip)
				{
					sword->play();
				}
				this->update(player, enemy);
				if (((float)enemy->HP / (float)enemy->maxHP) * 400 <= 0)
				{
					enemyHPbar2.setSize(Vector2f(0, 50));
				}
				else
				{
					enemyHPbar2.setSize(Vector2f(((float)enemy->HP / (float)enemy->maxHP) * 400, 50));
				}
				window.draw(enemyHPbar);
				window.draw(enemyHPbar2);
				window.draw(fight[6]);
			}
			else
			{
				fight[9].setString("Unik!");
				fight[9].setOrigin(fight[9].getLocalBounds().width / 2.0f, fight[9].getLocalBounds().height / 2.0f);
				fight[9].setPosition(1200, 350);
				window.draw(fight[9]);
				fight[9].setFillColor(Color::Transparent);
				window.draw(fight[9]);
				window.draw(enemyHPbar);
				enemyHPbar2.setSize(Vector2f(((float)enemy->HP / (float)enemy->maxHP) * 400, 50));
				window.draw(enemyHPbar2);
				window.draw(fight[6]);
			}
		}
		else
		{
			dmg = (player->attack / 2 * r - enemy->defense / 4 - player->difficulty * enemy->level + player->level);
			if (dmg <= 0)
			{
				dmg = 1;
			}
			enemy->HP -= dmg;
			fight[9].setString("-" + to_string(dmg));
			fight[9].setOrigin(fight[9].getLocalBounds().width / 2.0f, fight[9].getLocalBounds().height / 2.0f);
			fight[9].setPosition(1200, 350);
			window.draw(fight[9]);
			fight[9].setFillColor(Color::Transparent);
			window.draw(fight[9]);
			if (!skip)
			{
				sword->play();
			}
			this->update(player, enemy);
			if (((float)enemy->HP / (float)enemy->maxHP) * 400 <= 0)
			{
				enemyHPbar2.setSize(Vector2f(0, 50));
			}
			else
			{
				enemyHPbar2.setSize(Vector2f(((float)enemy->HP / (float)enemy->maxHP) * 400, 50));
			}
			window.draw(enemyHPbar);
			window.draw(enemyHPbar2);
			window.draw(fight[6]);
		}

		// czy przeciwnik zginął po ciosie?
		if (enemy->HP <= 0)
			return;

		// cios przeciwnika
		fight[10].setFillColor(Color::White);
		dodge = rand() % 4;
		r = (rand() % 2) + 1;
		if (dodge)
		{
			dmg = (enemy->attack / 2 * r - player->defense / 4 + player->difficulty * enemy->level);
			if (dmg <= 0)
			{
				dmg = 1;
			}
			player->HP -= dmg;
			if (player->HP <= 0 && player->potions > 0)
			{
				if (!skip)
				{
					potion->play();
				}
				player->HP += player->maxHP / 2;
				player->potions--;
				fight[12].setFillColor(Color(62, 175, 20, 255));
				fight[12].setString("+" + to_string(player->maxHP / 2));
				fight[12].setOrigin(fight[12].getLocalBounds().width / 2.0f, fight[12].getLocalBounds().height / 2.0f);
				fight[12].setPosition(400, 320);
				window.draw(fight[12]);
				fight[12].setFillColor(Color::Transparent);
				window.draw(fight[12]);
			}
			fight[10].setString("-" + to_string(dmg));
			fight[10].setOrigin(fight[10].getLocalBounds().width / 2.0f, fight[10].getLocalBounds().height / 2.0f);
			fight[10].setPosition(400, 350);
			window.draw(fight[10]);
			fight[10].setFillColor(Color::Transparent);
			window.draw(fight[10]);
			if (!skip)
			{
				sword->play();
			}
			this->update(player, enemy);
			if (((float)player->HP / (float)player->maxHP) * 400 <= 0)
			{
				playerHPbar2.setSize(Vector2f(0, 50));
			}
			else
			{
				playerHPbar2.setSize(Vector2f(((float)player->HP / (float)player->maxHP) * 400, 50));
			}
			window.draw(playerHPbar);
			window.draw(playerHPbar2);
			window.draw(fight[2]);
		}
		else
		{
			fight[10].setString("Unik!");
			fight[10].setOrigin(fight[10].getLocalBounds().width / 2.0f, fight[10].getLocalBounds().height / 2.0f);
			fight[10].setPosition(400, 350);
			window.draw(fight[10]);
			fight[10].setFillColor(Color::Transparent);
			window.draw(fight[10]);
			window.draw(playerHPbar);
			playerHPbar2.setSize(Vector2f(((float)player->HP / (float)player->maxHP) * 400, 50));
			window.draw(playerHPbar2);
			window.draw(fight[2]);
		}
	}
	else
	{
		window.draw(enemyHPbar);
		if (((float)enemy->HP / (float)enemy->maxHP) * 400 <= 0)
		{
			enemyHPbar2.setSize(Vector2f(0, 50));
			enemyHPbar2.setOutlineThickness(0);
		}
		else
		{
			enemyHPbar2.setSize(Vector2f(((float)enemy->HP / (float)enemy->maxHP) * 400, 50));
		}
		window.draw(enemyHPbar2);
		window.draw(fight[6]);
		window.draw(playerHPbar);
		if (((float)player->HP / (float)player->maxHP) * 400 <= 0)
		{
			playerHPbar2.setSize(Vector2f(0, 50));
			playerHPbar2.setOutlineThickness(0);
		}
		else
		{
			playerHPbar2.setSize(Vector2f(((float)player->HP / (float)player->maxHP) * 400, 50));
		}
		window.draw(playerHPbar2);
		window.draw(fight[2]);

		fight[0].setString("Kontynuuj");
		fight[0].setOrigin(fight[0].getLocalBounds().width / 2.0f, fight[0].getLocalBounds().height / 2.0f);
		fight[0].setPosition(800, 700);
		if (player->HP <= 0)
		{
			fight[11].setString(L"Porażka!");
		}
		else
		{
			fight[11].setString(L"Zwycięstwo!");
		}
		fight[11].setOrigin(fight[11].getLocalBounds().width / 2.0f, fight[11].getLocalBounds().height / 2.0f);
		fight[11].setPosition(800, 250);
		window.draw(fight[11]);
	}
}

int Fight::MouseSelect(int x, int y)
{
	if (x >= fight[0].getPosition().x - fight[0].getLocalBounds().width / 2.0f && x <= fight[0].getPosition().x + fight[0].getLocalBounds().width / 2.0f && y >= fight[0].getPosition().y - fight[0].getLocalBounds().height / 2.0f && y <= fight[0].getPosition().y + fight[0].getLocalBounds().height / 2.0f)
	{
		return 1;
	}
	return 0;
}