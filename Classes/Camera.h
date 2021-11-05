#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View GetPlayerCoordingateForView(float x, float y) 
{
	view.setCenter(x+ 100, y);
	return view;
}
