/* func_ov137_020cdac4 -- set the follow-up delay, and if the counter allows, commit the move.
 * The delay at +0x14 is first set to the long value (x * 30 / 5). If the counter at +0x40 has
 * reached 0x100 that is all that happens -- the long delay stands.
 * Otherwise a 2-field descriptor is built from data_ov137_020cf37c and passed to the owner's own
 * hook (+0x24) if it has one, the delay is REPLACED with the short value (x * 30 / 10), the owner
 * is retuned (mode 7), the progress fields (+0x3c/+0x54) cleared, the rig at +0x39c reset, and
 * the action dispatched with func_ov137_020cdba0.
 *
 * Both delays are kept unfolded on purpose: mwcc emits mul #0x1e then the 0x66666667 magic --
 * asr #1 for the /5 and asr #2 for the /10. Folding them to `x * 6` and `x * 3` would change
 * behaviour, since the x*30 intermediate can overflow. The two shifts are how you tell the
 * divisors apart; they are otherwise identical sequences. */

typedef struct {
    unsigned short a;
    unsigned short b;
} Ov137_Desc;

extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov107_020c9ee8(int rig, int a, int b);
extern void func_0203c634(int self, int action, void (*cb)(void));
extern void func_ov137_020cdba0(void);
extern unsigned short data_ov137_020cf37c[];

void func_ov137_020cdac4(int self) {
    int *ctx;
    Ov137_Desc d;
    Ov137_Desc *p;
    void (*hook)(int, Ov137_Desc *, int);

    ctx = *(int **)(self + 4);
    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 5;
    if (ctx[0x10] >= 0x100) {
        return;
    }

    p = &d;
    d.b = data_ov137_020cf37c[1];
    d.a = data_ov137_020cf37c[0];
    hook = *(void (**)(int, Ov137_Desc *, int))(ctx[0] + 0x24);
    if (hook != 0) {
        hook(ctx[0], p, 4);
    }

    ctx[5] = *(int *)(*(int *)self + 0x2c) * 30 / 10;
    func_ov107_020c9264(ctx[0], 7, 0);
    ctx[0xf] = 0;
    *(unsigned char *)((char *)ctx + 0x54) = 0;
    func_ov107_020c9ee8(*(int *)(ctx[0] + 0x39c), 0, 0);
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov137_020cdba0);
}
