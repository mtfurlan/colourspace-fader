


extern "C" {
#include <colourConvert.h>
}

#include <Arduino.h>
#include <FastLED.h>


#define LED_PIN     D4

#define DATA_PIN            D4
#define NUM_LEDS            3
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

CRGB leds[NUM_LEDS];

void setup()
{
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );
}


#define MIN_COLOUR_DIFF .42
#define HUE_INCREMENT .01
void incrementHue(double* R, double* G, double* B)
{
    static double l = 10;
    static double c = 100;
    static double h = 0;

    h += HUE_INCREMENT;
    if(h > 360) {
        h = 0;
    }
    CIELCHab2RGB(l, c, h,
            R, G, B);
}
void loop()
{
    static double last_L;
    static double last_a;
    static double last_b;
    double next_L;
    double next_a;
    double next_b;

    double R, G, B;

    //while we are still too close to the last colour, keep going
    do {
        incrementHue(&R, &G, &B);
        RGB2CIELab(R, G, B, &next_L, &next_a, &next_b);
    } while(CIELAB_DELTA_E_94(last_L, last_a, last_b,
                next_L, next_a, next_b) < MIN_COLOUR_DIFF)

    last_L = next_L;
    last_a = next_a;
    last_b = next_b;


    //static char buf[64];
    //sprintf(buf, "CIElch: %f, %f, %f\r\nRGB: %03d, %03d, %03d",
    //        l, c, h, clampConvert(R), clampConvert(G), clampConvert(B));
    //Serial.println(buf);

    fill_solid(leds, NUM_LEDS, CRGB(clampConvert(R), clampConvert(G), clampConvert(B)));
    FastLED.show();
}
