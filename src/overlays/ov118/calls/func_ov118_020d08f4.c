/* Two comparison forms matter here, both for the same reason (the ROM's constant is an
 * ARM immediate and mine was not): `obj[0x10] <= 0` not `< 1`, and `dist <= 0x2000`
 * not `< 0x2001`.
 * func_ov118_020d0200 takes THREE arguments -- Ghidra shows a fourth, which is the
 * leftover in r3. Passing it costs a callee-saved register and 32 B.
 * `target = obj[1] = f(...)` in that order: the ROM stores the raw r0. */
extern int  func_ov107_020cab14(int obj, int *out);
extern int  FX_Sqrt(int x);
extern int  func_02023eb4();
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov118_020d0200();
extern void func_0202f384();
extern void VEC_CrossProduct();
extern void func_01ffa724();
extern char data_02042258[];
extern char data_02042264[];

void func_ov118_020d08f4(int self) {
    int *obj = *(int **)(self + 4);
    int dist;
    int owner;
    int target;

    target = obj[1] = func_ov107_020cab14(*obj, &dist);
    if (target == 0) {
        return;
    }
    owner = *obj;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(owner + 0x80));
    owner = *obj;
    if (dist > *(int *)(owner + 0x2d8)) {
        return;
    }
    if (obj[0x10] <= 0) {
        int lo = *(int *)(owner + 0x224);
        int range = *(int *)(owner + 0x228) - lo;
        if (range < 0) {
            range = -range;
        }
        obj[0x10] = lo + func_02023eb4(range + 1);
        *(signed char *)(*obj + 0x1c7) = 6;
        func_0203c634(self, *(signed char *)(self + 0x20), 0);
        return;
    }
    if (dist <= 0x2000) {
        func_ov118_020d0200((int)obj, obj + 6, dist);
        func_0202f384(obj + 0xb, obj + 2, data_02042258);
        VEC_CrossProduct(obj + 0xb, data_02042264, obj + 0xb);
        func_01ffa724(obj[0x17], obj + 0xb, obj + 0xb);
        return;
    }
    *(signed char *)(owner + 0x1c7) = 4;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
