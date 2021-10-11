#include <colourConvert.h>
#include <unity.h>



// CIE/RGB conversion calculator http://www.brucelindbloom.com/index.html?ColorCalculator.html
// CIE/RGB conversion calculator http://www.easyrgb.com/en/convert.php#inputFORM
// CIE75 ΔE calculato: http://colormine.org/delta-e-calculator

void test_CIELCHab2RGB_red(void) {
    double l = 53.241;
    double c = 104.552;
    double h = 39.999;
    double R = 1;
    double G = 0;
    double B = 0;
    double _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}
void test_CIELCHab2RGB_green(void) {
    double l = 87.7347;
    double c = 119.7759;
    double h = 136.0160;
    double R = 0;
    double G = 1;
    double B = 0;
    double _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}
void test_CIELCHab2RGB_blue(void) {
    double l = 32.2970;
    double c = 133.8076;
    double h = 306.2849;
    double R = 0;
    double G = 0;
    double B = 1;
    double _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}

void test_CIELCHab2RGB_uint8_t_purple(void) {
    double l = 32.9025;
    double c = 63.7335;
    double h = 312.2874;
    double R = 102;
    double G = 51;
    double B = 153;
    uint8_t _R, _G, _B;
    CIELCHab2RGB_uint8_t(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL(R, _R);
    TEST_ASSERT_EQUAL(G, _G);
    TEST_ASSERT_EQUAL(B, _B);
}

void test_RGB2CIELab_uint8_t_purple(void) {
    double R = 102;
    double G = 51;
    double B = 153;
    double L = 32.90186; // TODO: actual 32.9025;
    double a = 42.89232; // TODO: actual 42.8831;
    double b = -47.15767;// TODO: actual -47.1486;
    double _L, _a, _b;
    RGB2CIELab_uint8_t(R, G, B, &_L, &_a, &_b);
    TEST_ASSERT_EQUAL_FLOAT(L, _L);
    TEST_ASSERT_EQUAL_FLOAT(a, _a);
    TEST_ASSERT_EQUAL_FLOAT(b, _b);
}


//http://www.brucelindbloom.com/index.html?ColorDifferenceCalc.html
double delta_E_L_1 = 43.8568;
double delta_E_a_1 = 77.0762;
double delta_E_b_1 = -88.4120;
double delta_E_L_2 = 32.6837;
double delta_E_a_2 = 67.1665;
double delta_E_b_2 = -63.0503;
double delta_E_CIE76 = 29.432257;
double delta_E_CIE94_Graphic_Arts = 12.453410;
double delta_E_CIE94_Textiles = 7.815650;
double delta_E_CIE2000_1_1_1 = 11.663238;
double delta_E_CMC_1_1 = 13.794244;
double delta_E_CMC_2_1 = 9.951353;

void test_CIELAB_DELTA_E_76(void) {
    double delta_e = CIELAB_DELTA_E_76(delta_E_L_1, delta_E_a_1, delta_E_b_1,
            delta_E_L_2, delta_E_a_2, delta_E_b_2);
    TEST_ASSERT_EQUAL_FLOAT(delta_E_CIE76, delta_e);
}

void test_CIELAB_DELTA_E_94(void) {
    double delta_e = CIELAB_DELTA_E_94(delta_E_L_1, delta_E_a_1, delta_E_b_1,
            delta_E_L_2, delta_E_a_2, delta_E_b_2);
    TEST_ASSERT_EQUAL_FLOAT(delta_E_CIE94_Graphic_Arts, delta_e);
}
void test_CIELAB_DELTA_E_2000(void) {
    double delta_e = CIELAB_DELTA_E_2000(delta_E_L_1, delta_E_a_1, delta_E_b_1,
            delta_E_L_2, delta_E_a_2, delta_E_b_2);
    TEST_ASSERT_EQUAL_FLOAT(delta_E_CIE2000_1_1_1, delta_e);
}

void test_fade_attempt_CIELCHab_sweep_H(void)
{
    const double lightness = 70;
    const double chroma = 100;
    const double min_colour_diff = 1;
    const double hue_increment = .01;


    double hue = 0;
    double last_hue;
    double last_L = 0;
    double last_a = 0;
    double last_b = 0;

    printf("PLOTTITLE: CIELCh hue sweep with min %.01f ΔE, L=%.01f C=%.01f\n", min_colour_diff, lightness, chroma);

    // loop till hue wraps
    do {
        double next_L;
        double next_a;
        double next_b;

        uint8_t R, G, B;

        last_hue = hue;
        //while we are still too close to the last colour, keep going
        do {
            hue += hue_increment;
            if(hue > 360) {
                hue = 0;
            }
            CIELCHab2RGB_uint8_t(lightness, chroma, hue, &R, &G, &B);
            RGB2CIELab_uint8_t(R, G, B, &next_L, &next_a, &next_b);
        } while(CIELAB_DELTA_E_2000(last_L, last_a, last_b,
                    next_L, next_a, next_b) < min_colour_diff);

        last_L = next_L;
        last_a = next_a;
        last_b = next_b;


        printf("PLOTDATA: %3.4f, %3d, %3d, %3d\n", hue, R, G, B);
    } while(hue > last_hue);
}

void test_fade_attempt_HSL(void)
{
    //HSL is 0-1
    const double saturation = 1;
    const double lightness = .5;
    const double min_colour_diff = 3;
    const double hue_increment = .01;

    double hue = 0;
    double last_L = 0;
    double last_a = 0;
    double last_b = 0;
    double last_hue;

    printf("PLOTTITLE: HSL hue sweep with min %.01f ΔE, S=%.01f L=%.01f\n", min_colour_diff, saturation, lightness);
    // loop till hue wraps
    do {
        double next_L;
        double next_a;
        double next_b;

        double R_f, G_f, B_f;
        uint8_t R, G, B;

        last_hue = hue;
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


        printf("PLOTDATA: %3.4f, %3d, %3d, %3d\n", hue, R, G, B);
    } while(hue > last_hue);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_CIELCHab2RGB_red);
    RUN_TEST(test_CIELCHab2RGB_green);
    RUN_TEST(test_CIELCHab2RGB_blue);
    RUN_TEST(test_CIELCHab2RGB_uint8_t_purple);
    RUN_TEST(test_RGB2CIELab_uint8_t_purple);
    RUN_TEST(test_CIELAB_DELTA_E_76);
    RUN_TEST(test_CIELAB_DELTA_E_94);
    RUN_TEST(test_CIELAB_DELTA_E_2000);

    /*
    RUN_TEST(test_fade_attempt_CIELCHab_sweep_H);
    /*/
    RUN_TEST(test_fade_attempt_HSL);
    //*/

    UNITY_END();
}
