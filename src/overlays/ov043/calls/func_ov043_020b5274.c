/* Bind the two 0x24-byte bone slots of the shared rig (at +0x1d4 of the global,
 * then +0x2c00 into it) to this enemy's two 0x1c8-byte parts, and back-point
 * each part at its slot. */
extern void WM_EndKeySharing_0x020b15a4(int handle, void *slot);

extern char *data_ov043_020b58e0;

void func_ov043_020b5274(char *self) {
    char *base;
    char *parts;
    int i;
    char *part;
    int off;
    char *slot;

    base = self + 0x2000;
    i = 0;
    parts = *(char **)(base + 0x644);
    off = 0;
    slot = data_ov043_020b58e0 + 0x2e4 + 0x3000;

    for (; i < 2; i++) {
        part = *(char **)(parts + 0x3c) + off;

        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x640), slot);
        *(char **)(part + 0x130) = slot;

        off += 0x1c8;
        slot += 0x24;
    }
}
