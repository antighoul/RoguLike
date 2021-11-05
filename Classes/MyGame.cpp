#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
#include "Camera.h"
using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Joska9 igra 228");
	view.reset(FloatRect(0, 0, 640, 480));
	string f = "Hero.png";

	float currentframe = 0;

	Image MAP;
	MAP.loadFromFile("gamedev\\World\\[A]_type1\\[A]Grass1-Dirt2_pipo.png");
	Texture mainMAP;
	mainMAP.loadFromImage(MAP);
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
		window.setView(view);
		window.clear(Color::White);

		/*for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0') map.setTextureRect(IntRect(32, 40, 32, 40));
				if (TileMap[i][j] == ' ') map.setTextureRect(IntRect(32, 120, 32, 40));
				if (TileMap[i][j] == '9') map.setTextureRect(IntRect(32, 80, 32, 40));

				map.setPosition(i * 32, j * 32);
				window.draw(map);

			}
	    }*/
		Smap(map, window);
		
			window.draw(p.sprite);
		window.display();
	}
	
	return 0;
}