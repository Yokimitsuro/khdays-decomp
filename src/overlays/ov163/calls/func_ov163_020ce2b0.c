/* func_ov163_020ce2b0: release hook of the ov163 enemy (x3), variant of the matched ov131 sibling: the two item transforms are refreshed from the +0x3c0 item before the sub-state-dependent task finishes (no 0x1c4 guard here). */
typedef struct { int w[11]; } SrtTransform;   /* 44 bytes, the node's SRT block */

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(void *attachment);
extern void func_ov107_020c7ca4(void *actor);

void func_ov163_020ce2b0(char *actor) {
    *(SrtTransform *)(**(char ***)(actor + 0x388) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);
    *(SrtTransform *)(*(char **)(actor + 0x38c) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);
    if (*(signed char *)(actor + 0x1c6) != 7) {
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x1c) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x1c));
            *(int *)(*(char **)(actor + 0x3c4) + 0x1c) = 0;
        }
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x24) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x24));
            *(int *)(*(char **)(actor + 0x3c4) + 0x24) = 0;
        }
    }
    if (*(signed char *)(actor + 0x1c6) != 6) {
        if (*(int *)(*(char **)(actor + 0x3c4) + 4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 4));
            *(int *)(*(char **)(actor + 0x3c4) + 4) = 0;
        }
        if (*(void **)(actor + 0x3d0) != 0) {
            func_ov107_020cb100(*(void **)(actor + 0x3d0));
            *(void **)(actor + 0x3d0) = 0;
        }
    }
    func_ov107_020c7ca4(actor);
}
