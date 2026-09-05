extern int func_ov024_02084e68(void);
extern void GXx_SetMasterBrightness_(volatile unsigned short *reg,
                                    int brightness);

#define REG_MASTER_BRIGHT_MAIN ((volatile unsigned short *)0x0400006c)
#define REG_MASTER_BRIGHT_SUB  ((volatile unsigned short *)0x0400106c)

void func_ov012_0205ac40(char *context) {
    char *base;
    int step;
    int level;

    base = context;
    context += 0x8000;
    step = *(int *)(context + 0xbe8);
    if (step < 0) {
        if (func_ov024_02084e68() <= 0) {
            return;
        }
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_SUB, 0);
        return;
    }
    if (step >= 0x10) {
        return;
    }
    *(int *)(context + 0xbe8) = step + 1;
    if (*(int *)(context + 0xbe4) == 0) {
        level = -*(int *)(context + 0xbe8);
    } else {
        level = *(int *)(context + 0xbe8);
    }
    GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_SUB, level);
    if (level >= *(int *)(base + 0x8bf4)) {
        level = *(int *)(base + 0x8bf4);
    }
    GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_MAIN, level);
}
