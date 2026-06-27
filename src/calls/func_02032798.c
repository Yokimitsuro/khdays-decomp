extern void G2x_SetBlendAlpha_(unsigned int reg, int a, int b, int c, int d);

void func_02032798(char *p, int alpha) {
    if (*(int *)(p + 0x4604) == 2)
        G2x_SetBlendAlpha_(0x04001050, 0, alpha, 0x10, 0);
    else
        G2x_SetBlendAlpha_(0x04000050, 0, alpha, 0x10, 0);
}
