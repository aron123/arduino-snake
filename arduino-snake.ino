#include <Adafruit_PCD8544.h>

// Constants

// speaker pin
#define SPEAKER_OUT 6

// LCD pins
#define RST 12
#define CE 13
#define DC 11
#define DIN 10
#define CLK 9

// button pins
#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_CONTROL 7 // F button

// game settings
#define BLOCK_SIZE 3
#define GAME_WIDTH 84/BLOCK_SIZE
#define GAME_HEIGHT 48/BLOCK_SIZE
#define SNAKE_MAX_SIZE 64

#define SNAKE_DIRECTION_UP 1
#define SNAKE_DIRECTION_RIGHT 2
#define SNAKE_DIRECTION_DOWN 3
#define SNAKE_DIRECTION_LEFT 4

#define MODE_START_SCREEN 1
#define MODE_GAME_SCREEN 2
#define MODE_RESULT_SCREEN 3

#define GAME_STATE_IN_PROGRESS 1
#define GAME_STATE_WIN 2
#define GAME_STATE_GAMEOVER 3

const uint8_t PROGMEM snake_start_Bitmap [] PROGMEM = {
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00011000, B00000000, B00000000, B00010000, B00000110, B00000001, B10100000, B00000000, B00000000,
  B00000000, B00000000, B00111000, B00000001, B10000110, B00110000, B01011110, B00001110, B00100000, B00000000, B00000000,
  B00000000, B00000000, B01111100, B11100011, B10011110, B01110000, B11011111, B11000000, B00100000, B00000000, B00000000,
  B00000000, B00000000, B11111100, B11100011, B10011110, B01111001, B11111010, B00000100, B11100000, B00000000, B00000000,
  B00000000, B00000001, B11110000, B11110011, B00111110, B00011011, B11110010, B00001100, B10000000, B00000000, B00000000,
  B00000000, B00000001, B11100001, B11110011, B00111011, B00011111, B10100001, B11001000, B10000000, B00000000, B00000000,
  B00000000, B00000011, B10000001, B11110011, B00110011, B11101111, B01100000, B01001000, B10000000, B00000000, B00000000,
  B00000000, B00000011, B00000000, B11111011, B01110011, B11101110, B00111100, B01001000, B10000000, B00000000, B00000000,
  B00000000, B00000111, B01111110, B11011011, B01110111, B11001110, B00111000, B01001000, B10000000, B00000000, B00000000,
  B00000000, B00000111, B11111110, B11011111, B01111111, B10011111, B00111010, B01001000, B10100000, B00000000, B00000000,
  B00000000, B00000000, B00001110, B11001111, B01111001, B10011111, B10011111, B01001000, B00100000, B00000000, B00000000,
  B00000000, B00000000, B00011111, B11000110, B01100001, B00011001, B10011100, B10000000, B11100000, B00000000, B00000000,
  B00000000, B00000000, B01111101, B10000001, B11100000, B11001000, B00011001, B00000111, B10000000, B00000000, B00000000,
  B00000000, B00000001, B11111011, B00000000, B01000001, B00110000, B00000001, B00111100, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11110000, B00000000, B00100100, B11001110, B00000000, B11110000, B00000000, B00000000, B00000000,
  B00000000, B00000001, B11000000, B00000000, B00110001, B10000001, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000001, B00000000, B00011111, B10110000, B00011000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B11111111, B11000100, B00001000, B10000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000011, B11011111, B10000000, B00000101, B10000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00001111, B11111110, B00000000, B11110011, B11110000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00011111, B11000001, B10000011, B01000011, B11111000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00111111, B01100000, B11111101, B10000100, B11101111, B10000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00111111, B11100000, B01010001, B00001001, B10000000, B01000100, B00000000, B00000000, B00000000,
  B00000000, B00000000, B01110011, B11100000, B00110010, B00010010, B00011110, B00110000, B00000000, B00000000, B00000000,
  B00000000, B00000001, B11111111, B11110000, B01010100, B00100100, B01111111, B00011000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B01111011, B11111111, B00001000, B01001000, B11101110, B10011100, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11111101, B11111101, B00011000, B10010001, B10011111, B10010010, B01000000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11111111, B00110001, B00000010, B10111111, B11111010, B01100000, B00000000, B00000000,
  B00000000, B00000001, B11111110, B10100001, B01000010, B00000100, B11000111, B11100011, B00000000, B00000000, B00000000,
  B00000000, B00000000, B11011111, B01001010, B01000101, B11000010, B01100000, B00011111, B00100000, B00000000, B00000000,
  B00000000, B00000000, B00110111, B10010100, B10001011, B11010001, B01101111, B11111111, B00100000, B00000000, B00000000,
  B00000000, B00000000, B11011011, B01010110, B10000011, B11101000, B10100000, B00011111, B10100000, B00000000, B00000000,
  B00000000, B00000011, B11101101, B11110110, B00011011, B11110101, B01000000, B00011111, B00100000, B00000000, B00000000,
  B00000000, B00000111, B11110110, B11110110, B00010100, B00110010, B01000111, B11011101, B10100000, B00000000, B00000000,
  B00000000, B00000111, B11111011, B01110110, B10000000, B01001100, B00100000, B00011001, B11000000, B00000000, B00000000,
  B00000000, B00000011, B11111100, B01001111, B01000000, B00000000, B01011100, B01110000, B00100000, B00000000, B00000000,
  B00000000, B00000000, B01111111, B11101111, B10011100, B00000001, B10011000, B00011111, B10000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

// Globals
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
int snake[SNAKE_MAX_SIZE][2]  = {0};
int snakeLength = 4;
int snakeDirection = SNAKE_DIRECTION_LEFT;
int food[2] = { 4, 4 };
int snakeSpeed = 100; // ms between movement frames
int mode = MODE_START_SCREEN;
int gameState = GAME_STATE_IN_PROGRESS;

void setup() {
  pinMode(SPEAKER_OUT, OUTPUT);

  randomSeed(analogRead(0));

  // Setup display
  display.begin();
  display.setContrast(63);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.drawBitmap(0, 0, snake_start_Bitmap, 84, 48, BLACK);
  display.setCursor(6, 40);
  display.println("Start with F");
  display.display();

  // Setup buttons
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_CONTROL, INPUT);

  // TODO: just for debug
  Serial.begin(9600);
}

