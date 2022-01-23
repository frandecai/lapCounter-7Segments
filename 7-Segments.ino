#include "TM1637Display.h"

// Define PINs for the displays
#define CLK1 2
#define DIO1 3
#define CLK2 4
#define DIO2 5

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

TM1637Display display1(CLK1, DIO1),  display2(CLK2, DIO2);

// Times for cars
long beginTime1, beginTime2, time1, time2, endTime1, endTime2 = 0;

boolean go1, go2 = false;


void setup()
{
    // Set brightness
    display1.setBrightness(10);
    display2.setBrightness(10);
  
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

    // Start time2 after 15 seconds (for testing)
    if (((millis() / 1000) > 15) && (go2 == false)) {
        beginTime2 = millis();
        go2 = true;
    }
  
    if ((go1 == true) && (time1 <= 3598)) {
        // Time counter
        time1 = (millis() - beginTime1) / 20;
        displayTime(display1, time1);
    }

    if ((go2 == true) && (time2 <= 3598)) {
        time2 = (millis() - beginTime2) / 20;
        displayTime(display2, time2);
    }
}


void displayTime(TM1637Display display, long timeNumber)
{
    // Array for characters
    uint8_t position[] = { 0, 0, 0, 0 };
  
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
