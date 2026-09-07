typedef unsigned char u8;

/* The player object. The fade state sits far into it, which is why every access
 * below compiles to a base-plus-offset split rather than a single load. */
struct MobiClipPlayer {
    char pad0000[0x8be2];
    u8 nScreens;
    u8 pad8be3;
    int nToWhite;
    int nStep;
};

extern int func_ov024_02084e68(void);
extern void GXx_SetMasterBrightness_(volatile unsigned short *reg, int brightness);

#define REG_MASTER_BRIGHT     ((volatile unsigned short *)0x0400006c)
#define REG_DB_MASTER_BRIGHT  ((volatile unsigned short *)0x0400106c)

void func_ov024_02082960(struct MobiClipPlayer *player) {
    int step;
    int level;

    step = player->nStep;
    if (step < 0) {
        if (func_ov024_02084e68() <= 0) {
            return;
        }
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, 0);
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, 0);
        return;
    }
    if (step >= 0x10) {
        return;
    }
    player->nStep = step + 1;

    level = player->nToWhite == 0 ? -player->nStep : player->nStep;

    switch (player->nScreens) {
    case 0:
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, level);
        break;
    case 1:
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, level);
        break;
    case 2:
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, level);
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, level);
        break;
    }
}
