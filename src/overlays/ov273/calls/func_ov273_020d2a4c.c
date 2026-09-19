/* Face-target entry: dir = target(+0x3dc)+0x74 - self+0x74 flattened (y = 0) and normalised;
 * builds the aim pose at state+0x38 from data_02042264 and atan2(dir.x, dir.z), copies it down
 * to state+0x28 and, unless the +8 flag byte is set, plays pose 0x17 and hands off to 020ceeb8. */
struct m4 { int w[4]; };
struct S213 { char pad[0x28]; struct m4 dst; struct m4 src; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *v, void *out);
extern int  func_020050b4(int x, int z);
extern void func_0202f188(void *dst, void *k, int angle);
extern void func_0203c634(int self, int idx, int cb);
extern void func_ov273_020d2af8(void);
extern int  data_02042264;

void func_ov273_020d2a4c(int *self) {
    int *state = (int *)self[1];
    int v[3];

    VEC_Subtract((void *)(*(int *)(*state + 0x3dc) + 0x74), (void *)(*state + 0x74), v);
    v[1] = 0;
    func_01ff8d18(v, v);
    func_0202f188((void *)(state + 0xe), &data_02042264, func_020050b4(v[0], v[2]));
    ((struct S213 *)state)->dst = ((struct S213 *)state)->src;
    if (*(unsigned char *)state[2] != 0) return;
    func_ov107_020c9264(*state, 0x17, 0);
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov273_020d2af8);
}
