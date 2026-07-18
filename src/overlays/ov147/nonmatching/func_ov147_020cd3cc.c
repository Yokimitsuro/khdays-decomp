/* NONMATCHING -- 216/216 B, 32 differing bytes, all in the head. The tail matches exactly.
 * Head of a 5-member family.
 *
 * The ROM HOISTS two constants above the branch so they serve both paths: `mov r2,#0` (the
 * third argument of the tail func_0203c634) and `mov r1,#2` (the 0x1c7 state) are emitted
 * before the `bne`. mwcc emits both inside the taken block.
 *
 * SOLVED here -- do NOT rediscover:
 *  - func_ov107_020c9264 is called here with NO arguments at all (no r0-r3 setup before the
 *    bl). Passing (obj, 0, 0) is 8 B long. Same callee takes 3 elsewhere -- it is unprototyped,
 *    so read the arity per call site.
 *  - the tail func_0203c634 DOES take its third argument here (dropping it is 4 B short), so
 *    the two calls to the same function in this function have different arities.
 *  - `* 0x1e / 10` reproduces the magic multiply (0x66666667, asr #2).
 *
 * Ruled out: the `+ (v - v)` RNG artifact (identical either way here), a local for the RNG
 * result (+4 B), writing the body as the positive case (112 bytes -- much worse), and caching
 * *obj in a local (no change). Measured with tools/bytedist.py. */
extern int  func_ov107_020cab14(int obj, int flag);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov107_020c9264();
extern void func_ov147_020cc9c0(int owner, int a);
extern int  func_02023eb4();
extern void VEC_Subtract();
extern void func_ov147_020cd4a4(void);

void func_ov147_020cd3cc(int *self) {
    int *obj = (int *)self[1];
    int v;
    int lo, range;

    *(int *)(*obj + 0x394) = func_ov107_020cab14(*obj, 0);
    if (*(int *)(*obj + 0x394) == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    func_ov107_020c9264();
    func_ov147_020cc9c0(*obj, 0);
    obj[0xf] = *(int *)(self[0] + 0x2c) * 0x1e / 10;
    lo = *(int *)(*obj + 0x224);
    range = *(int *)(*obj + 0x228) - lo;
    if (range < 0) {
        range = -range;
    }
    obj[0x10] = lo + func_02023eb4(range + 1) + (v - v);
    VEC_Subtract(*(int *)(*obj + 0x394) + 400, obj[3], obj + 10);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov147_020cd4a4);
}
