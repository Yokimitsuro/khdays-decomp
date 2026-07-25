/* Card / save-check polling state for the Load screen.
 *
 * Sub-state 0 waits out a delay measured against the 64-bit tick counter, then polls
 * the check; result 3 raises the busy/phase pair and parks in sub-state 3, any other
 * non-negative result starts the three-step scan. Sub-state 1 runs that scan one step
 * per frame and, when the third step reports 2, clears the current slot, recounts how
 * many slots hold data and refreshes the selection draw. Sub-state 2 waits for A or B
 * and returns the scene to state 2.
 *
 * CODEGEN NOTES:
 *
 *  1. The two 16-bit halves at +0x6a48 are BITFIELDS (`unsigned wBusy : 16;
 *     unsigned wPhase : 16;`), not two u16 members. mwcc emits the ROM's
 *     read/mask/or/write on the whole word for a bitfield store; two u16 members
 *     would give plain strh.
 *
 *  2. The 64-bit divide is called EXPLICITLY as func_02020368 rather than written as
 *     `(t << 6) / 0x82ea`. The division operator produces identical bytes, but mwcc
 *     emits the relocation against its runtime helper name `_ll_sdiv`, and the delink
 *     config knows that address as func_02020368 -- so the bytes match and
 *     verify_idx reports a reloc mismatch. Where a compiler runtime helper is
 *     involved, the call has to be spelled with the address symbol the config uses.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef long long      s64;
typedef unsigned long long u64;

typedef struct Ov000CardSlot {
    u8  pad_00[0x10];
    int nSlotKind;
    int nSlotState;
    u8  pad_18[8];
} Ov000CardSlot;

typedef struct Ov000CardContext {
    u8  pad_0000[0x4ad0];
    int nActiveState;
    u8  pad_4ad4[0x4adc - 0x4ad4];
    int nAdvance;
    int nCheckState;
    u8  pad_4ae4[0x4afb - 0x4ae4];
    u8  bStepDone;
    u8  pad_4afc[0x4b08 - 0x4afc];
    int nPageIndex;
    u8  pad_4b0c[0x4b10 - 0x4b0c];
    Ov000CardSlot aSlot[3];
    u8  pad_4b70[0x4d94 - 0x4b70];
    int nIdleTicks;
    u8  pad_4d98[0x6a48 - 0x4d98];
    unsigned wBusy : 16;
    unsigned wPhase : 16;
    int nSlotCount;
    int nRetry;
    u8  pad_6a54[0x6a58 - 0x6a54];
    u32 dwCheckDelay;
} Ov000CardContext;

extern Ov000CardContext *data_ov000_0205ac24;
extern u16 data_0204c190;

extern s64  func_020031d4(void);
extern s64  func_02020368(u32 nLo, u32 nHi, u32 dLo, u32 dHi);
extern int  func_ov000_0204f6e0(void);
extern int  func_ov000_0204fc64(int step);
extern void func_020208f0(void);
extern void func_ov000_020506d0(void);
extern void func_ov000_02051470(void);
extern void func_ov000_0205042c(int a, int b, int c);
extern void func_ov000_020505e4(int mode, int page);
extern void func_02033b78(int a, int id);

void func_ov000_020529c4(void)
{
    Ov000CardContext *ctx = data_ov000_0205ac24;
    int done = 0;
    int i;

    switch (ctx->nCheckState) {
    case 0:
        {
            int r;
            s64 t = func_020031d4() << 6;
            if ((u64)func_02020368((u32)t, (u32)((u64)t >> 32), 0x82ea, 0)
                    < data_ov000_0205ac24->dwCheckDelay) {
                r = -1;
            } else {
                r = func_ov000_0204f6e0();
            }
            if (r == 3) {
                data_ov000_0205ac24->wBusy = 1;
                data_ov000_0205ac24->wPhase = 1;
                data_ov000_0205ac24->nIdleTicks = 0;
                data_ov000_0205ac24->nCheckState = 3;
                return;
            }
            if (r >= 0) {
                data_ov000_0205ac24->nCheckState = 1;
                data_ov000_0205ac24->nAdvance = 0;
                data_ov000_0205ac24->nRetry = 0;
            }
        }
        break;
    case 1:
        if (func_ov000_0204fc64(ctx->nAdvance) == 2) {
            data_ov000_0205ac24->nAdvance++;
            data_ov000_0205ac24->bStepDone = 0;
            if (data_ov000_0205ac24->nAdvance >= 3) {
                func_020208f0();
                data_ov000_0205ac24->nCheckState = 2;
                data_ov000_0205ac24->nIdleTicks = 0;
                data_ov000_0205ac24->aSlot[data_ov000_0205ac24->nPageIndex].nSlotKind = 0;
                data_ov000_0205ac24->aSlot[data_ov000_0205ac24->nPageIndex].nSlotState = 0;
                data_ov000_0205ac24->nSlotCount = 0;
                for (i = 0; i < 3; i++) {
                    if (data_ov000_0205ac24->aSlot[i].nSlotKind > 0) {
                        data_ov000_0205ac24->nSlotCount++;
                    }
                }
                func_ov000_020506d0();
            }
        }
        break;
    case 2:
        switch (data_0204c190) {
        case 1:
            done = 1;
            func_02033b78(0, 1);
            break;
        case 2:
            done = 1;
            func_02033b78(0, 3);
            break;
        }
        break;
    }

    if (done == 0) {
        return;
    }
    func_ov000_0205042c(0, 0, 1);
    func_ov000_020506d0();
    func_ov000_02051470();
    func_ov000_020505e4(1, data_ov000_0205ac24->nPageIndex);
    data_ov000_0205ac24->nIdleTicks = 0;
    data_ov000_0205ac24->nActiveState = 2;
}
