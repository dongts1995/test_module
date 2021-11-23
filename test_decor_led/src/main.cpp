#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 40
#define NUMPIXELS 18

int rand1, rand2, rand3;

unsigned long g_prev_status_led = 0;
uint8_t state_led = 0;
uint8_t j_in_state = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 5000 // Time (in milliseconds) to pause between pixels
#define WARNING_BLINK_RATE 3
#define RANDOM_RATE 10

#define RGB_RED pixels.Color(255, 0, 0)
#define RGB_GREEN pixels.Color(0, 255, 0)
#define RGB_BLUE pixels.Color(0, 0, 255)
#define RGB_WHITE pixels.Color(127, 127, 127)

void Warning_state();
void Blink_random();
void Charging_state();
void Waiting_state();
void Normal_state();
uint32_t Wheel(byte WheelPos);

void setup()
{
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20);
  state_led = 1;
}

void loop()
{
  Normal_state();
}

void Warning_state()
{
  if ((state_led == 1) && ((millis() - g_prev_status_led) >= 1000 / WARNING_BLINK_RATE))
  {
    g_prev_status_led = millis();
    state_led = 2;
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
  }
  else if ((state_led == 2) && ((millis() - g_prev_status_led) >= 1000 / WARNING_BLINK_RATE))
  {
    g_prev_status_led = millis();
    state_led = 1;
    pixels.clear();
  }
  pixels.show();
}

void Blink_random()
{
  if (millis() - g_prev_status_led >= 1000 / RANDOM_RATE)
  {
    g_prev_status_led = millis();
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();
    }
  }
}

void Charging_state()
{
  if (millis() - g_prev_status_led >= 50)
  {
    g_prev_status_led = millis();
    switch (state_led)
    {
    case 1:
    {
      pixels.setPixelColor(j_in_state, RGB_RED);
      pixels.show();
      j_in_state++;
      if (j_in_state > NUMPIXELS)
      {
        state_led = 2;
        j_in_state = 0;
      }
    }
    break;
    case 2:
    {
      pixels.setPixelColor(j_in_state, RGB_GREEN);
      pixels.show();
      j_in_state++;
      if (j_in_state > NUMPIXELS)
      {
        state_led = 3;
        j_in_state = 0;
      }
    }
    break;
    case 3:
    {
      pixels.setPixelColor(j_in_state, RGB_BLUE);
      pixels.show();
      j_in_state++;
      if (j_in_state > NUMPIXELS)
      {
        state_led = 1;
        j_in_state = 0;
      }
    }
    break;

    default:
      break;
    }
  }
}

void Waiting_state()
{
  uint16_t i;
  if (millis() - g_prev_status_led >= 20)
  {
    g_prev_status_led = millis();
    for (i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, Wheel((i + j_in_state) & 255));
    }
    pixels.show();
    j_in_state = (j_in_state + 1) % 256;
  }
}

void Normal_state()
{
  uint16_t i;
  if (millis() - g_prev_status_led >= 5)
  {
    g_prev_status_led = millis();
    for (i = 0; i < pixels.numPixels(); i++)
    {
      pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + j_in_state) & 255));
    }
    pixels.show();
    j_in_state = (j_in_state + 1) % (256 * 5);
  }
}

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}