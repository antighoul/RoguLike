
//#include <SFML/Graphics.hpp>
//#include <iostream>
//const int HEIGHT_MAP = 25;
//const int WIDTH_MAP = 40;
//
//
//sf::String TileMap[HEIGHT_MAP] = {
//	"0000000000000000000000000000000000000000",
//	"0                                      0",
//	"0                                      0",
//	"0                                      0",
//	"0                                      0",
//	"0                                      0",
//	"0                       00             0",
//	"0                                      0",
//	"0                                      0",
//	"0                                      0",
//	"0               00                     0",
//	"0                   s                  0",
//	"0                   00   s             0",
//	"0                        00            0",
//	"0                                      0",
//	"0                             s        0",
//	"0                             00       0",
//	"0                                      0",
//	"0                          00          0",
//	"0                                      0",
//	"0               s   0000               0",
//	"0           000000000000               0",
//	"0    s      000000000000               0",
//	"0    000    000000000000    h   h  h   0",
//	"0000000000000000000000000000000000000000",
//};
//
//void randomMapGenerate() {//рандомно расставляем предметы
//
//
//	int randomElementX = 0;//случайный элемент по горизонтали
//	int randomElementY = 0;//случ эл-т по вертикали
//	srand(time(0));//рандом	
//	int countStone = 1;//количество камней 1
//
//	while (countStone > 0) {
//		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
//		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же
//		if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
//			TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.
//			
//			countStone--;//создали камень=>счетчик камней будет "текущий минус 1"
//		}
//	}
//}