#include "TM1637Display.h"

#define CLK 2 // Define pino 2 como CLK
#define DIO 3 // Define pino 3 como DIO

// Para configurações personalizadas junto ao display de 7 segmentos
// utiliza-se o seguinte esquema, no qual cada letra representa um segmento:

//      -         A
//    |   |     F   B
//      -         G
//    |   |     E   C
//      -         D

const uint8_t set[] = {
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,          // S
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,          // E
  SEG_A | SEG_B | SEG_G | SEG_E | SEG_D,          // 
};

TM1637Display display(CLK, DIO);

// Time for car 1
long beginTime1, beginTime2, endTime1, endTime2, time1, time2;

boolean go1, go2 = false;


void setup()
{
    // Set brightness
    display.setBrightness(10);
  
    // Set serial console speed
    Serial.begin(9600);
}


void loop()
{
    // Start time1 after 10 seconds (for testing)
    if (((millis() / 1000) > 10) && (go1 == false)) {
        beginTime1 = millis();
        go1 = true;
    }
  
    if ((go1 == true) && (time1 <= 3598)) {
      displayTime(time1);
    }
}


void displayTime(long timeNumber)
{
    // Array for characters
    uint8_t position[] = { 0, 0, 0, 0 };
  
    // Time counter
    time1 = (millis() - beginTime1) / 20;
  
    // Calculation of every digit
    position[0] = display.encodeDigit((timeNumber / 60) / 10); // First character (ten minute)
    position[1] = display.encodeDigit((timeNumber / 60) % 10); // Second character (minute unit)
    position[1] = position[1] + 128;
    position[2] = display.encodeDigit((timeNumber % 60) / 10); // Third character (ten second)
    position[3] = display.encodeDigit((timeNumber % 60) % 10); // Forth character (second unit)

    // Show information on display
    display.setSegments(position);
    Serial.println(timeNumber);
}
