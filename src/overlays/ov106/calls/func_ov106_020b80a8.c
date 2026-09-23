/* Blend the ov106 fade layer: the current fade level (ov002 02053dc4) weights plane 8 against planes
 * 0x21 (level / 16 - level) on the main engine, or on the sub engine while +0x8e48 is 1. */
extern char *data_ov106_020b8b60;
extern int func_ov002_02053dc4(void);
extern void G2x_SetBlendAlpha_(unsigned int reg, int a, int b, int c, int d);

void func_ov106_020b80a8(void)
{
    int level = func_ov002_02053dc4();

    if (*(int *)(data_ov106_020b8b60 + 0x8e48) == 1) {
        G2x_SetBlendAlpha_(0x04000050, 8, 0x21, level, 0x10 - level);
    } else {
        G2x_SetBlendAlpha_(0x04001050, 8, 0x21, level, 0x10 - level);
    }
}
