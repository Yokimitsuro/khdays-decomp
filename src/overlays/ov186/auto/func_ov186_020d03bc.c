/*
 * func_ov186_020d03bc -- x3 (ov185/...). Drive the sub-nodes through the group's exit modes.
 * p = *(self+0x214); owner = *p; mode = *(s8)(owner+0x1c6).
 *  - mode 9: clear the dirty byte owner+0x1c7 and report done (return 1).
 *  - mode 6: for each of the 4 sub-nodes, if its hw60 low bit is set run its +0x1e0 callback, then
 *    advance the group to mode 7.
 *  - mode 7: for each active sub-node (hw60 bit 0), run its +0x1e0 callback; if it returns non-zero,
 *    clear hw60 bit 8, clear the low nibble of +0x1c5, set +0x2e8 = 0x800; count the active nodes. If
 *    none were active, fall back to mode 9.
 *  - modes 2 and 4 (when neither the dirty byte nor mode is already 8): latch owner+0x1c7 = 8.
 * Return 0 in all non-mode-9 cases.
 */
struct flags16 { unsigned short lo : 8, hi : 8; };

int func_ov186_020d03bc(int self) {
    int *p = *(int **)(self + 0x214);
    int owner = *p;
    signed char mode = *(signed char *)(owner + 0x1c6);
    int i;

    if (mode == 9) {
        *(unsigned char *)(owner + 0x1c7) = 0;
        return 1;
    }
    if (mode == 6) {
        for (i = 0; i < 4; i++) {
            int node = ((int *)(*(int *)(*p + 0x390)))[i];
            if ((((struct flags16 *)(node + 0x60))->lo & 1) != 0) {
                void (*cb)(int) = *(void (**)(int))(node + 0x1e0);
                if (cb != 0) {
                    cb(node);
                }
            }
        }
        *(unsigned char *)(*p + 0x1c7) = 7;
    } else if (mode == 7) {
        int count = 0;
        int j;
        for (j = 0; j < 4; j++) {
            int node = ((int *)(*(int *)(*p + 0x390)))[j];
            if ((((struct flags16 *)(node + 0x60))->lo & 1) != 0) {
                int (*cb)(int) = *(int (**)(int))(node + 0x1e0);
                int ret = (cb != 0) ? cb(node) : 0;
                if (ret != 0) {
                    ((struct flags16 *)(node + 0x60))->hi &= ~1;
                    *(unsigned char *)(node + 0x1c5) &= ~0xf;
                    *(int *)(node + 0x2e8) = 0x800;
                }
                count++;
            }
        }
        if (count == 0) {
            *(unsigned char *)(*p + 0x1c7) = 9;
        }
    } else if (*(signed char *)(owner + 0x1c7) != 8 && mode != 8 && (mode == 2 || mode == 4)) {
        *(unsigned char *)(owner + 0x1c7) = 8;
    }
    return 0;
}
