/*
 * func_ov002_0206e2ec - compute a remaining-slot count from a bitmask (ARM).
 *
 * Reads a small record at *(int*)&data_ov002_0207fa00 + 0x8d7c: a signed guard byte at +6, a 16-bit
 * occupancy mask at +4, and a signed adjustment byte at +7; plus a capacity byte at base+0x8d18.
 * Returns capacity minus the number of set bits in the mask minus the adjustment. When the guard
 * byte is negative it short-circuits and returns the capacity unchanged.
 *
 * The popcount uses the Kernighan `v &= v - 1` bit-clear loop. `v` is a full unsigned int (not a
 * u16) so mwcc leaves the loop's `ands` to set the flags directly instead of re-truncating to 16
 * bits each iteration - the value stays 16-bit-valued anyway since bits only clear.
 */
extern int data_ov002_0207fa00;

int func_ov002_0206e2ec(void)
{
    int base = *(int *)&data_ov002_0207fa00;
    char *p = (char *)(base + 0x8d7c);
    int r = *(unsigned char *)(base + 0x8d18);
    unsigned v;
    if (*(signed char *)(p + 6) < 0) return r;
    v = *(unsigned short *)(p + 4);
    while (v != 0) {
        r--;
        v &= v - 1;
    }
    return r - *(signed char *)(p + 7);
}
