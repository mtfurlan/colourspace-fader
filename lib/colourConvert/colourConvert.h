#ifndef COLOUR_CONVERT_H
#define COLOUR_CONVERT_H

#include "yy_color_converter.h"

#include <stdint.h>

void CIELCHab2RGB(double l, double c, double h,
        double* R, double* G, double* B);

void RGB2CIELab(double R, double G, double B,
                double* L, double* a, double* b);
void RGB2CIELab_uint8_t(uint8_t R, uint8_t G, uint8_t B,
                double* L, double* a, double* b);

void CIELCHab2RGB_uint8_t(double l, double c, double h,
        uint8_t* r, uint8_t* g, uint8_t* b);

// take 0-1 float, return 0-255
uint8_t clampConvert(double n);

double CIELAB_DELTA_E_76(double L1, double a1, double b1,
        double L2, double a2, double b2);

double CIELAB_DELTA_E_94(double L1, double a1, double b1,
        double L2, double a2, double b2);

double CIELAB_DELTA_E_2000(double L1, double a1, double b1,
        double L2, double a2, double b2);
#endif // COLOUR_CONVERT_H
