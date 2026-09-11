/* Turn `currentAngle` toward `targetAngle` by the angular delta between them
 * (via acos of the cosine of the difference, computed through the sin/cos
 * table), then move `currentAngle` by `maxStep` in whichever rotational
 * direction (sign of sin(current-target)) closes that delta. Optionally
 * reports the unsigned delta angle through `outAngle`. */
extern int func_0203cd20(int c);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

int func_0203d040(int currentAngle, int targetAngle, int maxStep, int *outAngle) {
    unsigned int it = ANG2IDX(targetAngle);
    int sinT = data_0203d210[it * 2 + 1];
    unsigned int ic = ANG2IDX(currentAngle);
    int sinC = data_0203d210[ic * 2 + 1];
    int cosT = data_0203d210[it * 2];
    int cosC = data_0203d210[ic * 2];
    int cosDiff = (int)(((long long)cosT * cosC + (long long)sinT * sinC + 0x800) >> 12);
    int ang = func_0203cd20(cosDiff);
    int result;

    if ((long long)cosT * sinC - (long long)sinT * cosC > 0) {
        result = currentAngle + FX_MUL(ang, maxStep);
    } else {
        result = currentAngle - FX_MUL(ang, maxStep);
    }
    if (outAngle != 0) {
        *outAngle = ang;
    }
    return result;
}
