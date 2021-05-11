#ifndef COLOUR_CONVERT_H
#define COLOUR_CONVERT_H

#include "yy_color_converter.h"

#include <stdint.h>

void CIELCHab2RGB(CGFloat l, CGFloat c, CGFloat h,
        CGFloat* R, CGFloat* G, CGFloat* B);

void RGB2CIELab(CGFloat R, CGFloat G, CGFloat B,
                CGFloat* L, CGFloat* a, CGFloat* b);

void CIELCHab2RGB_uint8_t(CGFloat l, CGFloat c, CGFloat h,
        uint8_t* r, uint8_t* g, uint8_t* b);

// take 0-1 float, return 0-255
uint8_t clampConvert(CGFloat n);

CGFloat CIELAB_DELTA_E_76(CGFloat L1, CGFloat a1, CGFloat b1,
        CGFloat L2, CGFloat a2, CGFloat b2);

CGFloat CIELAB_DELTA_E_94(CGFloat L1, CGFloat a1, CGFloat b1,
        CGFloat L2, CGFloat a2, CGFloat b2);
#endif // COLOUR_CONVERT_H