void loop() {
  if (mode == MODE_START_SCREEN && digitalRead(BUTTON_CONTROL) == LOW) { // step into game
    mode = MODE_GAME_SCREEN;
    gameState = GAME_STATE_IN_PROGRESS;
    initializeGame();

    bool doEats = false;
    bool doBitesItself = false;
    bool doCollidesWithWall = false;

    playNokiaTune();

    while (true) {
      display.clearDisplay();
      snakeDirection = determineDirection(snakeDirection);
      doEats = isSnakeEating(snake, snakeLength, food);
      doBitesItself = isSnakeBitesItself(snake, snakeLength);
      doCollidesWithWall = isSnakeCollidesWithWall(snake, snakeLength, snakeDirection);

      if (doEats) {
        snakeLength++;
        playFoodCatchSound();
        moveFood(snake, snakeLength, food);
      }

      if (doBitesItself || doCollidesWithWall) {
        gameState = GAME_STATE_GAMEOVER;
        mode = MODE_RESULT_SCREEN;
        playGameOverSound();
        break;
      }

      if (snakeLength == SNAKE_MAX_SIZE) {
        gameState = GAME_STATE_WIN;
        mode = MODE_RESULT_SCREEN;
        playWinnerSound();
        break;
      }

      moveSnake(snake, snakeLength, snakeDirection, doEats);
      drawBorders();
      drawSnake(snake, snakeLength);
      drawFood(food);
      display.display();
      delay(snakeSpeed);
    }
  }

  if (mode == MODE_RESULT_SCREEN && gameState == GAME_STATE_GAMEOVER) {
    display.clearDisplay();
    display.setCursor(6, 0);
    display.println("Game Over :(");
    display.setCursor(4, 12);
    display.println("Length was " + String(snakeLength));
    display.setCursor(8, 36);
    display.println("New game: F");
    display.display();
  }

  if (mode == MODE_RESULT_SCREEN && gameState == GAME_STATE_WIN) {
    display.clearDisplay();
    display.setCursor(16, 0);
    display.println("You won!");
    display.setCursor(4, 12);
    display.println("Length was " + String(snakeLength));
    display.setCursor(8, 36);
    display.println("New game: F");
    display.display();
  }

  if (mode == MODE_RESULT_SCREEN && digitalRead(BUTTON_CONTROL) == LOW) {
    mode = MODE_START_SCREEN;
  }
}

void initializeGame() {
  snakeLength = 4;
  snakeDirection = SNAKE_DIRECTION_LEFT;
  food[0] = 4;
  food[1] = 4;

  for (int i = 0; i < SNAKE_MAX_SIZE; i++) {
    snake[i][0] = 0;
    snake[i][1] = 0;
  }

  snake[0][0] = 17;
  snake[0][1] = 8;

  snake[1][0] = 16;
  snake[1][1] = 8;

  snake[2][0] = 15;
  snake[2][1] = 8;

  snake[3][0] = 14;
  snake[3][1] = 8;
}

void drawBorders () {
  display.drawRect(0, 0, display.width(), display.height(), BLACK);
}

