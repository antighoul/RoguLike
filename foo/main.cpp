#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "camera.h"
#include <iostream>
#include <sstream>
#include "mission.h"
//#include "map.h"
#include "level.h"

#include "TinyXML\\tinyxml2.h"
using namespace sf;
using namespace std;
//class Something
//{
//public:
//	float x, y;
//	int w, h;
//	bool scored;
//	Texture texture;
//	Sprite sprite;
//	String name;
//	Something(Image& image, String Name, float X, float Y, int W, int H)
//	{
//		name = Name;
//		x = X; y = Y; w = W; h = H;
//		scored = false;
//		texture.loadFromImage(image);
//		sprite.setTexture(texture);
//		sprite.setOrigin(w / 2, h / 2);
//	}
//};


////////////////////////////////////Общий класс родитель//////////////////////////

class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;   // loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
	Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
	}

	void tick(float time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;

		if (currentFrame > frames.size()) {
			currentFrame -= frames.size();
			if (!loop) { isPlaying = false; return; }
		}

		int i = currentFrame;
		sprite.setTextureRect(frames[i]);
		if (flip) sprite.setTextureRect(frames_flip[i]);
	}

};

class AnimationManager
{

public:
	std::string currentAnim;
	std::map<std::string, Animation> animList;

	AnimationManager()
	{}

	~AnimationManager()
	{
		animList.clear();
	}

	//создание анимаций вручную
	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true)
	{
		Animation a;
		a.speed = speed;
		a.loop = Loop;
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(0, h);

		for (int i = 0; i < count; i++)
		{
			a.frames.push_back(IntRect(x + i * step, y, w, h));
			a.frames_flip.push_back(IntRect(x + i * step + w, y, -w, h));
		}
		animList[name] = a;
		currentAnim = name;
	}

	void set(std::string name)
	{
		currentAnim = name;
		animList[currentAnim].flip = 0;
	}

	void draw(RenderWindow& window, int x = 0, int y = 0)
	{
		animList[currentAnim].sprite.setPosition(x, y);
		window.draw(animList[currentAnim].sprite);
	}

	void flip(bool b = 1) { animList[currentAnim].flip = b; }

	void tick(float time) { animList[currentAnim].tick(time); }

	void pause() { animList[currentAnim].isPlaying = false; }

	void play() { animList[currentAnim].isPlaying = true; }

	void play(std::string name) { animList[name].isPlaying = true; }

	bool isPlaying() { return animList[currentAnim].isPlaying; }

	float getH() { return animList[currentAnim].frames[0].height; }

	float getW() { return animList[currentAnim].frames[0].width; }

};

