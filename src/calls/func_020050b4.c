/*
 * func_020050b4 - atan2(x, z) in Q12 fixed-point radians.
 *
 * Confirmed by src/overlays/ov137/calls/func_ov137_020cc9e0.c, which adds
 * PI (0x3244) to this function's result and documents it as "the atan2
 * result". Reduces (x, z) to one of eight symmetric octants by sign and by
 * which axis has the larger magnitude, then looks up the in-octant angle
 * from data_02041210 using FX_Inv of the smaller coordinate as the index,
 * and offsets it from the octant boundary (0, PI/4, PI/2, ...). Each of the
 * eight octant arms and the four axis-aligned/diagonal exact cases collapse
 * to the same handful of return shapes, so the eight live branches just set
 * (ratioVal, chkVal, baseVal, addFlag) and fall into one shared tail.
 *
 * The final angle is always truncated to 16 bits (cast to short) before
 * being widened back to int for the return.
 */

typedef short s16;

extern int FX_Inv(int x);
extern short data_02041210[130];

#define PI              0x3244
#define HALF_PI         0x1922
#define QUARTER_PI      0xc91
#define THREE_QTR_PI    0x25b3

int func_020050b4(int x, int z)
{
    int nx, nz;
    int addFlag, chkVal, ratioVal, baseVal;

    if (x > 0) {
        if (z > 0) {
            if (z > x) {
                ratioVal = x; chkVal = z; baseVal = 0; addFlag = 1;
            } else if (z < x) {
                ratioVal = z; chkVal = x; baseVal = HALF_PI; addFlag = 0;
            } else {
                return QUARTER_PI;
            }
        } else if (z < 0) {
            nz = -z;
            if (nz < x) {
                ratioVal = nz; chkVal = x; baseVal = HALF_PI; addFlag = 1;
            } else if (nz > x) {
                ratioVal = x; chkVal = nz; baseVal = PI; addFlag = 0;
            } else {
                return THREE_QTR_PI;
            }
        } else {
            return HALF_PI;
        }
    } else if (x < 0) {
        nx = -x;
        if (z < 0) {
            nz = -z;
            if (nz > nx) {
                ratioVal = nx; chkVal = nz; baseVal = -PI; addFlag = 1;
            } else if (nz < nx) {
                ratioVal = nz; chkVal = nx; baseVal = -HALF_PI; addFlag = 0;
            } else {
                return -THREE_QTR_PI;
            }
        } else if (z > 0) {
            if (z < nx) {
                ratioVal = z; chkVal = nx; baseVal = -HALF_PI; addFlag = 1;
            } else if (z > nx) {
                ratioVal = nx; chkVal = z; baseVal = 0; addFlag = 0;
            } else {
                return -QUARTER_PI;
            }
        } else {
            return -HALF_PI;
        }
    } else {
        if (z >= 0) {
            return 0;
        }
        return PI;
    }

    if (chkVal == 0) {
        return 0;
    }
    if (addFlag) {
        return (s16)(baseVal + data_02041210[FX_Inv(ratioVal) >> 5]);
    }
    return (s16)(baseVal - data_02041210[FX_Inv(ratioVal) >> 5]);
}
