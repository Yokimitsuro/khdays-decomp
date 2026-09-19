/* func_ov158_020cdad0 -- commit the move once the counter allows. If the counter at +0x40 has
 * reached 0x100 nothing happens. Otherwise a 2-field descriptor is built from
 * data_ov158_020cf540 and passed to the owner's own hook (+0x24) if it has one, the delay at
 * +0x14 is set to the short value (x * 30 / 10), the owner is retuned (mode 7), the progress
 * fields (+0x3c/+0x54) cleared, the rig at +0x39c reset, and the action dispatched with
 * func_ov158_020cdb88. */

typedef struct {
    unsigned short a;
    unsigned short b;
} Ov158_Desc;

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov107_020c9ee8(int rig, int a, int b);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov158_020cdb88(void);
extern unsigned short data_ov158_020cf540[];

void func_ov158_020cdad0(int self) {
    int *ctx;
    Ov158_Desc d;
    Ov158_Desc *p;
    void (*hook)(int, Ov158_Desc *, int);

    ctx = *(int **)(self + 4);
    if (ctx[0x10] >= 0x100) {
        return;
    }

    p = &d;
    d.b = data_ov158_020cf540[1];
    d.a = data_ov158_020cf540[0];
    hook = *(void (**)(int, Ov158_Desc *, int))(ctx[0] + 0x24);
    if (hook != 0) {
        hook(ctx[0], p, 4);
    }

    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    func_ov107_020c9264(ctx[0], 7, 0);
    ctx[0xf] = 0;
    *(unsigned char *)((char *)ctx + 0x54) = 0;
    func_ov107_020c9ee8(*(int *)(ctx[0] + 0x39c), 0, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov158_020cdb88);
}
