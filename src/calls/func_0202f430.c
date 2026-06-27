extern int FX_Sqrt(int x);

int func_0202f430(int *v)
{
    int a = v[0];
    int b = v[1];
    int c = v[2];
    int d = v[3];

    return FX_Sqrt((int)(((long long)a * a + 0x800) >> 12)
                 + (int)(((long long)b * b + 0x800) >> 12)
                 + (int)(((long long)c * c + 0x800) >> 12)
                 + (int)(((long long)d * d + 0x800) >> 12));
}
