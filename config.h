#define BUZZER 10
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7



  struct Obstacle {
  byte x;
  byte y;
  byte i;
};


byte dinoL[8] = {
  B01110,
  B11010,
  B11111,
  B11111,
  B01110,
  B11010,
  B10011,
  B11000
};
byte dinoR[8] = {
  B01110,
  B11010,
  B11111,
  B11111,
  B01110,
  B10010,
  B11010,
  B00011
};
byte cactusL[8] = {
  B00100,
  B10100,
  B10101,
  B11001,
  B11011,
  B01110,
  B00100,
  B00100
};
byte cactusB[8] = {
  B00000,
  B10100,
  B10100,
  B11101,
  B11001,
  B11011,
  B11110,
  B01110
};
byte bird[8] = {
  B01000,
  B10110,
  B00010,
  B11111,
  B10010,
  B00011,
  B00001,
  B00000
};