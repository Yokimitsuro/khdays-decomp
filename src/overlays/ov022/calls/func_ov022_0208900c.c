/* Refresh every live entry of the current root object's array (0x114 apart, count in the top
 * 6 bits of the header byte, re-read each pass), skipping entries whose first byte is clear.
 * Bit 3 of the second header byte gates the whole thing.
 *
 * Parked as needing "one extra callee-saved reg vs the original". It does not: func_ov022_02089078
 * takes TWO arguments, not three. The original never preserves r2 across the loop, which is the
 * proof -- a third argument would have to survive the calls. Once the arity is right the function
 * has no live parameters at all.
 *
 * The remaining two points are placement, not allocation: declare i BEFORE p so the two land in
 * r4/r5 the way the original has them, and put `i = 0` between the two guards, which is where the
 * original schedules it. */
extern unsigned char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_02089078(int entry, int base);

void func_ov022_0208900c(void) {
    int i;
    unsigned char *p;
    int off;

    p = NNSi_FndGetCurrentRootHeap();
    if (((unsigned int)p[1] << 0x1c) >> 0x1f == 0) return;
    i = 0;
    if ((int)(((unsigned int)p[0] << 0x18) >> 0x1a) <= 0) return;
    off = 0;
    do {
        int e = *(int *)(p + 0xc);
        if (*(unsigned char *)(e + off) != 0) {
            func_ov022_02089078(e + off, e);
        }
        i = i + 1;
        off = off + 0x114;
    } while (i < (int)(((unsigned int)p[0] << 0x18) >> 0x1a));
}
