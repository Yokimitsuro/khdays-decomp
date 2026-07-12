/* Snapshot the +0x30 vector, decay the +0x34 accumulator by delta*30/32, then dispatch if ready. */
extern int func_ov107_020c9264(int, int, int);
extern int func_0203c634(int, int, void *);
struct w3 { int a, b, c; };
struct bit0 { unsigned char b : 1; };
extern int func_ov137_020cd5a4(int);
void func_ov137_020cd514(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(struct w3 *)(owner + 0x18) = *(struct w3 *)(owner + 0x30);
    int delta = *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(owner + 0x34) -= (int)((((long long)(delta * 30) << 7) + 0x800) >> 12);
    if ((((struct bit0 *)(*(int *)owner + 0x17a))->b) == 0) return;
    func_ov107_020c9264(*(int *)owner, 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov137_020cd5a4);
}
