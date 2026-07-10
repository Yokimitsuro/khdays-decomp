/* NONMATCHING: register-coloring / CSE tie. The control word at obj+0x10 must live
 * in r3 (caller-saved) across the switch while obj=r5 and base=r4. Two near-misses,
 * neither reachable together:
 *   - bitfield-driven (w->sel / w->a / w->b): colors obj=r5, base=r4 correctly but
 *     splits the load, emitting one extra `mov r3,r6` (216 != 212).
 *   - raw-driven (cast-after-shift on an int local): loads straight into r3 with the
 *     right instruction count, but permutes obj->r4, base->r6 (byte diff @0x5).
 * Eight source forms tried (4 declaration orders, union, register, per-branch reads,
 * inlined table base). Semantics below are exact. */
extern unsigned int *func_01fffde0(int kind);
extern void func_ov022_020922a4(unsigned int *base, int obj, int a, int b);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int state);
extern int func_02020a9c(void);
extern void func_ov106_020b8140(int obj);
extern void func_ov002_02061df8(int obj);
extern void func_ov022_02092060(unsigned int *base, int v, int obj, int w);

/* The int at obj+0x10 is a packed control word. */
struct Ctl02091f8c {
    unsigned int kind : 2;   /* bits 0..1  -> selects the base block */
    unsigned int _p1 : 3;
    unsigned int sel : 4;    /* bits 5..8  -> dispatch selector */
    unsigned int _p2 : 2;
    unsigned int a : 12;     /* bits 11..22 */
    unsigned int b : 8;      /* bits 23..30 */
    unsigned int _p3 : 1;
};

void func_ov022_02091f8c(int arg0) {
    struct Ctl02091f8c *w = (struct Ctl02091f8c *)(arg0 + 0x10);
    unsigned int *base = func_01fffde0(w->kind);
    int raw = *(int *)w;
    unsigned int *tbl = base + 0x992;
    int s;
    switch (w->sel) {
    case 6:
        func_ov022_020922a4(base, arg0, w->a, w->b);
        return;
    case 7:
        s = func_ov022_02088474(func_01fffe14());
        if (s != func_ov022_02088474(*((unsigned char *)base + 9))) return;
        if (func_02020a9c() == 0x2a) func_ov106_020b8140(arg0);
        else func_ov002_02061df8(arg0);
        return;
    case 8:
        if (tbl[1] == 0) return;
        func_ov022_02092060(base, tbl[1], arg0, raw);
        return;
    }
    if (tbl[w->sel] == 0) return;
    func_ov022_02092060(base, tbl[w->sel], arg0, raw);
}