class Entity {
public:
	vector<Object> obj; // вектор объектов карты 
	AnimationManager anim;
	float dx, dy, x, y, speed, moveTimer;//dx dy направление джвиения x y координаты игрока 
	float w, h, health;
	float timer, timer_end;
	bool life, isMove,scored,dir;
	Sprite sprite;
	String name;
	std::string Name;
	int Health;
	virtual void update(float time) = 0;
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	Entity(Texture& texture, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true;  isMove = false; scored = false;
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	Entity(AnimationManager& A, int X, int Y)
	{
		anim = A;
		x = X;
		y = Y;
		dir = 0;

		life = true;
		timer = 0;
		timer_end = 0;
		dx = dy = 0;
	}
	void draw(RenderWindow& window)
	{
		anim.draw(window, x, y + h);
	}
	void option(string NAME, float SPEED = 0, int HEALTH = 10, std::string FIRST_ANIM = "")
	{
		name = NAME;
		if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
		w = anim.getW();
		h = anim.getH();
		dx = SPEED;
		health = HEALTH;
	}
};
class Coin :public Entity
{
public:
	Coin(Texture& texture, String Name,TileMap& lvl, float X, float Y, int W, int H) :Entity(texture, Name, X, Y, W, H)
	{
		obj = lvl.getAllObjects();
	    scored = false;
		if (name == "Coin")
		{
			sprite.setTextureRect(IntRect(168, 8, w, h));
			sprite.setPosition(x + w/2 , y + h/2);
		}
		if (name == "Telega")
		{
			sprite.setTextureRect(IntRect(222, 30, w, h));
			sprite.setPosition(x + w / 2, y + h / 2);
		}
		if (name == "Bonus")
		{
			sprite.setTextureRect(IntRect(200, 100, w, h ));
			sprite.setPosition(x + w / 2, y + h / 2);
		}
	}
	void Collision(int num)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "Solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h;  dy = 0; }
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
	}
	void update(float time)
	{
		x += dx * time;
		Collision(0);
		y += dy * time;
		Collision(1);
		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class PLAYER : public Entity
{
public:
	int playerScore,bonusCount;
	enum { stay, walk, duck, jump, climb, swim } STATE;
	bool onLadder, shoot, hit,bon;
	std::map<std::string, bool> key;

	PLAYER(AnimationManager& a, TileMap& lev, int x, int y) :Entity(a, x, y)
	{
		//setPlayerCoordinateForView(x, y);
		option("Player", 0, 100, "stay");
	    hit = false;
		bon = false;
		obj = lev.getAllObjects();
	}
	int getplayercoordinateX()
	{
		return x;
	}
	void Keyboard()
	{
		if (life) {
			if (key["L"])
			{
				dir = 1;
				if (STATE != duck) {
					dx = -0.2;
					if (bon)
					{
						dx -= bonusCount * 0.1;
					}
				}
				if (STATE == stay) STATE = walk;
			}

			if (key["R"])
			{
				dir = 0;
				if (STATE != duck)
				{
					dx = 0.2;
					if (bon)
					{
						dx += bonusCount * 0.1;
					}
				}

				if (STATE == stay) STATE = walk;
			}

			if (key["Up"])
			{
				if (onLadder) STATE = climb;
				if (STATE == stay || STATE == walk) { dy = -0.4; STATE = jump; anim.play("jump"); }
				if (STATE == climb) dy = -0.05;
				if (STATE == climb) if (key["L"] || key["R"]) STATE = stay;
			}

			if (key["Down"])
			{
				if (STATE == stay || STATE == walk) { STATE = duck; dx = 0; }
				if (STATE == climb) dy = 0.05;
			}

			if (key["Space"])
			{
				shoot = true;
			}

			/////////////////////если клавиша отпущена///////////////////////////
			if (!(key["R"] || key["L"]))
			{
				dx = 0;
				if (STATE == walk) STATE = stay;
			}

			if (!(key["Up"] || key["Down"]))
			{
				if (STATE == climb) dy = 0;
			}

			if (!key["Down"])
			{
				if (STATE == duck) { STATE = stay; }
			}

			if (!key["Space"])
			{
				shoot = false;
			}

			key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
		}
		else STATE = duck;
	}

	void Animation(float time)
	{
		if (STATE == stay) anim.set("stay");
		if (STATE == walk) anim.set("walk");
		if (STATE == jump) anim.set("jump");
		if (STATE == duck) anim.set("duck");
		if (STATE == climb) { anim.set("climb"); anim.pause(); if (dy != 0) anim.play(); }

		if (shoot) {
			anim.set("shoot");
			if (STATE == walk) anim.set("shootAndWalk");
		}

		if (hit) {
			timer += time;
			if (timer > 1000) { hit = false; timer = 0; }
			anim.set("hit");
		}

		if (dir) anim.flip();

		anim.tick(time);
	}

	void update(float time)
	{
		Keyboard();

		Animation(time);

		if (STATE == climb) if (!onLadder) STATE = stay;
		if (STATE != climb) dy += 0.0005 * time;
		onLadder = false;

		x += dx * time;
		Collision(0);

		y += dy * time;
		Collision(1);

		if (health <= 0) { life = false; }
		
	}

	void Collision(int num)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "Solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h;  dy = 0;   STATE = stay; }
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}

				if (obj[i].name == "ladder") { onLadder = true; if (STATE == climb) x = obj[i].rect.left - 10; }
				
				if (obj[i].name == "Death")
				{
					health -= 100;
				}
			}
	}

};


///////////////////////////////////////////////////////////КЛАСС ВРАГА /////////////////////////////////////////////////////

class Enemy :public Entity {
public:

	Enemy(AnimationManager& a, TileMap& lev, int x, int y) :Entity(a, x, y)
	{
		option("Enemy", 0.01, 15, "move");
	}
	Enemy(Texture& texture, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(texture, Name, X, Y, W, H)
	{
		obj = lvl.getObjectsByName("Solid");
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(55, 40, w, h));
			dx = 0.1;//даем скорость.этот объект всегда двигается
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = 0; i < obj.size(); i++)//проходимся по объектам
			if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
			{
				if (obj[i].name == "Solid")//если встретили препятствие
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0;  }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy") {//для персонажа с таким именем логика будет такой

			moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
			x += dx * time;
			checkCollisionWithMap(0, dy);
			y += dy * time;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
			if (health <= 0) { life = false; };
			//anim.tick(time);
			//dy = dy + 0.0015 * time;
		}
	}
};




                                                          //////////////////////////////МЕНЮ///////////////////
