/* Character select: should the pending input be handed to the confirm state? Refuses while the
 * manager is gone or the scene is locked out (obj+0x4e8). Scenes already in the confirm
 * (func_ov006_0204ece4) or cancel (func_ov006_0204ed24) state are accepted as-is. Otherwise the
 * touch must be released, the drag-armed bit 0 at obj+0x42c must be set, and the live key state
 * must differ from the one latched at obj+0x434 -- only then does the scene move to confirm.
 *
 * The old note called this "the ctx-CSE / pool-rematerialisation tie ... not steerable from C":
 * the ROM re-loads &data_ov006_020565e4 from the literal pool three times and the address of
 * func_ov006_0204ece4 twice, keeping the prologue at `push {r3,lr}`, while mwcc cached both in
 * callee-saved registers. It is steerable, and it took three separate things:
 *
 *   - SPELL EACH POOL-LOAD GROUP DIFFERENTLY. The ROM has three groups, and within a group it
 *     shares the base: (a) the null test + 0x4e8 + the scene pointer at +4, (b) the 0x42c byte,
 *     (c) the 0x434 halfword + the scene pointer again. Writing all of them through one macro
 *     lets mwcc keep one copy in a callee-saved register; writing each group as a different but
 *     equivalent expression -- `*(char **)&sym`, `((char **)&sym)[0]`, `*(char **)((char *)&sym)`,
 *     `((int *)&sym)[1]` -- makes it reload, and the push drops from {r3,r4,r5,lr} to {r4,lr}.
 *   - COMPARE THE STATE AS A FUNCTION POINTER, not as an int. `(void (*)(void))state ==
 *     func_ov006_0204ece4` for the two tests and `(int)&func_ov006_0204ece4` for the call
 *     argument are the same address spelled two ways, so mwcc stops CSE-ing them into r4 and
 *     re-loads the pool word like the ROM. That is the last callee-saved: push {r3,lr}.
 *   - ONE SHARED `return 0` REACHED BY `goto`. Three separate `return 0;` statements each get
 *     predicated (`movne r0,#0 ; popne`); one label with three predecessors cannot be
 *     if-converted, which is what produces the ROM's three branches to a single exit block.
 *
 * The drag-armed test is a 1-bit bitfield read, not a shift pair: written as
 * `(x << 0x1f) >> 0x1f` mwcc folds the whole thing to `tst r0,#1` because the result is only
 * tested, and the ROM's `lsl #0x1f ; lsrs #0x1f` disappears. */
extern int   OS_IsTickAvailable(void);
extern int   OS_IsTickAvailable_0x01ff8138(void);
extern void  func_02023a44(int scene, int next);
extern void  func_ov006_0204ece4(void);
extern void  func_ov006_0204ed24(void);
extern int   data_ov006_020565e4;

typedef struct { unsigned char b0 : 1; unsigned char rest : 7; } Bits8;

int func_ov006_0204f2f4(void) {
    int state;
    unsigned int armed;
    int keys;

    if (*(char **)&data_ov006_020565e4 == 0
        || *(int *)(*(char **)&data_ov006_020565e4 + 0x4e8) != 0) {
        return 0;
    }
    state = *(int *)(*(int *)((int)&data_ov006_020565e4 + 4) + 0x14);
    if ((void (*)(void))state == func_ov006_0204ece4) {
        return 1;
    }
    if ((void (*)(void))state == func_ov006_0204ed24) {
        return 1;
    }
    if (OS_IsTickAvailable() != 0) {
        goto ret0;
    }
    armed = ((Bits8 *)(((char **)&data_ov006_020565e4)[0] + 0x42c))->b0;
    if (armed == 0) {
        goto ret0;
    }
    keys = OS_IsTickAvailable_0x01ff8138();
    if (*(unsigned short *)(*(char **)((char *)&data_ov006_020565e4) + 0x434) == keys) {
        goto ret0;
    }
    func_02023a44(((int *)&data_ov006_020565e4)[1], (int)&func_ov006_0204ece4);
    return 1;
ret0:
    return 0;
}
