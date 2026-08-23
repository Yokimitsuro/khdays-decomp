/*
 * Ov002_PollPageTouches - read every slot's touch and route it.
 *
 * Each of the four slots is read in turn. A touch inside the board goes to the
 * page under it, and a slot other than the local one that still holds something
 * marks the board as changed; a touch outside the board, or on a slot with
 * nothing to report, releases whatever that slot was holding.
 *
 * Whatever was read is kept as the slot's last touch, so the next pass can tell
 * a press from a hold.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    u16 wX;
    u16 wY;
    u16 wButtons;
    char pad006[2];
} Ov002TouchInput;

typedef struct {
    char pad000[4];
    int nSlot;
    char pad008[0xc];
    int bDirty;
    int aFlags[4];
} Ov002TabCtx;

typedef struct {
    char pad000[0xc];
    char aLast[4];
    u16 wButtons;
    char pad012[2];
} Ov002TabSlot;

extern Ov002TabCtx *data_ov002_0207f99c;
extern Ov002TabSlot data_ov002_0207f9a0[];

extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern int func_02030788(void);

extern int func_ov002_02066e40(Ov002TouchInput *pOut, u8 nSlot);
extern void func_ov002_020659f0(int nSlot, Ov002TouchInput *pInput);
extern void func_ov002_02065bc0(int nSlot, Ov002TouchInput *pInput);

int func_ov002_02065e54(void)
{
    Ov002TabCtx *ctx;
    int i;
    int nOwner;
    Ov002TouchInput input;
    Ov002TabSlot *pSlot;

    ctx = data_ov002_0207f99c;
    nOwner = func_02030788();
    pSlot = data_ov002_0207f9a0;

    for (i = 0; i < 4; i++) {
        ctx->nSlot = i;
        if (func_ov002_02066e40(&input, (u8)i) != 0) {
            if (input.wX >= 0x18 && input.wX < 0xe8 &&
                input.wY >= 0x20 && input.wY < 0x88) {
                func_ov002_020659f0(i, &input);
                if (i != nOwner && ctx->aFlags[i] != 0) {
                    ctx->bDirty = 1;
                }
            } else {
                func_ov002_02065bc0(i, &input);
                ctx->aFlags[i] = 0;
            }
            MI_CpuCopy8(&input, pSlot->aLast, 8);
        } else {
            ctx->aFlags[i] = 0;
            pSlot->wButtons = 0;
        }
        pSlot++;
    }
    return 0;
}
