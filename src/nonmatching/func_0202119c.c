/* NONMATCHING — narrow-value-extension placement tie (THUMB). Same calls, same table
 * lookups, same math; only WHERE the u16 angle extension lands differs.
 *
 * The ROM masks both angle arguments to 16 bits IN THE PROLOGUE and HOLDS the masked
 * values in callee-saved r5/r4 across the two leading MTX_Identity43_ calls, deriving
 * `>> 4` (asrs r0,r5,#4) at each use. Our confirmed compiler (mwcc 3.0/139 patch4)
 * instead HOLDS THE RAW params in r5/r4 and extends at the use site
 * (lsls#16;lsrs#16;asrs#4). Both are 108 bytes with the identical instruction MULTISET
 * (9 instrs of angle handling either way) — the diff is purely the extension PLACEMENT,
 * cascading through register numbers. Everything after the second use-site extension
 * aligns exactly. Confirmed-compiler diff is down to 28 positional diffs from this ONE
 * root cause (was 68 under the earlier build sweep).
 *
 * Exhaustively swept (~17 source forms, this file's history): param types int/uint/
 * unsigned short; mask forms `&0xffff`, `(x<<16)>>16` (fuses to lsls;asrs#20 — shorter),
 * `(unsigned short)`; up-front reassign `param&=0xffff`; named/register held locals;
 * shared-subexpression short[] index; full MtxFx43 struct modeling. Every form holds raw
 * and extends at use — mwcc defers narrow extension past the calls and no source form
 * pulls it into the prologue. Best form (short[] shared index, 28 diffs) in
 * build/try/0202119c.c. Same hold-vs-recompute class as func_0202accc. Blob keeps the
 * build byte-exact.
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
