#include "colourConvert.h"
#include "yy_color_converter.h"

void CIELCHab2RGB(CGFloat l, CGFloat c, CGFloat h,
        CGFloat* R, CGFloat* G, CGFloat* B)
{
    CGFloat L, a, b;
    CGFloat X, Y, Z;
    CIELCHab2CIELab(l, c, h, &L, &a, &b);
    CIELab2CIEXYZ(yy_illuminant_D65,
                   L, a, b,
                   &X, &Y, &Z);
    CIEXYZ2RGBDefault( X, Y, Z,
                    R, G, B);
}

void RGB2CIELab(CGFloat R, CGFloat G, CGFloat B,
                CGFloat* L, CGFloat* a, CGFloat* b)
{
    CGFloat X, Y, Z;
    RGB2CIEXYZDefault(R, G, B,
                      &X, &Y, &Z);
    CIEXYZ2CIELab(yy_illuminant_D65,
                   X, Y, Z,
                   L, a, b);
}

CGFloat CIELAB_DELTA_E_76(CGFloat L1, CGFloat a1, CGFloat b1,
        CGFloat L2, CGFloat a2, CGFloat b2)
{
    return sqrt(pow(L2-L1, 2) + pow(a2-a1, 2) + pow(b2-b1, 2));
}

/*
 *
 *      graphic arts    textiles
 *  k_L 1               2
 *  K_1 0.045           0.048
 *  K_2 0.015           0.014
 */
#define K_L 1
#define K_1 0.045
#define K_2 0.015

CGFloat CIELAB_DELTA_E_94(CGFloat L1, CGFloat a1, CGFloat b1,
        CGFloat L2, CGFloat a2, CGFloat b2)
{
    return 0;
    //CGFloat l1, c1, h1;
    //CGFloat l2, c2, h2;
    //CIELCHab2CIELab(L1, a1, b1, &l1, &c1, &h1);
    //CIELCHab2CIELab(L2, a2, b2, &l2, &c2, &h2);

    //CGFloat K_C = ;
    //CGFloat S_C = ;
    //CGFloat S_C = ;
    //return sqrt(pow((l2-l1)/(K_L*S_L), 2) + pow((c1-c2)/(K_C*S_C), 2) + pow((delta_H/(K_H*S_H), 2));
}

void CIELCHab2RGB_uint8_t(CGFloat l, CGFloat c, CGFloat h,
        uint8_t* r, uint8_t* g, uint8_t* b)
{
    CGFloat R, G, B;
    CIELCHab2RGB(l, c, h,
        &R, &G, &B);

    // sRGB values out of yy_color_converter are 0-1, but might be outside that range.
    *r = clampConvert(R);
    *g = clampConvert(G);
    *b = clampConvert(B);
}

uint8_t clampConvert(CGFloat n)
{
    n *= 255;
    n = n > 255 ? 255 : n;
    return (uint8_t)round(n < 0 ? 0 : n);
}
