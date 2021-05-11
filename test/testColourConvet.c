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

void test_CIELCHab2RGB_purple_uint8_t(void) {
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

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_CIELCHab2RGB_red);
    RUN_TEST(test_CIELCHab2RGB_green);
    RUN_TEST(test_CIELCHab2RGB_blue);
    RUN_TEST(test_CIELCHab2RGB_purple_uint8_t);
    RUN_TEST(test_CIELAB_DELTA_E_76);
    RUN_TEST(test_CIELAB_DELTA_E_94);

    UNITY_END();
}
