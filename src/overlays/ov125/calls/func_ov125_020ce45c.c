/*
 * func_ov125_020ce45c -- push the object toward the midpoint of two node anchors, then hand
 * off. Through the +0x84 state's first word: v = (+0x394)->+0x14 + (+0x398)->+0x14 (VEC_Add);
 * scale v by 0x800 (01ffa724); then the 0203bc78 handoff with (self, arg1).
 */
extern void VEC_Add(void *a, void *b, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203bc78(int self, int arg1);

void func_ov125_020ce45c(int *self, int arg1) {
    char *base = *(char **)self[0x21];
    int v[3];

    VEC_Add(*(char **)(base + 0x394) + 0x14, *(char **)(base + 0x398) + 0x14, v);
    func_01ffa724(0x800, v, v);
    func_0203bc78((int)self, arg1);
}
