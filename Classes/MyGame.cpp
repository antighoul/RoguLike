#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Camera.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "RogueLike");
	view.reset(FloatRect(0, 0, 640, 480));
	string f = "Hero.png";
	string fileMap = "gamedev\\map.png";

	float currentframe = 0;

	
	Texture mainMAP;
	mainMAP.loadFromFile(fileMap);
	Sprite map;
	map.setTexture(mainMAP);	


	Player p(f,0,0,43.16,86.375);

	Clock clock; // Привязка ко времени , а не к процессору
	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();//задаём прошедшее время в микросекундах
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.direction = 0; p.speed = 0.1;
			currentframe += 0.005;
			if (currentframe > 3)currentframe -= 3;
			p.sprite.setTextureRect(IntRect(43.16 * int(currentframe), 86.375, 43.16, 86.375));
			GetPlayerCoordingateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		};
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.direction = 1; p.speed = 0.1;
			currentframe += 0.005;
			if (currentframe > 3)currentframe -= 3;
			p.sprite.setTextureRect(IntRect(43.16 * int(currentframe), 172.75, 43.16, 86.375));
			GetPlayerCoordingateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p.direction = 2; p.speed = 0.1;
			currentframe += 0.005;
			if (currentframe > 3)currentframe -= 3;
			p.sprite.setTextureRect(IntRect(43.16 * int(currentframe), 259.125, 43.16, 86.375));
			GetPlayerCoordingateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p.direction = 3; p.speed = 0.1;
			currentframe += 0.005;
			if (currentframe > 3)currentframe -= 3;
			p.sprite.setTextureRect(IntRect(43.16 * int(currentframe), 0, 43.16, 86.375));
			GetPlayerCoordingateForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
		}

		p.update(time);
		viewmap(time);
		window.setView(view);
		window.clear(Color::White);

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  map.setTextureRect(IntRect(0, 0, 32, 32)); 
				if (TileMap[i][j] == 's')  map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) map.setTextureRect(IntRect(64, 0, 32, 32));


				map.setPosition(j * 32, i * 32);

				window.draw(map);//рисуем квадратики на экран
			}
		
		
			window.draw(p.sprite);
		window.display();
	}
	
	return 0;
}