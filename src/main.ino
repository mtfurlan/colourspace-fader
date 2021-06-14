


extern "C" {
#include <colourConvert.h>
}

#include <Arduino.h>
#include <FastLED.h>


#define LED_PIN     D4

#define DATA_PIN            D2
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

void loop()
{
    const static double saturation = 1;
    const static double lightness = .5;
    const static double min_colour_diff = .01;
    const static double hue_increment = .01;

    double hue = 0;
    static double last_L = 0;
    static double last_a = 0;
    static double last_b = 0;

    double next_L;
    double next_a;
    double next_b;

    double R_f, G_f, B_f;
    uint8_t R, G, B;

    //while we are still too close to the last colour, keep going
    do {
        //incremenmt hue
        hue += hue_increment;
        if(hue > 360) {
            hue = 0;
        }
        HSL2RGB(hue, saturation, lightness, &R_f, &G_f, &B_f);
        R = clampConvert(R_f);
        G = clampConvert(G_f);
        B = clampConvert(B_f);


        RGB2CIELab_uint8_t(R, G, B, &next_L, &next_a, &next_b);
    } while(CIELAB_DELTA_E_2000(last_L, last_a, last_b,
                next_L, next_a, next_b) < min_colour_diff);

    last_L = next_L;
    last_a = next_a;
    last_b = next_b;


    static char buf[512];
    sprintf(buf, "%3.4f, %3d, %3d, %3d\n", hue, R, G, B);
    Serial.print(buf);
    fill_solid(leds, NUM_LEDS, CRGB(R, G, B));
    FastLED.show();
}
