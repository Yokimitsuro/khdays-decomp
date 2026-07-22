/* Bind the ten 0x24-byte bone slots of the shared rig (at +0x30c of the object,
 * then +0x2c00 into it) to this enemy's ten 0x1c8-byte parts, and back-point
 * each part at its slot. */
extern void WM_EndKeySharing_0x020b15a4(int handle, void *slot);

void func_ov045_020b48b4(char *self) {
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
    slot = self + 0x30c + 0x2c00;

    for (; i < 10; i++) {
        part = *(char **)(parts + 0xc) + off;

        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), slot);
        *(char **)(part + 0x130) = slot;

        off += 0x1c8;
        slot += 0x24;
    }
}
