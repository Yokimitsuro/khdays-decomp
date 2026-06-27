extern int FX_Sqrt(int x);
extern int func_020050b4(int x, int y);

int func_0203cd20(int x)
{
    int y;

    if (x > -0x1000) {
        if (x >= 0x1000)
            return 0;

        y = (int)(((long long)(0x1000 - x) * (x + 0x1000) + 0x800) >> 12);
        return func_020050b4(FX_Sqrt(y), x);
    }

    return 0x3244;
}
