/* func_ov162_020ce2cc: release hook of the ov161 enemy (x2), variant of the matched ov131 sibling with a third task slot (+0x2c) and attachment (+0x3d4) finished outside sub-state 7. */
typedef struct { int w[11]; } SrtTransform;   /* 44 bytes, the node's SRT block */

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(void *attachment);
extern void func_ov107_020c7ca4(void *actor);

void func_ov162_020ce2cc(char *actor) {
    if (*(signed char *)(actor + 0x1c6) != 7) {
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x14) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x14));
            *(int *)(*(char **)(actor + 0x3c4) + 0x14) = 0;
        }
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x24) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x24));
            *(int *)(*(char **)(actor + 0x3c4) + 0x24) = 0;
        }
        if (*(int *)(*(char **)(actor + 0x3c4) + 0x2c) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3c4) + 0x2c));
            *(int *)(*(char **)(actor + 0x3c4) + 0x2c) = 0;
        }
        if (*(void **)(actor + 0x3d4) != 0) {
            func_ov107_020cb100(*(void **)(actor + 0x3d4));
            *(void **)(actor + 0x3d4) = 0;
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
    *(SrtTransform *)(**(char ***)(actor + 0x388) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);
    *(SrtTransform *)(*(char **)(actor + 0x38c) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x3c0) + 4);
    func_ov107_020c7ca4(actor);
}
