#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const int HEIGHT_MAP = 6;
const int WIDTH_MAP = 10;

String  TileMap[HEIGHT_MAP] = {
	"00   00000",
	"000 000000",
	"000  00000",
	"000  00000",
	"0000000000",
	"000    000",
};
void Smap(Sprite map, RenderWindow window) {
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '0') map.setTextureRect(IntRect(32, 40, 32, 40));
			if (TileMap[i][j] == ' ') map.setTextureRect(IntRect(32, 120, 32, 40));
			if (TileMap[i][j] == '9') map.setTextureRect(IntRect(32, 80, 32, 40));

			map.setPosition(i * 32, j * 32);
			window.draw(map);

		}
	}
}

void foo() {
	RenderTexture rTexture;
	if (!rTexture.create(640, 480)) {};

}