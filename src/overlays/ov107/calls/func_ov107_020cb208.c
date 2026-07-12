/* Unless the object is inactive or locked, resolve the target via 02033d0c and dispatch. */
extern int func_02033d0c(int a, int b, int c, int d);
extern int func_0203c634(int, int, void *);
extern int func_ov107_020cb178(int);
struct sb0 { int b0 : 1; };
void func_ov107_020cb208(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    if (((struct sb0 *)(obj + 0x40))->b0 == 0) return;
    if (*(unsigned char *)(obj + 0x1c4) & 2) return;
    *(int *)(owner + 0x10) = func_02033d0c((short)*(short *)(owner + 4),
        *(unsigned char *)(owner + 6), *(int *)(owner + 0xc) + 0x10, 2);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov107_020cb178);
}
