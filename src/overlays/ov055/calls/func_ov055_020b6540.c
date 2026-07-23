/* Bind the shared rig's 0x24-byte bone slots to this enemy's 0x1c8-byte parts and back-point
 * each part at its slot: twelve from the rig block at +0x134 into the parts reached through
 * +0x3c, then two more from +0x2e4 into the parts reached through +0x6c. The rig itself is the
 * global block at +0x194, not part of the enemy.
 *
 * Same template as func_ov047_020b3b40 and func_ov031_020b408c: everything is `char *`
 * arithmetic and `part` is computed BEFORE the call, which is what puts the ROM's
 * `add r7, parts, off` above the `bl` instead of after it.
 *
 * The second loop needs its OWN locals -- with one shared set mwcc reuses the first loop's
 * registers and elides the `base` recompute the ROM does at the top of loop 2 -- and the ROM's
 * register rotation falls out of the DECLARATION ORDER of that second set: base2, parts2,
 * part2, off2, slot2, i2. All 720 orders were compiled; exactly this one matches.
 *
 * One of four byte-identical siblings (ov036/ov055/ov075/ov092). */
extern void WM_EndKeySharing_0x020b15a4(int handle, void *slot);
extern char *data_ov055_020b7740;

void func_ov055_020b6540(char *self) {
    char *base;
    char *parts;
    char *rig;
    int i;
    char *part;
    int off;
    char *slot;
    char *base2;
    char *parts2;
    char *part2;
    int off2;
    char *slot2;
    int i2;

    rig = data_ov055_020b7740 + 0x194 + 0x2c00;
    base = self + 0x2000;
    i = 0;
    parts = *(char **)(base + 0x644);
    off = 0;
    slot = rig + 0x134;
    for (; i < 0xc; i++) {
        part = *(char **)(parts + 0x3c) + off;
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), slot);
        *(char **)(part + 0x130) = slot;
        off += 0x1c8;
        slot += 0x24;
    }

    base2 = self + 0x2000;
    i2 = 0;
    parts2 = *(char **)(base2 + 0x644);
    off2 = 0;
    slot2 = rig + 0x2e4;
    for (; i2 < 2; i2++) {
        part2 = *(char **)(parts2 + 0x6c) + off2;
        WM_EndKeySharing_0x020b15a4(*(int *)(base2 + 0x640), slot2);
        *(char **)(part2 + 0x130) = slot2;
        off2 += 0x1c8;
        slot2 += 0x24;
    }
}
