#include <SFML/Graphics.hpp>

using namespace sf;

class Player 
{
private: float x, y;
public:
	float width, hight, dx, dy, speed = 0;//X,Y,W,H,-���������� � ������ ������, dx,dy-��������� �� x,y; speed-�������� 
	int direction = 0;// ����������� ��������
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String file, float x, float y, float w, float h);//������� ����� ������ ������, ��� ��������
	void update(float time);//�������� �� ������������ ������
	float GetPlayerCoordinateX();
	float GetPlayerCoordinateY();
};