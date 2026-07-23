/* NONMATCHING: semantically complete, register-alloc tie in the six struct copies. The 44-byte
 * SrtTransform copies emit the exact ldm/stm 4+4+3 groups, but the ROM holds the src pointer in
 * scratch (ip/lr) and dst in r5, while mwcc uses callee-saved r5/r6 -- one extra saved register
 * in the push, +7 instructions. No C form controls which registers the struct-copy pointers get.
 * Behaviour: sync six bone SRT transforms (source+4 -> target+0x10) from actor handles at
 * +0x3c8..+0x3d4 into targets at +0x3ac(**)/+0x3c4/+0x3bc/+0x3c0/+0x3b8/+0x3b0(**), then finish
 * stale sub-task tags per animation state (+0x1c6) and flags (+0x1c4). */
typedef struct {
    int aRot[4];
    int aTranslation[3];
    int aScale[3];
    unsigned char bFlags;
    unsigned char aPad29[3];
} SrtTransform;

extern void TaskList_FinishByTag(int list, int tag);
extern void func_ov107_020c7ca4(int actor);

void func_ov206_020cc9b4(int actor) {
    char state;
    int tag;
    unsigned int mode;
    int gated;

    *(SrtTransform *)(**(int **)(actor + 0x3ac) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3c8) + 4);
    *(SrtTransform *)(*(int *)(actor + 0x3c4) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3c8) + 4);
    *(SrtTransform *)(*(int *)(actor + 0x3bc) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3cc) + 4);
    *(SrtTransform *)(*(int *)(actor + 0x3c0) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3d0) + 4);
    *(SrtTransform *)(*(int *)(actor + 0x3b8) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3d4) + 4);
    *(SrtTransform *)(**(int **)(actor + 0x3b0) + 0x10) =
        *(SrtTransform *)(*(int *)(actor + 0x3d4) + 4);

    state = *(char *)(actor + 0x1c6);
    if (state != '\b' && state != '\x06') {
        tag = *(int *)(*(int *)(actor + 0x3e0) + 0x14);
    }
    if ((state != '\b' && state != '\x06') && tag != 0) {
        TaskList_FinishByTag(*(int *)(actor + 0x3c), tag);
        tag = 0;
        *(int *)(*(int *)(actor + 0x3e0) + 0x14) = 0;
    }

    if (state != '\x05') {
        tag = *(int *)(*(int *)(actor + 0x3e0) + 4);
    }
    if (state != '\x05' && tag != 0) {
        TaskList_FinishByTag(*(int *)(actor + 0x3c), tag);
        *(int *)(*(int *)(actor + 0x3e0) + 4) = 0;
    }

    mode = *(unsigned char *)(actor + 0x1c4);
    gated = (*(unsigned char *)(actor + 0x1c4) & 10) != 0;
    if (gated) {
        mode = (unsigned int)*(char *)(actor + 0x1c6);
    }
    if (gated && mode != 0 && mode != 1 && mode != 3 && mode != 2 && mode != 0xc) {
        *(unsigned char *)(actor + 0x1c7) = 2;
        tag = *(int *)(*(int *)(actor + 0x3e0) + 4);
        if (tag != 0) {
            TaskList_FinishByTag(*(int *)(actor + 0x3c), tag);
            *(int *)(*(int *)(actor + 0x3e0) + 4) = 0;
        }
    }
    func_ov107_020c7ca4(actor);
}
