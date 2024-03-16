#include <LiquidCrystal.h> 
#include "config.h"

int score = 0;
Obstacle obstacles[4];
byte numObstacles = 0;
unsigned int frame = 300;

// Функция создания нового препятствия
void spawnObstacle() {
    if (numObstacles < 4 && random(0, 100) < 50){
        Obstacle newObstacle;
        newObstacle.i = random(2, 5);
        newObstacle.y = (newObstacle.i == 4) ? 0 : 1;
        newObstacle.x = 16;
        
        obstacles[numObstacles] = newObstacle;
        numObstacles++;
    }
}

// Функция обновления кадра
void updateFrame() {
    static int jumpTime = 0;
    static int leftStep = 1;
    byte d = (digitalRead(8) == LOW) ? 0 : 1;

    if (d == 0) {
        jumpTime++;
    } else {
        // Динозавр не в прыжке, сбрасываем время прыжка
        jumpTime = 0;
    }

    // Если динозавр прыгает дольше 9 временных шагов
    if (jumpTime > 9) {
        // Опускание динозавра
        d = 1;
        // Сброс времени прыжка
        jumpTime = 0;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(score);
    lcd.setCursor(3, d);
    lcd.write(byte(leftStep)); // Символ левой ноги

    // Меняем флаг шага для следующего кадра
    leftStep = !leftStep;

    for (int i = 0; i < numObstacles; i++) {
        lcd.setCursor(obstacles[i].x, obstacles[i].y);
        lcd.write(byte(obstacles[i].i));
        
        if (obstacles[i].x == 3 && obstacles[i].y == d) {
            tone(BUZZER, 50);
              
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print("GAME OVER!");
            delay(800);

            noTone(BUZZER);

            lcd.clear();
            lcd.setCursor(3, 1);
            lcd.print("Score: ");
            lcd.print(score);
            delay(1500);

            lcd.clear();
            lcd.setCursor(7, 0);
            lcd.print("GO!");
            delay(500);
            tone(BUZZER, 600);
            delay(100);
            noTone(BUZZER);

            numObstacles = 0;
            score = 0;
            frame = 300;
        }
    }
}

void setup() {
    // Инициализация LCD и создание пользовательских символов
    lcd.begin(16, 2);
    pinMode(8, INPUT_PULLUP);
    lcd.createChar(0, dinoL);
    lcd.createChar(1, dinoR);
    lcd.createChar(2, cactusL);
    lcd.createChar(3, cactusB);
    lcd.createChar(4, bird);

    lcd.setCursor(3, 0);
    lcd.print("GO, DINO!");
    delay(1000);
    lcd.clear();
}

void loop() {
    unsigned long lastSpawnTime = millis();
    unsigned long lastFrameTime = millis();
    unsigned long lastMoveTime = millis();

    while (1) {
        unsigned long currentTime = millis();

        if (currentTime - lastSpawnTime >= 6 * frame) {
            spawnObstacle();
            lastSpawnTime = currentTime;
        }

        if (currentTime - lastFrameTime >= 3 * frame) {
            // Обновление препятствий на экране
            int numRemovedObstacles = 0;
            tone(BUZZER, 50);
            delay(10);
            noTone(10);
            
            for (int i = 0; i < numObstacles; i++) {
                if (obstacles[i].x > 0) {
                    obstacles[i].x--;
                } else {
                    numRemovedObstacles++;
                    score++;
                    if (frame > 200) frame -= score * 3;
                }
            }

            for (int i = 0; i < numRemovedObstacles; i++) {
                for (int j = 0; j < numObstacles - 1;j++) {
                    obstacles[j] = obstacles[j + 1];
                }
                numObstacles--;
            }

            lastFrameTime = currentTime;
        }

        if (currentTime - lastMoveTime >= frame) {
            updateFrame();
            lastMoveTime = currentTime;
        }
    }
}