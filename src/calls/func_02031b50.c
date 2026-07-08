extern int func_02031b2c();
extern int func_02011f60();
unsigned int func_02031b50(int param_1, int *param_2)
{
    int a = func_02031b2c(param_1);
    unsigned int v;
    a = func_02011f60((int)(param_2 + 0xd), a);
    v = *param_2 + a;
    switch (param_2[2] >> 0x14 & 3) {
    case 0: return (v + 0x1f) & 0xffffffe0;
    case 1: return (v + 0x3f) & 0xffffffc0;
    case 2: return (v + 0x7f) & 0xffffff80;
    case 3: return (v + 0xff) & 0xffffff00;
    }
    return v;
}