void drawSnake (int snake[][2], int length) {
  for (int i = 0; i < length; i++) {
    display.drawRect(BLOCK_SIZE * snake[i][0], BLOCK_SIZE * snake[i][1], BLOCK_SIZE, BLOCK_SIZE, BLACK);
  }
}

void drawFood (int food[2]) {
  display.fillRect(BLOCK_SIZE * food[0], BLOCK_SIZE * food[1], BLOCK_SIZE, BLOCK_SIZE, BLACK);
}

int determineDirection (int currentDirection) {
  bool upPushed = digitalRead(BUTTON_UP) == LOW;
  bool rightPushed = digitalRead(BUTTON_RIGHT) == LOW;
  bool downPushed = digitalRead(BUTTON_DOWN) == LOW;
  bool leftPushed = digitalRead(BUTTON_LEFT) == LOW;

  if (!upPushed && !rightPushed && !downPushed && !leftPushed) {
    return currentDirection;
  }

  if (upPushed && currentDirection == SNAKE_DIRECTION_UP
      || rightPushed && currentDirection == SNAKE_DIRECTION_RIGHT
      || downPushed && currentDirection == SNAKE_DIRECTION_DOWN
      || leftPushed && currentDirection == SNAKE_DIRECTION_LEFT) {
    return currentDirection;
  }

  if (upPushed && currentDirection == SNAKE_DIRECTION_DOWN
      || rightPushed && currentDirection == SNAKE_DIRECTION_LEFT
      || downPushed && currentDirection == SNAKE_DIRECTION_UP
      || leftPushed && currentDirection == SNAKE_DIRECTION_RIGHT) {
    return currentDirection;
  }

  int pushedCount = 0;
  int buttonPushes[] = { upPushed, rightPushed, downPushed, leftPushed };

  for (int i = 0; i < 4; i++) {
    pushedCount += buttonPushes[i];
  }

  if (pushedCount != 1) {
    return currentDirection;
  }

  if (upPushed) {
    return SNAKE_DIRECTION_UP;
  }
  if (rightPushed) {
    return SNAKE_DIRECTION_RIGHT;
  }
  if (downPushed) {
    return SNAKE_DIRECTION_DOWN;
  }
  if (leftPushed) {
    return SNAKE_DIRECTION_LEFT;
  }
}

bool isFoodInsideSnake(int snake[][2], int snakeLength, int foodX, int foodY) {
  for (int i = 0; i < snakeLength; i++) {
    if (snake[i][0] == foodX && snake[i][1] == foodY) {
      return true;
    }
  }

  return false;
}

bool isSnakeEating (int snake[][2], int snakeLength, int food[2]) {
  int head = snakeLength - 1;
  return food[0] == snake[head][0] && food[1] == snake[head][1];
}

bool isSnakeBitesItself(int snake[][2], int snakeLength) {
  int headX = snake[snakeLength - 1][0];
  int headY = snake[snakeLength - 1][1];

  for (int i = 0; i < snakeLength - 1; i++) {
    if (snake[i][0] == headX && snake[i][1] == headY) {
      return true;
    }
  }

  return false;
}

bool isSnakeCollidesWithWall(int snake[][2], int snakeLength, int direction) {
  int headX = snake[snakeLength - 1][0];
  int headY = snake[snakeLength - 1][1];

  return (headX == 0 && direction == SNAKE_DIRECTION_LEFT
          || headY == 0 && direction == SNAKE_DIRECTION_UP
          || headX == GAME_WIDTH - 1 && direction == SNAKE_DIRECTION_RIGHT
          || headY == GAME_HEIGHT - 1 && direction == SNAKE_DIRECTION_DOWN);
}

bool moveFood(int snake[][2], int snakeLength, int food[2]) {
  int width, height;

  do {
    width = random(1, GAME_WIDTH - 1);
    height = random(1, GAME_HEIGHT - 1);
  } while (isFoodInsideSnake(snake, snakeLength, width, height));

  food[0] = width;
  food[1] = height;
}


