#include "Arduino_GigaDisplay_GFX.h"

GigaDisplay_GFX display;
GFXcanvas1 cnv(800, 480);

#define GC9A01A_CYAN 0x07FF
#define GC9A01A_RED 0xf800
#define GC9A01A_BLUE 0x001F
#define GC9A01A_GREEN 0x07E0
#define GC9A01A_MAGENTA 0xF81F
#define GC9A01A_WHITE 0xffff
#define GC9A01A_BLACK 0x0000
#define GC9A01A_YELLOW 0xFFE0

// Function prototypes
void generateInvaderPattern(bool grid[][8], int invLength, int invHeight);
void drawInvader(int x, int y, int pixelSize, bool invaderGrid[][8], int invLength, int invHeight);

unsigned long previousMillis = -1000;
const long interval = 500;
bool invaderGrid[8][8];
int invLength = 8;
int invHeight = 8;

void setup() {
  // Serial.begin(115200);
  display.begin();                // Initialize the display
  cnv.fillScreen(GC9A01A_BLACK);  // Fill the screen with black color
  // Serial.println("Start Up");
  display.setRotation(1);
}

void loop() {
  cnv.fillScreen(GC9A01A_BLACK);
  display.fillScreen(GC9A01A_BLACK);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    generateInvaderPattern(invaderGrid, 8, 8);  // Generate the pattern
    
    
  }
  drawInvader(150, 240 + 50 * sin(millis()/1000.0), 5, invaderGrid, 8, 8);  // Draw the invader
  drawInvader(650, 240 - 50 * sin(millis()/1000.0), 5, invaderGrid, 8, 8);  // Draw the invader
  display.drawBitmap(0, 0, cnv.getBuffer(), cnv.width(), cnv.height(), GC9A01A_GREEN);

}

void generateInvaderPattern(bool grid[][8], int invLength, int invHeight) {
  float maxVal = 0.0;
  uint8_t actualInvLength = int(random(5, invLength + 1));
  uint8_t delta = invLength - actualInvLength;
  float softGrid[invLength][invHeight];
  for (uint8_t i = 0; i < delta; i++) {
    for (uint8_t j = 0; j < invHeight; j++) {
      softGrid[i][j] = 0;
    }
  }
  for (uint8_t i = delta; i < invLength; i++) {
    for (uint8_t j = 0; j < invHeight; j++) {
      float val = random(200) / 100.0;  // Random value between 0 and 2
      val += sin(PI * 90 * (i - delta) / invLength / 180);
      val += sin(PI * 180 * j / invHeight / 180);
      maxVal = max(maxVal, val);
      softGrid[i][j] = val;
    }
  }

  // Normalizing and calculating the threshold
  float sum = 0;
  uint8_t count = 0;
  for (uint8_t i = 0; i < invLength; i++) {
    for (uint8_t j = 0; j < invHeight; j++) {
      softGrid[i][j] /= maxVal;
      sum += softGrid[i][j];
      if (softGrid[i][j] != 0) {
        count++;
      }
    }
  }
  float threshold = sum / count;
  // Update grid with boolean values
  for (uint8_t i = 0; i < invLength; i++) {
    for (uint8_t j = 0; j < invHeight; j++) {
      grid[i][j] = false;
      grid[i][j] = softGrid[i][j] > threshold;
    }
  }
}

void drawInvader(int x, int y, int pixelSize, bool invaderGrid[][8], int invLength, int invHeight) {
  int topLeftX = x;
  int topLeftY = y;
  for (int isMirrored = 0; isMirrored <= 1; isMirrored++) {
    for (int i = 0; i < invLength; i++) {
      for (int j = 0; j < invHeight; j++) {
        if (invaderGrid[isMirrored ? invLength - i - 1 : i][j]) {
          int xPos = topLeftX + (isMirrored ? i : i - invLength) * pixelSize;
          int yPos = topLeftY + j * pixelSize - invHeight / 2 * pixelSize;
          cnv.fillRect(xPos, yPos, pixelSize, pixelSize, GC9A01A_GREEN);
        }
      }
    }
  }
}
