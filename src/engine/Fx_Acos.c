/* Arc cosine of an fx32 value as an angle index (0 for 1.0 and above, a half turn for -1.0 and
 * below), via the angle of (sqrt(1 - x^2), x). */

extern int FX_Sqrt(int x);
extern short FX_Atan2(int x, int y);

int Fx_Acos(int x)
{
    int y;

    if (x > -0x1000) {
        if (x >= 0x1000)
            return 0;

        y = (int)(((long long)(0x1000 - x) * (x + 0x1000) + 0x800) >> 12);
        return FX_Atan2(FX_Sqrt(y), x);
    }

    return 0x3244;
}
