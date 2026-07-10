/*
 * NONMATCHING (fixed-point scaler; register-coloring + accumulation-scheduling
 * tie, size-exact byte diff @0x15). The 64-bit math, the table lookup, the
 * per-term <<12 accumulation (separate `sum +=` statements to defeat mwcc's
 * A*K+B*K -> (A+B)*K factoring), the 0x3e7000 clamp, the recombine
 * `(u32)((u64)v >> 0xc)` and the signed `>>0xd` all match. What differs is
 * which register holds iVar3 (orig r4, mwcc r5) and the interleave of the two
 * iVar3 ldrh loads vs the first `sum +=` — mwcc accumulates term A immediately
 * after loading it, the original loads A and B first, then reuses iVar3's dead
 * register for the running sum. Tried: separate/temp'd loads, pv-first decl,
 * shared base pointer. Logic is byte-equivalent.
 *
 * iVar3 = &data_0204c678 + p[9]*0x104;
 * sum = (*(u16)(iVar3+8) + *(u16)(iVar3+0xa) + *(s16)(p+0x91a) + *(s16)(p+0x91c)) each *0x1000;
 * if (sum >= 0x3e7000) sum = 0x3e7000;
 * v = ((long long)sum * arg1 + 0x800) >> 0xc;
 * *arg2 = (v + (v>>31)) >> 0xd;  *arg3 = 0;
 */
extern int data_0204c678;

void func_ov022_020a23a4(int param_1, int param_2, int *param_3, int *param_4) {
    int iVar3 = (int)&data_0204c678 + *(unsigned char *)(param_1 + 9) * 0x104;
    int sum = 0;
    long long lVar1;
    unsigned int uVar2;
    short *pv = (short *)(param_1 + 0x918);
    sum += *(unsigned short *)(iVar3 + 8) * 0x1000;
    sum += *(unsigned short *)(iVar3 + 0xa) * 0x1000;
    sum += pv[1] * 0x1000;
    sum += pv[2] * 0x1000;
    if (0x3e7000 <= sum) {
        sum = 0x3e7000;
    }
    lVar1 = (long long)sum * param_2 + 0x800;
    uVar2 = (unsigned int)((unsigned long long)lVar1 >> 0xc);
    *param_3 = (int)(uVar2 + (uVar2 >> 0x1f)) >> 0xd;
    *param_4 = 0;
}
