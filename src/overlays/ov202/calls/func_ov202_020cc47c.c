/* func_ov202_020cc47c: release hook of the ov202 enemy (x2: ov202/203), variant of the matched ov131 sibling: the sub-state-dependent task finishes come first (slots +0x3dc, attachment +0x410), then both item transforms are refreshed from the +0x3d8 item. */
typedef struct { int w[11]; } SrtTransform;   /* 44 bytes, the node's SRT block */

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(void *attachment);
extern void func_ov107_020c7ca4(void *actor);

void func_ov202_020cc47c(char *actor) {
    if (*(signed char *)(actor + 0x1c6) != 7) {
        if (*(int *)(*(char **)(actor + 0x3dc) + 0x14) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3dc) + 0x14));
            *(int *)(*(char **)(actor + 0x3dc) + 0x14) = 0;
        }
        if (*(int *)(*(char **)(actor + 0x3dc) + 0x24) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3dc) + 0x24));
            *(int *)(*(char **)(actor + 0x3dc) + 0x24) = 0;
        }
    }
    if (*(signed char *)(actor + 0x1c6) != 6) {
        if (*(int *)(*(char **)(actor + 0x3dc) + 4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3dc) + 4));
            *(int *)(*(char **)(actor + 0x3dc) + 4) = 0;
        }
        if (*(void **)(actor + 0x410) != 0) {
            func_ov107_020cb100(*(void **)(actor + 0x410));
            *(void **)(actor + 0x410) = 0;
        }
    }
    *(SrtTransform *)(**(char ***)(actor + 0x38c) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3d8) + 4);
    *(SrtTransform *)(*(char **)(actor + 0x390) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3d8) + 4);
    func_ov107_020c7ca4(actor);
}
