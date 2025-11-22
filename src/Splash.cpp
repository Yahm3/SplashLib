#include "../include/Splash.h"
#include "../include/scarfy_data.h"
#include <raylib.h>
#include <raymath.h>

Splash::Splash() {
  Image image = LoadImageFromMemory(".png", SCARFY_PNG, SCARFY_PNG_LEN);
  Texture2D texture = LoadTextureFromImage(image);
  scarfy = texture;
  int w = GetScreenWidth();
  int PADDING = w / 8;
  int base = PADDING;

  position = {base * 1.0f, 0.0f};
  frameRec = {0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height};

  framesCounter = 0;
  currentFrame = 0;
  framesSpeed = 8;
  done = false;
  xPerc = 0.0f;
}

Splash::~Splash() {
  if (IsTextureValid(scarfy)) {
    UnloadTexture(scarfy);
  }
}

bool Splash::isComplete() { return done; }

void Splash::draw() {
  framesCounter++;
  if (framesCounter >= (60 / framesSpeed)) {
    framesCounter = 0;
    currentFrame++;
    if (currentFrame > 5)
      currentFrame = 0;
    frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
  }

  const int MAX_FRAME_SPEED = 15;
  const int MIN_FRAME_SPEED = 1;

  if (framesSpeed > MAX_FRAME_SPEED)
    framesSpeed = MAX_FRAME_SPEED;
  else if (framesSpeed < MIN_FRAME_SPEED)
    framesSpeed = MIN_FRAME_SPEED;

  int w = GetScreenWidth();
  int h = GetScreenHeight();
  int PADDING = w / 8;
  int base = PADDING;

  const char *text = "Grass Games";
  int fontSize = 170;

  int textPosY = (h / 2) + (h / 20);
  Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 0);

  float scarfyPosY = textPosY - frameRec.height - (int)(h / 40);

  float redLinePosY = textPosY + textSize.y + (int)(h / 100);

  if (position.x < 170 * 6.5) {
    position.x++;

    DrawText(text, base, textPosY, fontSize, MAGENTA);

    float maxRedLineWidth = textSize.x;
    float currentRedLineWidth =
        xPerc < maxRedLineWidth ? xPerc++ : maxRedLineWidth;
    DrawRectangle(base, redLinePosY, currentRedLineWidth, 20, RED);

    Vector2 scarfyDrawPosition = {position.x, scarfyPosY};
    DrawTextureRec(scarfy, frameRec, scarfyDrawPosition, RAYWHITE);
  } else {
    done = true;
  }
}
