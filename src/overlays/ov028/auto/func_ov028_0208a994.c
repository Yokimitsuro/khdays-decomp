/* ARC4/RC4 key-schedule (KSA) -- MATCHED, but built with mwcc 1.2 sp4, NOT the
 * game's 3.0_patch4. The anti-tamper crypto core is precompiled middleware from
 * an older CodeWarrior: 2.0/3.0 emit `add ip,ip,r4` (in-place, t as rn) where the
 * ROM has `add ip,r4,ip` (si as rn), an operand-order + scratch cascade that ONLY
 * 1.2's allocator reproduces. Requires a per-file compiler override in the build
 * (see staging/ov028/README.md). Init S-box to identity, then permute i=0xff->0
 * with keyByte=key[keyIdx] (keyIdx wraps mod keylen), standard RC4 swap. */
void func_ov028_0208a994(int ctx, int key, unsigned int keylen) {
    int i; unsigned int j; unsigned int keyIdx; unsigned char *Si; int k; unsigned char si; unsigned char *Sj; unsigned char sj; unsigned int t; unsigned char keyByte;
    keyIdx = 0;
    *(int *)ctx = 0;
    j = 0;
    k = 0;
    *(int *)(ctx + 4) = 0;
    do { *(unsigned char *)(ctx + k + 8) = (unsigned char)k; k++; } while (k < 0x100);
    i = 0xff;
    do {
        keyByte = *(unsigned char *)(key + keyIdx);
        Si = (unsigned char *)(ctx + i);
        si = Si[8];
        t = j + keyByte; keyIdx++; j = (si + t) & 0xff;
        Sj = (unsigned char *)(ctx + j); sj = Sj[8];
        if (keyIdx >= keylen) keyIdx = 0;
        Sj[8] = si; Si[8] = sj;
        i--;
    } while (i >= 0);
}
