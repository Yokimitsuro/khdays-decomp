/*
 * Levels the mission tallies up when the session countdown expires.
 *
 * The highest tally across the members is found first, then every member is
 * awarded the shortfall from that leader: the gap is taken into 12-bit fixed
 * point, scaled by the current rate, rounded, and rounded up again to whole
 * units. Members already level get nothing.
 *
 * Two things here are load-bearing rather than style.
 *
 * The award takes three arguments, not two. The whole-unit count is already in
 * the third argument register when the call is reached, which is why the
 * original shifts it into that register instead of updating the running value
 * in place.
 *
 * Both sweeps are for loops over the member count rather than guarded
 * do-whiles, so the zero-trip guards come out as signed compares against the
 * count; written as `count > 0` the compiler knows the byte cannot be negative
 * and tests for zero instead.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002TallyEntry {
    char pad000[2];
    u8 nValue;
    char pad003[0x101];
} Ov002TallyEntry;

extern u8 data_02042a1d;
extern Ov002TallyEntry data_0204c678[];

extern int func_ov002_0206e6d0(void);
extern void func_ov002_0206bbb8(int nIndex, int nKind, int nWhole);

void func_ov002_0206a894(void)
{
    int i;
    int nMax;
    int nScaled;
    int nWhole;

    nMax = -1;
    for (i = 0; i < data_02042a1d; i++) {
        if (nMax < data_0204c678[i].nValue) {
            nMax = data_0204c678[i].nValue;
        }
    }

    for (i = 0; i < data_02042a1d; i++) {
        nScaled = (int)((((long long)((nMax - data_0204c678[i].nValue) << 12))
                         * (long long)func_ov002_0206e6d0() + 0x800) >> 12);
        nWhole = (nScaled + 0xfff) >> 12;
        if (nWhole > 0) {
            func_ov002_0206bbb8(i, 7, nWhole);
        }
    }
}
