/* NONMATCHING: the ctx-CSE / pool-rematerialisation tie (see references/deferred-ties.md).
 * Same 184 bytes and the same instruction count; only the register allocation differs. The ROM
 * reloads BOTH &data_ov006_020565e4 (ldr r0,[pool] at +0x04, +0x5c and +0x78) and
 * &func_ov006_0204ece4 (at +0x2c and +0x94) from the literal pool after each call, keeping the
 * prologue at push {r3,lr}; mwcc 3.0/139 caches both in callee-saved registers and pushes
 * {r3,r4,r5,lr}. Not steerable from C.
 *
 * Everything else lands: the shared return-0 block, the single load of the scene state at +0x14
 * compared twice, the movs bit test on obj+0x42c, and the unsigned ldrh of obj+0x434 via the
 * base+0x400 split.
 *
 * func_ov006_0204f2f4 -- char select: should the pending input be handed to the confirm state?
 * Refuses while the manager is gone or the scene is locked out (obj+0x4e8). Scenes already in
 * the confirm (func_ov006_0204ece4) or cancel (func_ov006_0204ed24) state are accepted as-is.
 * Otherwise the touch must be released, the drag-armed bit 0 at obj+0x42c must be set, and the
 * live key state must differ from the one latched at obj+0x434 -- only then does the scene move
 * to the confirm state. */
extern int   OS_IsTickAvailable(void);
extern int   OS_IsTickAvailable_0x01ff8138(void);
extern void  func_02023a44(int scene, int next);
extern void  func_ov006_0204ece4(void);
extern void  func_ov006_0204ed24(void);
extern int   data_ov006_020565e4;

#define OBJ   (*(char **)&data_ov006_020565e4)
#define SCENE (*(int *)((int)&data_ov006_020565e4 + 4))

int func_ov006_0204f2f4(void) {
    int state;
    unsigned int armed;
    int keys;

    if (OBJ == 0 || *(int *)(OBJ + 0x4e8) != 0) {
        return 0;
    }
    state = *(int *)(SCENE + 0x14);
    if (state == (int)func_ov006_0204ece4) {
        return 1;
    }
    if (state == (int)func_ov006_0204ed24) {
        return 1;
    }
    if (OS_IsTickAvailable() != 0) {
        return 0;
    }
    armed = ((unsigned int)*(unsigned char *)(OBJ + 0x42c) << 0x1f) >> 0x1f;
    if (armed == 0) {
        return 0;
    }
    keys = OS_IsTickAvailable_0x01ff8138();
    if (*(unsigned short *)(OBJ + 0x434) == keys) {
        return 0;
    }
    func_02023a44(SCENE, (int)func_ov006_0204ece4);
    return 1;
}
