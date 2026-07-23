/* Bind the six 0x24-byte bone slots of the shared rig to this enemy's parts and back-point
 * each part at its slot: three from the rig block at +0x2a8 into the parts reached through
 * +0x6c, then three more from +0x23c into the parts reached through +0xc.
 *
 * Everything is `char *` arithmetic and `part` is computed BEFORE the call -- that is what
 * puts the ROM's `add r8, parts, off` above the `bl` instead of after it, and it is the same
 * template that matched func_ov047_020b3b40.
 *
 * The second loop needs its OWN locals. With one shared set mwcc reuses the first loop's
 * registers and elides the `blk` recompute the ROM does at the top of loop 2 (four bytes
 * short); with a second set it recomputes, and the ROM's register rotation then falls out of
 * the DECLARATION ORDER of that second set -- base2, part2, off2, slot2, parts2, i2. All 720
 * orders were compiled; exactly this one matches.
 *
 * One of four byte-identical siblings (ov031/ov050/ov070/ov088). */
extern void WM_EndKeySharing_0x020b15a4(int handle, void *slot);

void func_ov050_020b688c(char *self) {
    char *base;
    char *parts;
    char *rig;
    int i;
    char *part;
    int off;
    char *slot;
    char *base2;
    char *part2;
    int off2;
    char *slot2;
    char *parts2;
    int i2;

    rig = self + 0x2c + 0x2c00;
    base = self + 0x2000;
    i = 0;
    parts = *(char **)(base + 0x644);
    off = 0;
    slot = rig + 0x2a8;
    for (; i < 3; i++) {
        part = *(char **)(parts + 0x6c) + off;
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), slot);
        *(char **)(part + 0x130) = slot;
        off += 0x1c8;
        slot += 0x24;
    }

    base2 = self + 0x2000;
    i2 = 0;
    parts2 = *(char **)(base2 + 0x644);
    off2 = 0;
    slot2 = rig + 0x23c;
    for (; i2 < 3; i2++) {
        part2 = *(char **)(parts2 + 0xc) + off2;
        WM_EndKeySharing_0x020b15a4(*(int *)(base2 + 0x640), slot2);
        *(char **)(part2 + 0x130) = slot2;
        off2 += 0x1c8;
        slot2 += 0x24;
    }
}
