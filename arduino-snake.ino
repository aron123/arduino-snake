#include <Adafruit_PCD8544.h>

// Constants

// speaker pin
#define SPEAKER_OUT 6

// LCD pins
#define RST 12
#define CE  13
#define DC  11
#define DIN  10
#define CLK  9

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
#define SNAKE_DIRECTION_RIGTH 2
#define SNAKE_DIRECTION_DOWN 3
#define SNAKE_DIRECTION_LEFT 4
#define MODE_START_SCREEN 1
#define MODE_GAME_SCREEN 2


// Globals
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
int snake[SNAKE_MAX_SIZE][2]  = {
  {13, 8},
  {14, 8},
  {15, 8},
  {16, 8},
  0
};
int snakeLength = 4;
int snakeDirection = SNAKE_DIRECTION_LEFT;
int food[2] = { 4, 4 };
int mode = MODE_START_SCREEN;

void setup() {
  pinMode(SPEAKER_OUT, OUTPUT);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  // Setup display
  display.begin();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  drawBorders();
  display.setCursor(6, 20);
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
  //playLooseSound();
  //delay(1000);
  //playWinnerSound();
  //delay(1000);

  
  if (mode == MODE_START_SCREEN && digitalRead(BUTTON_CONTROL) == LOW) {
    mode = MODE_GAME_SCREEN;
    display.clearDisplay();
    drawBorders();
    drawSnake(snake, snakeLength);
    drawFood(food);
    display.display();
  }
}

void drawBorders () {
  display.drawRect(0, 0, display.width(), display.height(), BLACK);
}

void drawSnake (int snake[][2], int length) {
  int i;

  for (i=0; i < length; i++) {
    display.drawRect(BLOCK_SIZE * snake[i][0], BLOCK_SIZE * snake[i][1], BLOCK_SIZE, BLOCK_SIZE, BLACK);
  }
}

void drawFood (int food[2]) {
  display.fillRect(BLOCK_SIZE * food[0], BLOCK_SIZE * food[1], BLOCK_SIZE, BLOCK_SIZE, BLACK);
}

void playWinnerSound() {

  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 150; i++) {
      digitalWrite(SPEAKER_OUT, HIGH);
      delayMicroseconds(250);
      digitalWrite(SPEAKER_OUT, LOW);
      delayMicroseconds(250);
    }

    for (int i = 0; i < 150; i++) {
      digitalWrite(SPEAKER_OUT, HIGH);
      delayMicroseconds(300);
      digitalWrite(SPEAKER_OUT, LOW);
      delayMicroseconds(300);
    }

    for (int i = 0; i < 150; i++) {
      digitalWrite(SPEAKER_OUT, HIGH);
      delayMicroseconds(350);
      digitalWrite(SPEAKER_OUT, LOW);
      delayMicroseconds(350);
    }

    for (int i = 0; i < 150; i++) {
      digitalWrite(SPEAKER_OUT, HIGH);
      delayMicroseconds(300);
      digitalWrite(SPEAKER_OUT, LOW);
      delayMicroseconds(300);
    }

    for (int i = 0; i < 150; i++) {
      digitalWrite(SPEAKER_OUT, HIGH);
      delayMicroseconds(350);
      digitalWrite(SPEAKER_OUT, LOW);
      delayMicroseconds(350);
    }
  }
}

void playLooseSound() {
  for (int i = 0; i < 150; i++) {
    digitalWrite(SPEAKER_OUT, HIGH);
    delayMicroseconds(250);
    digitalWrite(SPEAKER_OUT, LOW);
    delayMicroseconds(250);
  }

  delay(250);

  for (int i = 0; i < 150; i++) {
    digitalWrite(SPEAKER_OUT, HIGH);
    delayMicroseconds(300);
    digitalWrite(SPEAKER_OUT, LOW);
    delayMicroseconds(300);
  }

  delay(250);

  for (int i = 0; i < 150; i++) {
    digitalWrite(SPEAKER_OUT, HIGH);
    delayMicroseconds(350);
    digitalWrite(SPEAKER_OUT, LOW);
    delayMicroseconds(350);
  }

  delay(250);

  for (int i = 0; i < 750; i++) {
    digitalWrite(SPEAKER_OUT, HIGH);
    delayMicroseconds(400);
    digitalWrite(SPEAKER_OUT, LOW);
    delayMicroseconds(400);
  }
}
