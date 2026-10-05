/* Ov008_SaveMenuDrawPrompt -- Ov008_SaveMenuDrawPrompt: redraw the save menu's
 * prompt surface (+0x1a0) for phase nPhase.  The surface is cleared first.
 * Phase 0 (slot pick) writes variable record 1 at (0x62, 0); phase 1
 * (confirm) formats record 2 (slot in use, +0x20 + 0x1c * slot non-zero) or
 * 3 (empty slot) with the 1-based slot number at (0x10, 0) and adds records
 * 5 and 6 (yes / no) at (0x50, 0x12) and (0xae, 0x12) in style 2 with
 * shadow 2; phase 2 (saving) writes record 0xb, phase 3 record 7, and
 * phase 4 (done) record 0xa, or 0xd when the sub-state (+0x240) is 0, in
 * style 4.  The surface is then queued for the graphics engine.
 */

#include "nitro/types.h"

#define PHASE_PICK     0
#define PHASE_CONFIRM  1
#define PHASE_SAVING   2
#define PHASE_WAIT     3
#define PHASE_DONE     4
#define TEXT_CAP       0x80

typedef struct Ov008SaveSlotInfo {
    int bUsed;                /* 0x00 */
    u8  pad_04[0x1c - 0x4];
} Ov008SaveSlotInfo;

typedef struct Ov008SaveMenu {
    int nSlot;                /* 0x000: chosen slot */
    u8  pad_004[0x20 - 0x4];
    Ov008SaveSlotInfo aSlot[3]; /* 0x020 */
    u8  pad_074[0x158 - 0x74];
    u8  varRecords[0xc];      /* 0x158 */
    u8  pad_164[0x1a0 - 0x164];
    u8  promptSurface[0x3c];  /* 0x1a0 */
    u8  pad_1dc[0x240 - 0x1dc];
    int nSubState;            /* 0x240 */
} Ov008SaveMenu;

extern void  Obj_InvokeInnerVtable4(void *pSurface);                                  /* Obj_InvokeInnerVtable4: clear */
extern u16  *Ov008_GetVarRecordByIndex(void *pRecords, int nIndex);                /* GetVarRecordByIndex */
extern void  Ov008_DrawTextNewline(void *pSurface, int nX, int nY, int nStyle, const u16 *pText); /* Ov008_DrawTextNewline */
extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...); /* Text_FormatUtf16 */
extern void  Ov008_DrawWithShadow(void *pSurface, int nX, int nY, int nStyle, const u16 *pText, int nShadow); /* Ov008_DrawWithShadow */
extern void  Text_DrawWithShadow(void *pSurface, int nX, int nY, int nStyle, const u16 *pText, int nShadow); /* Text_DrawWithShadow */
extern void  EnqueueObjGfxCommand(void *pSurface);                                  /* EnqueueObjGfxCommand */

void Ov008_SaveMenuDrawPrompt(Ov008SaveMenu *pMenu, int nPhase)
{
    u16 text[TEXT_CAP];
    int nRecord;
    u16 *pText;

    Obj_InvokeInnerVtable4(pMenu->promptSurface);
    switch (nPhase) {
    case PHASE_PICK:
        Ov008_DrawTextNewline(pMenu->promptSurface, 0x62, 0, 2, Ov008_GetVarRecordByIndex(pMenu->varRecords, 1));
        break;
    case PHASE_CONFIRM:
        if (pMenu->aSlot[pMenu->nSlot].bUsed != 0) {
            nRecord = 2;
        } else {
            nRecord = 3;
        }
        pText = Ov008_GetVarRecordByIndex(pMenu->varRecords, nRecord);
        Text_FormatUtf16(text, TEXT_CAP, pText, pMenu->nSlot + 1);
        Ov008_DrawWithShadow(pMenu->promptSurface, 0x10, 0, 2, text, 0);
        Ov008_DrawWithShadow(pMenu->promptSurface, 0x50, 0x12, 2, Ov008_GetVarRecordByIndex(pMenu->varRecords, 5), 2);
        Ov008_DrawWithShadow(pMenu->promptSurface, 0xae, 0x12, 2, Ov008_GetVarRecordByIndex(pMenu->varRecords, 6), 2);
        break;
    case PHASE_SAVING:
        Text_DrawWithShadow(pMenu->promptSurface, 0x10, 0, 2, Ov008_GetVarRecordByIndex(pMenu->varRecords, 0xb), 0);
        break;
    case PHASE_WAIT:
        Text_DrawWithShadow(pMenu->promptSurface, 0x10, 0, 2, Ov008_GetVarRecordByIndex(pMenu->varRecords, 7), 0);
        break;
    case PHASE_DONE:
        if (pMenu->nSubState != 0) {
            nRecord = 0xa;
        } else {
            nRecord = 0xd;
        }
        Text_DrawWithShadow(pMenu->promptSurface, 0x10, 0, 4, Ov008_GetVarRecordByIndex(pMenu->varRecords, nRecord), 0);
        break;
    }
    EnqueueObjGfxCommand(pMenu->promptSurface);
}
