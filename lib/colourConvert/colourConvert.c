#include "colourConvert.h"
#include "yy_color_converter.h"
#include <stdbool.h>

void CIELCHab2RGB(double l, double c, double h,
        double* R, double* G, double* B)
{
    double L, a, b;
    double X, Y, Z;
    CIELCHab2CIELab(l, c, h, &L, &a, &b);
    CIELab2CIEXYZ(yy_illuminant_D65,
                   L, a, b,
                   &X, &Y, &Z);
    CIEXYZ2RGBDefault( X, Y, Z,
                    R, G, B);
}

void RGB2CIELab(double R, double G, double B,
                double* L, double* a, double* b)
{
    double X, Y, Z;
    RGB2CIEXYZDefault(R, G, B,
                      &X, &Y, &Z);
    CIEXYZ2CIELab(yy_illuminant_D65,
                   X, Y, Z,
                   L, a, b);
}

double CIELAB_DELTA_E_76(double L1, double a1, double b1,
        double L2, double a2, double b2)
{
    return sqrt(pow(L2-L1, 2) + pow(a2-a1, 2) + pow(b2-b1, 2));
}

// http://www.brucelindbloom.com/index.html?Eqn_DeltaE_CIE94.html
double CIELAB_DELTA_E_94(double L_1, double a_1, double b_1,
        double L_2, double a_2, double b_2)
{
    bool textiles = false; //TOOD param or something

    double C_1 = sqrt(pow(a_1, 2) + pow(b_1, 2));
    double C_2 = sqrt(pow(a_2, 2) + pow(b_2, 2));
    double delta_L = L_1 - L_2;
    double delta_C = C_1 - C_2;
    double delta_a = a_1 - a_2;
    double delta_b = b_1 - b_2;
    // not sqrting ΔH cause we pow it later.
    double delta_H_pow2 = pow(delta_a, 2) + pow(delta_b, 2) - pow(delta_C, 2);

    double S_L = 1;
    double K_C = 1;
    double K_H = 1;

    double K_L = 1;
    double K_1 = 0.045;
    double K_2 = 0.015;

    if(textiles) {
        K_L = 2;
        K_1 = 0.048;
        K_2 = 0.014;
    }

    double S_C = 1 + K_1 * C_1;
    double S_H = 1 + K_2 * C_1;

    return sqrt(pow(delta_L/(K_L*S_L), 2) + pow(delta_C/(K_C*S_C), 2) + delta_H_pow2/pow((K_H*S_H), 2));
}

void CIELCHab2RGB_uint8_t(double l, double c, double h,
        uint8_t* r, uint8_t* g, uint8_t* b)
{
    double R, G, B;
    CIELCHab2RGB(l, c, h,
        &R, &G, &B);

    // sRGB values out of yy_color_converter are 0-1, but might be outside that range.
    *r = clampConvert(R);
    *g = clampConvert(G);
    *b = clampConvert(B);
}

uint8_t clampConvert(double n)
{
    n *= 255;
    n = n > 255 ? 255 : n;
    return (uint8_t)round(n < 0 ? 0 : n);
}
