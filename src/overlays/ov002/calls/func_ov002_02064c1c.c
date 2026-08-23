/*
 * Ov002_StepPageScroll - hand the page's characters over and place the layer.
 *
 * The upload happens once, the first time round: the characters go to the sub
 * engine's BG3 and the page moves on to its next state, taking the layer with
 * it if it was still waiting.
 *
 * From then on the layer is parked off screen whenever it is not wanted, and
 * otherwise scrolled so that the page's own position sits under the window.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef volatile unsigned int vu32;

#define REG_BG3OFS_SUB (*(vu32 *)0x0400101c)

typedef struct {
    char pad000[0x10];
    int nCharSize;
    void *pCharData;
} Ov002PageChars;

typedef struct {
    char pad000[8];
    int nX;
    int nY;
    char pad010[0x10];
    u8 nShowState;
    char pad021[3];
    int bDirty;
    u8 nLoadState;
    char pad029[7];
    Ov002PageChars *pChars;
} Ov002PageLayer;

extern Ov002PageLayer *data_ov002_0207f638;

extern void GXS_LoadBG3Char(const void *pSrc, unsigned int nOffset,
                            unsigned int nSize);

void func_ov002_02064c1c(void)
{
    Ov002PageLayer *ctx;

    ctx = data_ov002_0207f638;
    if (ctx->nLoadState == 1) {
        GXS_LoadBG3Char(ctx->pChars->pCharData, 0x39e0, ctx->pChars->nCharSize);
        ctx->nLoadState = 2;
        ctx->bDirty = 1;
        if (ctx->nShowState == 1) {
            ctx->nShowState = 2;
        }
    }

    if (ctx->nShowState < 2) {
        REG_BG3OFS_SUB = ((ctx->nX - 0x68) & 0x1ff) |
                         (((ctx->nY - 0x38) << 16) & 0x1ff0000);
        return;
    }
    REG_BG3OFS_SUB = 0x01c80198;
}
