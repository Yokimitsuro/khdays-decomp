/*
 * [nonmatching: 64-bit divide/compare runtime helper — deferred class]
 *
 * When data_0204be04 is clear, calls the 64-bit helper func_02020368 (a
 * runtime divide/compare) on a widened (func_020031d4() << 6) value against a
 * threshold, and returns func_ov022_02086ae4 when the comparison holds; then
 * runs func_ov022_02086d60(0x10000).
 *
 * The func_02020368 call takes a 64-bit argument split across r0:r1 plus the
 * SBORROW/carry-based signed 64-bit comparison the decompiler renders with
 * `(uint)((uint)uVar7 <= uVar4) <= uVar3 - uVar2`. mwcc's lowering of the
 * widening, the r0:r1 split, and the multi-word compare does not reproduce the
 * original register/scheduling shape (same 64-bit-runtime-helper class noted for
 * func_02020368/020374/02020374 elsewhere). Left uncarved (byte-exact in the
 * blob) with the clean equivalent recorded here.
 */
extern int NNSi_FndGetCurrentRootHeap(void);
extern long long func_020031d4(void);
extern unsigned long long func_02020368(unsigned int lo, unsigned int hi, int arg2, int arg3);
extern void func_ov022_02086d60(int arg0);
extern int data_0204be04;

int func_ov022_02086a90(void) {
    int h = NNSi_FndGetCurrentRootHeap();
    long long m;
    unsigned long long q;
    int limit;
    int ret = 0;
    if (*(unsigned char *)&data_0204be04 != 0) return 0;
    m = func_020031d4() << 6;
    q = func_02020368((unsigned int)m, (unsigned int)((unsigned long long)m >> 0x20), 0x2710, 0);
    limit = *(int *)(h + 0xc4) + 100;
    if ((long long)q <= (long long)limit) {
        ret = 1;
    }
    func_ov022_02086d60(0x10000);
    return ret;
}
