/*
 * func_ov201_020d3f24 -- x3. Push the object toward the midpoint of two node anchors, then hand off.
 * base = self[0x84]; v = base(+0x48) + base(+0x4c) (VEC_Add); scale v by 0x800 (01ffa724); then the
 * 0203bc78 handoff with (self, arg1).
 */
extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203bc78(int self, int arg1);

void func_ov201_020d3f24(int *self, int arg1) {
    int *base = (int *)self[0x21];
    int v[3];

    VEC_Add((void *)base[0x12], (void *)base[0x13], v);
    func_01ffa724(0x800, v, v);
    func_0203bc78((int)self, arg1);
}
