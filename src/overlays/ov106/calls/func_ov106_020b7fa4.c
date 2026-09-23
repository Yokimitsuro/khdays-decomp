/* Brightness fade of the ov106 scene: the fade of the active screen (+0x8e18 pair, picked by +0x8e48)
 * advances one step while the fade task runs (020b8a34) and the ov022 menu is closed, interpolating its
 * level between +0 and +4 over +0xc steps (clamped to +/-16); the level is applied to that screen and
 * the other one is reset. */
typedef struct { int from; int to; int step; int steps; int level; } Fade;
struct Ov106Fades { char pad[0x8e18]; Fade fades[2]; };

extern char *data_ov106_020b8b60;
extern int func_ov106_020b8a34(int param_1);
extern int func_ov022_02084028(void);
extern int func_02020400(int a, int b);
extern void G2x_SetBlendBrightness_(void *pReg, int nPlaneMask, int nBrightness);

void func_ov106_020b7fa4(void)
{
    Fade *fade = &((struct Ov106Fades *)data_ov106_020b8b60)->fades[*(int *)(data_ov106_020b8b60 + 0x8e48) == 0];

    if (func_ov106_020b8a34(1) == 0) {
        return;
    }
    if (func_ov022_02084028() != 0) {
        return;
    }
    if (fade->step < fade->steps) {
        int from;

        fade->step++;
        from = fade->from;
        fade->level = from + func_02020400((fade->to - from) * fade->step, fade->steps);
        if (fade->level > 0x10) {
            fade->level = 0x10;
        }
        if (fade->level < -0x10) {
            fade->level = -0x10;
        }
    }
    if (*(int *)(data_ov106_020b8b60 + 0x8e48) == 1) {
        G2x_SetBlendBrightness_((void *)0x04000050, 1, 0);
        G2x_SetBlendBrightness_((void *)0x04001050, 1, fade->level);
    } else {
        G2x_SetBlendBrightness_((void *)0x04000050, 1, fade->level);
        G2x_SetBlendBrightness_((void *)0x04001050, 1, 0);
    }
}
