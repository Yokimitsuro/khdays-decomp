#include "game/ov006_mission_mode_select.h"
/* Character select: should the pending input be handed to the confirm state? Refuses while the
 * manager is gone or the scene is locked out (obj+0x4e8). Scenes already in the confirm
 * (Ov006_UpdateAndGetIdleHandler) or cancel (Ov006_IdleStateNoOp) state are accepted as-is. Otherwise the
 * touch must be released, the drag-armed bit 0 at obj+0x42c must be set, and the live key state
 * must differ from the one latched at obj+0x434 -- only then does the scene move to confirm.
 *
 * The old note called this "the ctx-CSE / pool-rematerialisation tie ... not steerable from C":
 * the ROM re-loads &data_ov006_020565e4 from the literal pool three times and the address of
 * Ov006_UpdateAndGetIdleHandler twice, keeping the prologue at `push {r3,lr}`, while mwcc cached both in
 * callee-saved registers. It is steerable, and it took three separate things:
 *
 *   - SPELL EACH POOL-LOAD GROUP DIFFERENTLY. The ROM has three groups, and within a group it
 *     shares the base: (a) the null test + 0x4e8 + the scene pointer at +4, (b) the 0x42c byte,
 *     (c) the 0x434 halfword + the scene pointer again. Writing all of them through one macro
 *     lets mwcc keep one copy in a callee-saved register; writing each group as a different but
 *     equivalent expression -- `*(char **)&sym`, `((char **)&sym)[0]`, `*(char **)((char *)&sym)`,
 *     `((int *)&sym)[1]` -- makes it reload, and the push drops from {r3,r4,r5,lr} to {r4,lr}.
 *   - COMPARE THE STATE AS A FUNCTION POINTER, not as an int. `(void (*)(void))state ==
 *     Ov006_UpdateAndGetIdleHandler` for the two tests and `(int)&Ov006_UpdateAndGetIdleHandler` for the call
 *     argument are the same address spelled two ways, so mwcc stops CSE-ing them into r4 and
 *     re-loads the pool word like the ROM. That is the last callee-saved: push {r3,lr}.
 *   - ONE SHARED `return 0` REACHED BY `goto`. Three separate `return 0;` statements each get
 *     predicated (`movne r0,#0 ; popne`); one label with three predecessors cannot be
 *     if-converted, which is what produces the ROM's three branches to a single exit block.
 *
 * The drag-armed test is a 1-bit bitfield read, not a shift pair: written as
 * `(x << 0x1f) >> 0x1f` mwcc folds the whole thing to `tst r0,#1` because the result is only
 * tested, and the ROM's `lsl #0x1f ; lsrs #0x1f` disappears. */
extern unsigned short WH_GetCurrentAid(void);
extern unsigned short WH_GetBitmap(void);
extern void  Obj_SetField14(int scene, int next);
extern void  Ov006_UpdateAndGetIdleHandler(void);
extern void  Ov006_IdleStateNoOp(void);
#define MISSION_CONTEXT (data_ov006_020565e4.pContext)

typedef struct { unsigned char b0 : 1; unsigned char rest : 7; } Bits8;

int Ov006_ShouldEnterConfirmState(void) {
    int state;
    unsigned int armed;
    int keys;

    if ((char *)data_ov006_020565e4.pContext == 0
        || *(int *)((char *)data_ov006_020565e4.pContext + 0x4e8) != 0) {
        return 0;
    }
    state = *(int *)((int)data_ov006_020565e4.pController + 0x14);
    if ((void (*)(void))state == Ov006_UpdateAndGetIdleHandler) {
        return 1;
    }
    if ((void (*)(void))state == Ov006_IdleStateNoOp) {
        return 1;
    }
    if (WH_GetCurrentAid() != 0) {
        goto ret0;
    }
    armed = ((Bits8 *)(((char *)data_ov006_020565e4.pContext) + 0x42c))->b0;
    if (armed == 0) {
        goto ret0;
    }
    keys = WH_GetBitmap();
    if (*(unsigned short *)(*(char **)((char *)&data_ov006_020565e4) + 0x434) == keys) {
        goto ret0;
    }
    Obj_SetField14(((int *)&data_ov006_020565e4)[1], (int)&Ov006_UpdateAndGetIdleHandler);
    return 1;
ret0:
    return 0;
}
