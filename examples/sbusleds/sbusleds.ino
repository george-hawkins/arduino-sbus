#include <SBUS.h>
#include <limits.h>

// Remember to unplug the RX pin of your UNO when uploading this sketch.
SBUS sbus(Serial);

const int LED1 = 5;
const int LED2 = 6;
const int LED3 = 9;
const int LED4 = 10;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  sbus.begin();
}

// This is timer2, which triggers ever 1ms and processes the incoming SBUS datastream.
ISR(TIMER2_COMPA_vect)
{
  sbus.process();
}

static int minChannel = INT_MAX;
static int maxChannel = INT_MIN;

// Scale the S.BUS channel values into the range [0, 255] for use as LED brightness values.
int getChannel(int channel) {
  int value = sbus.getChannel(channel);

  if (value < minChannel) {
    minChannel = value;
  }
  if (value > maxChannel) {
    maxChannel = value;
  }

  float result = value;
  
  result -= minChannel;
  result /= (maxChannel - minChannel);
  result *= 255;

  return (int)result; 
}

void loop()
{
  analogWrite(LED1, getChannel(1));
  analogWrite(LED2, getChannel(2));
  analogWrite(LED3, getChannel(3));
  analogWrite(LED4, getChannel(4));
}
