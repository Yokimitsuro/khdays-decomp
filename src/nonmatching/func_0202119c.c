/* NONMATCHING — value-hold strategy tie (THUMB). Same calls, same table lookups,
 * same math; the register/scheduling strategy differs.
 *
 * The ROM masks both angle arguments to 16 bits up front and HOLDS the masked values
 * in callee-saved r5/r4 across all six MTX calls, deriving `>> 4` at each use. Every
 * mwcc build we have instead holds the RAW 32-bit params and re-masks (lsl#16;lsr#16)
 * on demand, which permutes register use throughout (68 of 108 bytes differ, but only
 * in register numbers / mask placement — the call sequence and reloc offsets align).
 * Declaring pre-masked locals does not help: mwcc CSEs them back to raw+mask-on-use.
 * Same hold-vs-recompute class as func_0202accc; consistent with retail = 3.0 >=140.
 *
 * Proven unsteerable: swept all 27 mwccarm builds x {-O4,p/s / -O4 / -O3,p / -O2};
 * none byte-matches (best is the same 68-byte register permutation). THUMB. Blob keeps
 * the build byte-exact.
 *
 * Build a rotation matrix into `param_1`: identity, then post-multiply by a rotation
 * about X by angle (param_2 & 0xffff)>>4 and about Y by angle (param_3 & 0xffff)>>4,
 * looking up {sin,cos} pairs in the angle table (data_0203d210), 4 bytes per entry. */
#pragma thumb on
extern void MTX_Identity43_(void *m);
extern void MTX_RotX43_(void *m, int s, int c);
extern void MTX_RotY43_(void *m, int s, int c);
extern void MTX_Concat43(void *a, void *b, void *dst);
extern short data_0203d210[];
void func_0202119c(int *param_1, unsigned int param_2, unsigned int param_3) {
    unsigned int temp[12];
    int i;
    MTX_Identity43_(param_1);
    MTX_Identity43_(temp);
    i = (int)(param_2 & 0xffff) >> 4;
    MTX_RotX43_(temp, (int)*(short *)((char *)data_0203d210 + i * 4),
                (int)*(short *)((char *)data_0203d210 + (i * 2 + 1) * 2));
    MTX_Concat43(param_1, temp, (unsigned int *)param_1);
    MTX_Identity43_(temp);
    i = (int)(param_3 & 0xffff) >> 4;
    MTX_RotY43_(temp, (int)*(short *)((char *)data_0203d210 + i * 4),
                (int)*(short *)((char *)data_0203d210 + (i * 2 + 1) * 2));
    MTX_Concat43(param_1, temp, (unsigned int *)param_1);
}
