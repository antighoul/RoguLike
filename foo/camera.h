#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view;

void setPlayerCoordinateForView(float x, float y)
{
	float tempX = x; float tempY = y;

	if (x < 500) tempX = 500;//������� �� ���� ����� �������
	if (x >1700)tempX = 1700;
	if (y < 240) tempY = 240;//������� �������
	if (y > 670) tempY = 675;//������ �������	

	view.setCenter(tempX, tempY);
}
