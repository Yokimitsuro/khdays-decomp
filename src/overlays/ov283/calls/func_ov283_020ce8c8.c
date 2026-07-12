/* Unless bit 0 of +0x17a is clear, retract via 020cc830, kick anim 4, then dispatch. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct bit0 { unsigned char b : 1; };
extern int func_ov283_020cc830(int, int);
extern int func_ov283_020ce95c(int);
void func_ov283_020ce8c8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    if ((((struct bit0 *)(obj + 0x17a))->b) == 0) return;
    func_ov283_020cc830(obj, 3);
    func_ov107_020c9264(*(int *)owner, 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020ce95c);
}
