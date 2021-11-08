#include <SFML/Graphics.hpp>

using namespace sf;

class Player 
{
private: float x, y;
public:
	float width, hight, dx, dy, speed = 0;//X,Y,W,H,-КООРДИНАТЫ И ИКОНКА ИГРОКА, dx,dy-ускорение по x,y; speed-скорость 
	int direction = 0;// направление движения
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String file, float x, float y, float w, float h);//создает новый объект игрока, его текстуру
	void update(float time);//отвечает за передвижение игрока
	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
};