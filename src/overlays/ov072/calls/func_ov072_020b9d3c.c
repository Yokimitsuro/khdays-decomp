/* Bind the shared rig's 0x24-byte bone slots at +0x118 to this enemy's 0x1c8-byte parts and
 * back-point each part at its slot. The part count is the byte at +0x49 of the part table and
 * is re-read on every iteration, so the loop follows it if it changes.
 *
 * Same `char *` template as func_ov047_020b3b40, plus two things this one needs:
 *   - the +0x118 step is a SEPARATE cast expression. Written as `rig + 0x118` mwcc folds the
 *     whole chain (0x278 + 0x2c00 + 0x118) into two adds; the ROM keeps `rig` as its own value
 *     and adds 0x118 to it, which is three.
 *   - the zero-trip test is an EXPLICIT `if` around a do/while, not a `for`. The ROM emits the
 *     guard BEFORE initialising `off` and `slot`, and a `for` puts every initialiser above the
 *     test. `i < count` and not `count > 0`: the second gives `popeq` where the ROM has `pople`.
 *
 * Declaration order (parts, rig, i, part, off, slot, base) colours the registers; all 5040
 * orders were compiled and this is the one that matches.
 *
 * One of three byte-identical siblings (ov032/ov052/ov072). */
extern void WM_EndKeySharing_0x020b15a4(int handle, void *slot);

void func_ov072_020b9d3c(char *self) {
    char *parts;
    char *rig;
    int i;
    char *part;
    int off;
    char *slot;
    char *base;

    base = self + 0x2000;
    parts = *(char **)(base + 0x644);
    rig = self + 0x278 + 0x2c00;
    i = 0;
    if (i < *(unsigned char *)(parts + 0x49)) {
        off = 0;
        slot = (char *)(0x118 + (int)rig);
        do {
            part = *(char **)(parts + 0x3c) + off;
            WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), slot);
            *(char **)(part + 0x130) = slot;
            off += 0x1c8;
            slot += 0x24;
            i++;
        } while (i < *(unsigned char *)(parts + 0x49));
    }
}