void moveSnake(int snake[][2], int length, int direction, bool doEats) {
  int previousBlock[2] = { 0, 0 };
  int head = length - 1;

  // if snake eats, only put one block on the head
  if (doEats) {
    int secondBlock[2] = {snake[head - 1][0], snake[head - 1][1]};

    if (direction == SNAKE_DIRECTION_UP) {
      snake[head][0] = secondBlock[0];
      snake[head][1] = secondBlock[1] - 1;
    }
    else if (direction == SNAKE_DIRECTION_RIGHT) {
      snake[head][0] = secondBlock[0] + 1;
      snake[head][1] = secondBlock[1];
    }
    else if (direction == SNAKE_DIRECTION_DOWN) {
      snake[head][0] = secondBlock[0];
      snake[head][1] = secondBlock[1] + 1;
    }
    else if (direction == SNAKE_DIRECTION_LEFT) {
      snake[head][0] = secondBlock[0] - 1;
      snake[head][1] = secondBlock[1];
    }

    return;
  }

  // avoid to overcome borders
  if (direction == SNAKE_DIRECTION_UP && snake[head][1] == 0
      || direction == SNAKE_DIRECTION_RIGHT && snake[head][0] == GAME_WIDTH - 1
      || direction == SNAKE_DIRECTION_DOWN && snake[head][1] == GAME_HEIGHT - 1
      || direction == SNAKE_DIRECTION_LEFT && snake[head][0] == 0) {
    return;
  }

  // move head, shift body parts
  for (int i = length - 1; i >= 0; i--) {
    if (i == length - 1) {
      previousBlock[0] = snake[i][0];
      previousBlock[1] = snake[i][1];

      if (direction == SNAKE_DIRECTION_UP) {
        snake[i][1] -= 1;
      }
      else if (direction == SNAKE_DIRECTION_RIGHT) {
        snake[i][0] += 1;
      }
      else if (direction == SNAKE_DIRECTION_DOWN) {
        snake[i][1] += 1;
      }
      else if (direction == SNAKE_DIRECTION_LEFT) {
        snake[i][0] -= 1;
      }
    } else {
      int tmp = snake[i][0];
      snake[i][0] = previousBlock[0];
      previousBlock[0] = tmp;

      tmp = snake[i][1];
      snake[i][1] = previousBlock[1];
      previousBlock[1] = tmp;
    }
  }
}

void playNokiaTune() {
  tone(SPEAKER_OUT, 1318, 94.56519375);
  delay(105.0724375);
  delay(3.6231875);
  tone(SPEAKER_OUT, 1174, 100.271714063);
  delay(111.413015625);
  delay(9.05796875);
  tone(SPEAKER_OUT, 739, 183.423867188);
  delay(203.804296875);
  delay(6.340578125);
  tone(SPEAKER_OUT, 830, 185.86951875);
  delay(206.5216875);
  delay(1.81159375);
  tone(SPEAKER_OUT, 1108, 86.413021875);
  delay(96.01446875);
  delay(0.905796875);
  tone(SPEAKER_OUT, 987, 105.978234375);
  delay(117.75359375);
  delay(0.905796875);
  tone(SPEAKER_OUT, 587, 207.065165625);
  delay(230.07240625);
  delay(0.905796875);
  tone(SPEAKER_OUT, 659, 221.739075);
  delay(246.37675);
  delay(0.905796875);
  tone(SPEAKER_OUT, 987, 103.532582813);
  delay(115.036203125);
  delay(2.717390625);
  tone(SPEAKER_OUT, 880, 126.358664063);
  delay(140.398515625);
  delay(0.905796875);
  tone(SPEAKER_OUT, 554, 237.228201563);
  delay(263.586890625);
  tone(SPEAKER_OUT, 554, 237.228201563);
  delay(57.065203125);
  tone(SPEAKER_OUT, 659, 237.228201563);
  delay(57.065203125);
  tone(SPEAKER_OUT, 759, 237.228201563);
  delay(57.065203125);
  tone(SPEAKER_OUT, 880, 684.7824375);
  delay(760.869375);
}

void playFoodCatchSound() {
  tone(SPEAKER_OUT, 400, 75);
  tone(SPEAKER_OUT, 500, 75);
}

void playGameOverSound() {
  tone(SPEAKER_OUT, 369, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 349, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 311, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 277, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 261, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 233, 75.0);
  delay(83.3333333333);
  tone(SPEAKER_OUT, 220, 450.0);
  delay(500.0);
}

void playWinnerSound() {
  tone(SPEAKER_OUT, 220, 78.94725);
  delay(87.7191666667);
  delay(175.438333333);
  tone(SPEAKER_OUT, 220, 78.94725);
  delay(87.7191666667);
  tone(SPEAKER_OUT, 220, 78.94725);
  delay(87.7191666667);
  tone(SPEAKER_OUT, 220, 78.94725);
  delay(87.7191666667);
  tone(SPEAKER_OUT, 246, 78.94725);
  delay(87.7191666667);
  delay(175.438333333);
  tone(SPEAKER_OUT, 246, 78.94725);
  delay(87.7191666667);
  delay(175.438333333);
  tone(SPEAKER_OUT, 277, 78.94725);
  delay(87.7191666667);
  delay(175.438333333);
  tone(SPEAKER_OUT, 220, 78.94725);
  delay(87.7191666667);
  delay(175.438333333);
  tone(SPEAKER_OUT, 246, 236.84175);
  delay(263.1575);
}
