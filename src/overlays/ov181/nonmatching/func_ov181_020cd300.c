/* NONMATCHING -- 344/344 B, every instruction matches except ONE REGISTER PAIR:
 * the ROM holds `target` in r7 and `owner` in r6; mwcc swaps them. Nothing else differs.
 *
 * Head of a 6-member family (ov181/182/183/184 + 2 more), so the swap is worth 6.
 *
 * Already solved on the way here -- do NOT redo:
 *  - `target = obj[4] = f(...)` in that order. The ROM stores the raw call result
 *    (`str r0`); writing `obj[4] = target;` as a separate statement stores the copy.
 *    (Same crack as ov115_020ce2e4, which DID go on to match.)
 *  - `obj[8] = *(int *)(*(int *)self + 0x2c) * 0x1e / 20;` reproduces the ROM's magic
 *    multiply (0x66666667, asr #3). Verified against the pool literal at +0x14c.
 *  - VEC_Subtract takes `obj[4] + 0x74`, i.e. it RE-READS obj[4] rather than reusing
 *    `target` -- the ROM reloads it (`ldr r0,[r4,#0x10]`).
 *
 * Ruled out for the r6/r7 swap:
 *  - ALL 120 permutations of the five local declarations (scripted).
 *  - `owner` scoped into a block at its point of use.
 *  - dropping `owner` entirely and inlining `*obj` (that one changes the push list). */
extern int  func_ov107_020cab14(int obj, int *out);
extern void func_0203c634(int self, int index, void *cb);
extern int  FX_Sqrt(int x);
extern void VEC_Subtract();
extern int  func_020050b4(int a, int b);
extern void func_0202f384();
extern void func_01ffa724();
extern char data_02042258[];
extern void func_ov181_020cd458(void);

void func_ov181_020cd300(int self) {
    int dist;
    int v[3];
    int *obj = *(int **)(self + 4);
    int target;
    int owner;

    target = obj[4] = func_ov107_020cab14(*obj, &dist);
    if (target == 0) {
        *(signed char *)(*obj + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    owner = *obj;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    obj[8] = *(int *)(*(int *)self + 0x2c) * 0x1e / 20;
    VEC_Subtract(obj[4] + 0x74, obj[2], v);
    obj[6] = func_020050b4(v[0], v[2]);
    func_0202f384((int)obj + 0x54, *obj + 0xa0, data_02042258);
    func_01ffa724(0x300, (int)obj + 0x54, (int)obj + 0x54);
    if (obj[0x1d] > 0) {
        if (dist < *(int *)(*obj + 0x2d8) && dist > 0x2000) {
            return;
        }
        *(signed char *)(*(int *)(*obj + 0x384) + 0xa8) = 0;
        func_0203c634(self, *(signed char *)(self + 0x20), &func_ov181_020cd458);
        return;
    }
    *(signed char *)(*obj + 0x1c7) = 5;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
