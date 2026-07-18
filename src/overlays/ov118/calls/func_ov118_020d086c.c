/* The `+ (v - v)` terms are the documented crack for func_02023eb4's copy artifact.
 * The second one needs its OWN local (`int r = …`): the ROM copies into a fresh register
 * (`add r1,r0,#0`), and inlining the expression makes mwcc copy in place (`add r0,r0,#0`)
 * and swap the multiply operands. */
extern int  func_02023eb4();
extern void func_ov107_020c9264(int owner, int a, int b);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov118_020d08f4(void);

void func_ov118_020d086c(int *self) {
    int v;
    int *obj = (int *)self[1];
    int sign;

    obj[10] = *(int *)(self[0] + 0x2c) * 0x1e / 20;
    func_ov107_020c9264(*obj, 1, 1);
    sign = func_02023eb4(2) + (v - v) != 0 ? -1 : 1;
    {
        int r = func_02023eb4(0x101) + (v - v);
        obj[0x17] = r * sign;
    }
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), &func_ov118_020d08f4);
}
