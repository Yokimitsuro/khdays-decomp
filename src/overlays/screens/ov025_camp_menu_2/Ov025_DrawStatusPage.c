/* Ov025_DrawStatusPage -- Ov008_DrawStatusPage (712 B, 36 relocs).
 * Stats/status menu page render state. Draws six labelled stat fields (record indices 4,7,5,8,6,0xc
 * off ctx+0x58) into the ctx+0x118 layer, then pushes the numeric values through the variadic
 * setter Ov025_DrawPageBElement (ids 1, 9, 0xe, 0x10, 0x14, 0x12, 0x13, 0xf) sourced from the global
 * record at gGameState and from game-state field 0x44e. When LoadGlobalShort (GetLanguage)
 * reports state 3 it briefly swaps ctx+0x138 around the fourth draw. A message-record scan
 * (MsgDb_FetchRecord / DispatchByNodeKind) over up to 99 entries computes a remaining count that feeds the
 * final eb64(0xf) call, then it builds the menu list and enqueues the five layer gfx commands.
 *
 * Ov025_DrawPageBElement is variadic (id, flag, ...): the callers pass zero, one, or two value
 * registers. eq3/counter must be declared before uVar9 so the coalesced eq3+counter live range
 * takes r7 and uVar9 takes r8, matching the ROM. */

#include "nitro/types.h"

extern char *gGameState;

extern int   Ov025_GetCtxBlock968c(void);
extern int   Ov025_GetDescriptor3(void);
extern int  *Ov025_GetVarRecordByIndex(int base, int id);
extern void  Text_DrawWithShadow(int dctx, int x, int y, int mode, int rec, int flag);
extern int   GetLanguage(void);
extern int Ov025_DrawPageBElement(int param_1, int param_2, ...);
extern int   GameState_GetField(int id, int field);
extern void  MsgDb_FetchRecord(int *rec, int a, int b, int c);
extern void  DispatchByNodeKind(int *rec);
extern void  Ov025_BuildMenuList(void *ids);
extern void  EnqueueObjGfxCommand(int dctx);

void Ov025_DrawStatusPage(int ctx)
{
    int eq3, counter;
    int uVar9 = 0;
    int local_28 = 0;
    int a = Ov025_GetCtxBlock968c();
    int b = Ov025_GetDescriptor3();
    int *rec;

    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 4);
    Text_DrawWithShadow(ctx + 0x118, 5, 7, 0xf2, (int)rec, 1);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 7);
    Text_DrawWithShadow(ctx + 0x118, 0x59, 7, 0xf2, (int)rec, 1);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 5);
    Text_DrawWithShadow(ctx + 0x118, 5, 0x17, 0xf2, (int)rec, 1);

    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 8);
    eq3 = GetLanguage() == 3;
    if (eq3)
        *(int *)(ctx + 0x138) = b;
    Text_DrawWithShadow(ctx + 0x118, 0x59, 0x17, 0xf2, (int)rec, 1);
    if (eq3)
        *(int *)(ctx + 0x138) = a;

    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 6);
    Text_DrawWithShadow(ctx + 0x118, 5, 0x27, 0xf2, (int)rec, 1);
    rec = Ov025_GetVarRecordByIndex(ctx + 0x58, 0xc);
    Text_DrawWithShadow(ctx + 0x118, 5, 0x57, 0xf2, (int)rec, 1);

    Ov025_DrawPageBElement(1, 0);
    Ov025_DrawPageBElement(9, 0, 0x64);
    Ov025_DrawPageBElement(0xe, 0, *(int *)(gGameState + 4));
    Ov025_DrawPageBElement(0x10, 0, 0);
    Ov025_DrawPageBElement(0x14, 0, 6);
    Ov025_DrawPageBElement(0x12, 0, *(u16 *)(gGameState + 0x196a),
                        *(u16 *)(gGameState + 0x1968));
    if (GameState_GetField(0x44e, 3) != 0)
        Ov025_DrawPageBElement(0x13, 0, GameState_GetField(0x44e, 3) + 0xe);

    counter = 1;
    while (1) {
        int uVar7, field4;
        MsgDb_FetchRecord(&local_28, 0x1c, counter, 0xe);
        uVar7 = *(int *)(local_28 + 0xc);
        if (uVar7 < 0) {
            uVar9 = -1;
            DispatchByNodeKind(&local_28);
            break;
        }
        field4 = *(int *)(gGameState + 4);
        if ((unsigned)uVar7 > (unsigned)field4) {
            uVar9 = uVar7 - field4;
            DispatchByNodeKind(&local_28);
            break;
        }
        DispatchByNodeKind(&local_28);
        counter++;
        if (counter >= 0x64)
            break;
    }

    Ov025_DrawPageBElement(0xf, 0, uVar9);
    Ov025_BuildMenuList(gGameState + 0xee0);
    EnqueueObjGfxCommand(ctx + 0x64);
    EnqueueObjGfxCommand(ctx + 0xa0);
    EnqueueObjGfxCommand(ctx + 0xdc);
    EnqueueObjGfxCommand(ctx + 0x118);
    EnqueueObjGfxCommand(ctx + 0x154);
}
