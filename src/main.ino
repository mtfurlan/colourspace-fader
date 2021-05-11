


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
// brightness out of 255
#define BRIGHTNESS          42

CRGB leds[NUM_LEDS];

void setup()
{
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection( TypicalLEDStrip );

    FastLED.setBrightness( BRIGHTNESS );
}


#define MIN_COLOUR_DIFF .42
#define HUE_INCREMENT .01
void incrementHue(CGFloat* R, CGFloat* G, CGFloat* B)
{
    static CGFloat l = 42;
    static CGFloat c = 100;
    static CGFloat h = 0;

    h += HUE_INCREMENT;
    if(h > 360) {
        h = 0;
    }
    CIELCHab2RGB(l, c, h,
            R, G, B);
}
void loop()
{
    static CGFloat last_L;
    static CGFloat last_a;
    static CGFloat last_b;
    CGFloat next_L;
    CGFloat next_a;
    CGFloat next_b;

    CGFloat R, G, B;

    incrementHue(&R, &G, &B);
    RGB2CIELab(R, G, B, &next_L, &next_a, &next_b);

    //while we are still too close to the last colour, keep going
    while(CIELAB_DELTA_E_76(last_L, last_a, last_b,
                next_L, next_a, next_b) < MIN_COLOUR_DIFF) {
        incrementHue(&R, &G, &B);
        RGB2CIELab(R, G, B, &next_L, &next_a, &next_b);
    }

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
