#include <colourConvert.h>
#include <unity.h>



// CIE/RGB conversion calculator http://www.brucelindbloom.com/index.html?ColorCalculator.html
// CIE/RGB conversion calculator http://www.easyrgb.com/en/convert.php#inputFORM
// CIE75 ΔE calculato: http://colormine.org/delta-e-calculator

void test_CIELCHab2RGB_red(void) {
    CGFloat l = 53.241;
    CGFloat c = 104.552;
    CGFloat h = 39.999;
    CGFloat R = 1;
    CGFloat G = 0;
    CGFloat B = 0;
    CGFloat _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}
void test_CIELCHab2RGB_green(void) {
    CGFloat l = 87.7347;
    CGFloat c = 119.7759;
    CGFloat h = 136.0160;
    CGFloat R = 0;
    CGFloat G = 1;
    CGFloat B = 0;
    CGFloat _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}
void test_CIELCHab2RGB_blue(void) {
    CGFloat l = 32.2970;
    CGFloat c = 133.8076;
    CGFloat h = 306.2849;
    CGFloat R = 0;
    CGFloat G = 0;
    CGFloat B = 1;
    CGFloat _R, _G, _B;
    CIELCHab2RGB(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL_FLOAT(R, round(_R));
    TEST_ASSERT_EQUAL_FLOAT(G, round(_G));
    TEST_ASSERT_EQUAL_FLOAT(B, round(_B));
}

void test_CIELCHab2RGB_purple_uint8_t(void) {
    CGFloat l = 32.9025;
    CGFloat c = 63.7335;
    CGFloat h = 312.2874;
    CGFloat R = 102;
    CGFloat G = 51;
    CGFloat B = 153;
    uint8_t _R, _G, _B;
    CIELCHab2RGB_uint8_t(l, c, h, &_R, &_G, &_B);
    TEST_ASSERT_EQUAL(R, _R);
    TEST_ASSERT_EQUAL(G, _G);
    TEST_ASSERT_EQUAL(B, _B);
}

void test_CIELAB_DELTA_E_76(void) {
    CGFloat L1 = 43.85681447436276;
    CGFloat a1 = 77.07621305817636;
    CGFloat b1 = -88.41197970043207;
    CGFloat L2 = 32.683692101535776;
    CGFloat a2 = 67.1664527102051;
    CGFloat b2 = -63.05028108783548;
    CGFloat delta_e = CIELAB_DELTA_E_76(L1, a1, b1, L2, a2, b2);
    TEST_ASSERT_EQUAL_FLOAT(29.4323, delta_e);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_CIELCHab2RGB_red);
    RUN_TEST(test_CIELCHab2RGB_green);
    RUN_TEST(test_CIELCHab2RGB_blue);
    RUN_TEST(test_CIELCHab2RGB_purple_uint8_t);
    RUN_TEST(test_CIELAB_DELTA_E_76);

    UNITY_END();
}