void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images\\start.png");
	menuTexture2.loadFromFile("images\\finish.png");
	menuBackground.loadFromFile("images\\village.jpg");
	
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	menu1.setScale(0.05f, 0.05f);
	menu2.setScale(0.2f, 0.2f);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(85, 105);
	menuBg.setPosition(0, 0);

	                                             
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 375, 60).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Green); menuNum = 1; }
		if (IntRect(100, 105, 375, 60).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Green); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	////////////////////////////////////////////////////
}

int startGame()
{
	RenderWindow window(VideoMode(960, 480), "MyGame");
	menu(window);
	view.reset(FloatRect(0, 0, 960, 480));


	/////////////////////////////////////////////////////////////// КАРТА/////////////////////////
	//string map1 = "map.tmx";
	TileMap lvl;
	lvl.load("map2.tmx");




	Font font;
	font.loadFromFile("images/CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Black);
	Text prologe2("", font, 20);
	Text prologe("", font, 40);
	prologe.setColor(Color::Red);
	Text pointsNumber("Coins collected : ", font, 25);
	pointsNumber.setColor(Color::Black);

	///////////////////////////////////////////////  QUEST IMAGE /////////////////////////////////////////////////////
	Image quest_image;
	quest_image.loadFromFile("images/svitok2.jpg");
	//quest_image.createMaskFromColor(Color(0, 0, 0));
	Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);

	bool showMissionText = true;



	Texture heroImage;
	heroImage.loadFromFile("images/megaman.png");

	Texture easyEnemyImage;
	easyEnemyImage.loadFromFile("images/Run2.png");

	Texture coinImage;
	coinImage.loadFromFile("images/pixel_platform_03_tileset_final.png");//взять монетку из тайлсета 

	Texture telegaImage;
	telegaImage.loadFromFile("images/pixel_platform_03_tileset_final.png");

	Texture bonusImage;
	bonusImage.loadFromFile("images/pixel_platform_03_tileset_final.png");

	AnimationManager anim;
	anim.create("walk", heroImage, 445, 575, 41, 46, 5, 0.005, 46);
	anim.create("jump", heroImage, 268, 690, 31, 61, 3, 0.0045, 33);
	anim.create("duck", heroImage, 140, 350, 56, 24, 1, 0.005);
	anim.create("stay", heroImage, 0, 155, 45, 41, 1, 0.005);
	anim.create("shoot", heroImage, 0, 155, 45, 41, 3, 0.004, 45);
	anim.create("climb", heroImage, 175, 390, 35, 61, 3, 0.004, 35);
	anim.create("swim", heroImage, 6, 531, 54, 35, 2, 0.005, 54);

	Animation soldjier;

	/////////////////////////////////////////////////////// ENEMIES LIST///////////////////
	list <Entity*> universals;
	list<Entity*>::iterator it;

	//////////////////////////////////////// Objects on map //////////////////////////////////
	vector <Object> enemies = lvl.getObjectsByName("EasyEnemy");
	vector <Object>coins = lvl.getObjectsByName("Coin");
	vector<Object>bonus = lvl.getObjectsByName("Bonus");

	Object telega = lvl.getObject("Telega");

	Object player = lvl.getObject("Player");

	PLAYER p(anim, lvl, player.rect.left, player.rect.top);//объект класса игрока

	for (int i = 0; i < bonus.size(); i++)
	{
		universals.push_back(new Coin(coinImage, "Bonus", lvl, bonus[i].rect.left, bonus[i].rect.top, 16, 22));
	}
	for (int i = 0; i < coins.size(); i++)
	{
		universals.push_back(new Coin(coinImage, "Coin", lvl, coins[i].rect.left, coins[i].rect.top, 17, 16));
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		universals.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, enemies[i].rect.left, enemies[i].rect.top, 90, 83));
	};

	Coin t(telegaImage, "Telega", lvl, telega.rect.left, telega.rect.top, 33, 36);

	Clock clock;


	int createObjectForMapTimer = 0;
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::RShift)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		float currentFrame = 0;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ

					switch (showMissionText) {//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
						std::ostringstream playerHealthString;//строка здоровья игрока
						playerHealthString << p.health; //заносим в строку здоровье 
						std::ostringstream playerScoreString;
						playerScoreString << p.playerScore;
						std::ostringstream task;//строка текста миссии
						task << getTextMission(getCurrentMission(p.getplayercoordinateX()));//вызывается функция getTextMission (она возвращает текст миссии), которая принимает в качестве аргумента функцию getCurrentMission(возвращающую номер миссии), а уже эта ф-ция принимает в качестве аргумента функцию p.getplayercoordinateX() (эта ф-ция возвращает Икс координату игрока)
						text.setString("Helth : " + playerHealthString.str() + "\n" + task.str() + "\n" + playerScoreString.str());
						showMissionText = false;//эта строка позволяет убрать все что мы вывели на экране
						break;//выходим , чтобы не выполнить условие "false" (которое ниже)
					}
					case false: {
						text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
						showMissionText = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
						break;
					}
					}
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) p.key["L"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Right)) p.key["R"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Up)) p.key["Up"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Down))p.key["Down"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Space)) p.key["Space"] = true;



		p.update(time);// Player update function
		t.update(time);
		for (it = universals.begin(); it != universals.end();)
		{
			Entity* b = *it;
			(*it)->update(time);
			if ((*it)->life == false)
			{
				it = universals.erase(it);
				//delete b;
			}
			if ((*it)->scored == true)
			{
				if ((*it)->name == "Coin")
				{
					it = universals.erase(it);
					p.playerScore += 1;
					delete b;
				}
				if ((*it)->name == "Bonus")
				{
					it = universals.erase(it);
					p.bonusCount += 1;
					delete b;
				}
			}
			else it++;
		}
		for (it = universals.begin(); it != universals.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "Coin")
				{
					(*it)->scored = true;
				}
				if ((*it)->name == "Bonus")
				{
					p.bon = true;
					(*it)->scored = true;
					p.health += 20;
				}
			}
		}
		for (it = universals.begin(); it != universals.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "EasyEnemy")
				{
					if ((p.dy > 0))
					{
						(*it)->dx = 0; p.dy = -0.2; (*it)->health = 0;
					}
					else
					{
						p.health -= 30;
					}

				}
			}
		}
		if (p.getRect().intersects(t.getRect()))
		{
			if (t.name == "Telega")
			{
				if (p.dx > 0)

					if (t.dx != -0.1)
					{
						p.x = p.x - t.w / 2;
						t.dx = 0.05;
					}
					else t.dx = 0;

				if (p.dx < 0)
				{
					if (t.dx != 0.1)
					{
						p.x = p.x + t.w / 2;
						t.dx = -0.05;
					}
					else t.dx = 0;
				}
			}
		}

		for (it = universals.begin(); it != universals.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((*it)->name == "EasyEnemy") {//и при этом имя объекта EasyEnemy,то..
					if ((*it)->dx > 0)//если враг идет вправо
					{
						(*it)->x = (*it)->x - 100; //отталкиваем его от игрока влево (впритык)
						//(*it)->dx = (*it)->dx;//останавливаем
					}
					if ((*it)->dx < 0)//если враг идет влево
					{
						(*it)->x = (*it)->x + 100; //аналогично - отталкиваем вправо
						(*it)->dx = (*it)->dx;
					}
					if (p.dx > 0)
					{
						//p.x = (*it)->x + p.w;
					}
					if (p.dx < 0)
					{
						//p.x = (*it)->x - (*it)->w;
					}
				}
			}
		}


		window.clear(Color::White);
		//view.setCenter(p.x, p.y);
		setPlayerCoordinateForView(p.x, p.y);
		window.setView(view);

		window.draw(lvl);

		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);//позиция всего этого текстового блока
			s_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);//позиция фона для блока			
			window.draw(s_quest); window.draw(text); //рисуем спрайт свитка (фон для текста миссии). а затем и текст. все это завязано на логическую переменную, которая меняет свое состояние от нажатия клавиши ТАБ
		}

		if (!p.life)
		{
			prologe2.setString("press rShift to restart");
			prologe2.setPosition(view.getCenter().x, view.getCenter().y + 50);
			prologe2.setColor(Color::Black);
			prologe.setPosition(view.getCenter().x - 50, view.getCenter().y);
			prologe.setString("YOU DIED !!!!!");
			window.draw(prologe);
			window.draw(prologe2);
		}
		std::ostringstream playerHealthString;//строка здоровья игрока
		playerHealthString << p.health; //заносим в строку здоровье 
		std::ostringstream playerScoreString;
		playerScoreString << p.playerScore;
		pointsNumber.setColor(Color::Magenta);
		pointsNumber.setPosition(view.getCenter().x + 150, view.getCenter().y - 170);
		pointsNumber.setString("Coins Collected:" + playerScoreString.str() + '\n'+ "Current Health:"+playerHealthString.str()+'\n');
		window.draw(pointsNumber);

		for (it = universals.begin(); it != universals.end(); it++)
		{
			/*if ((*it)->life==true)
			{*/
			window.draw((*it)->sprite);
			//window.draw((*itCoin)->sprite);
		/*}*/
		}
		window.draw(t.sprite);
		p.draw(window);

		window.display();
		//cout << p.STATE << endl;
	}

	return 0;
}

void gameRunning()
{
	if (startGame()) { gameRunning(); }
}

int main()
{
		gameRunning();//запускаем процесс игры
		return 0;
}

