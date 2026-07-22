/* func_ov023_020853a8 -- rebuild every visible entry of the 0x40-entry table at +0x440 of the VM
 * state; entries whose bit 2 is set in func_0202c424's flags are skipped. Always reports 1.
 *
 * Two shapes are load-bearing. The table pointer is reached as `((int *)obj)[0x4a]`, an ARRAY
 * INDEX: written as `*(int *)(obj + 0x128)` mwcc hoists the 0x128 into a callee-saved register
 * where the ROM rebuilds it (`movs #0x4a ; lsls #2`) at each use, which costs 4 bytes and steals
 * the register the mask wants. And the whole loop sits INSIDE the guard rather than after an
 * early `return 1`, so the single exit is shared. */
extern void func_0202c4b0(int obj);
extern int func_0202c424(unsigned short i);
extern void func_ov023_020888e8(int p);

int func_ov023_020853a8(int obj) {
    int i;
    int off;
    int mask;
    func_0202c4b0(obj);
    if (*(int *)(((int *)obj)[0x4a] + 0x440) != 0) {
        i = 0;
        off = i;
        mask = 4;
        do {
            if ((func_0202c424((unsigned short)i) & mask) == 0) {
                func_ov023_020888e8(*(int *)(((int *)obj)[0x4a] + 0x440) + off);
            }
            i = i + 1;
            off = off + 0x1a64;
        } while (i < 0x40);
    }
    return 1;
}
