/* func_ov025_020a13d8 -- Ov008_ChangeMenuSelection (160 B, 9 relocs).
 * Moves the menu selection to newSel with a fade transition. No-op if already selected
 * (p->sel == newSel). Kicks a fade on the sub-animation at p+0x1c (func_02035fb0 target
 * p->field38 << 12, offset newSel ? 0xc0000 : 0, duration param3; then func_02035ffc starts it),
 * bumps a global (func_ov025_02084cf0(1)), records the new selection (p->sel = newSel), refreshes
 * dependent state (func_ov025_020a11c4), and disables the confirm/back buttons (ids 0x47, 0x48).
 * The offset ternary is written `newSel == 0 ? 0 : 0xc0000` so mwcc emits moveq(#0) before
 * movne(#0xc0000) as the ROM does (the != form flips the two conditional movs). */
typedef unsigned char u8;

typedef struct Ov008SelState {
    u8  pad_0000[0x1c];
    u8  fade[0x38 - 0x1c];   /* 0x1c: fade/animation sub-object */
    int field38;             /* 0x38 */
    u8  pad_003c[0x44 - 0x3c];
    int sel;                 /* 0x44 */
} Ov008SelState;

extern void *func_ov025_02084a8c(void);
extern void  func_02035fb0(void *fade, int mode, int target, int a, int dur);
extern void  func_02035ffc(void *fade);
extern void  func_ov025_02084cf0(int value);
extern void  func_ov025_020a11c4(Ov008SelState *p);
extern void *func_ov025_0208843c(void *ctx, int id);
extern void  func_ov025_0208884c(void *ctx, void *widget, int flag);

void func_ov025_020a13d8(Ov008SelState *p, int newSel, int param3)
{
    void *ctx = func_ov025_02084a8c();

    if (p->sel == newSel) {
        return;
    }
    func_02035fb0(&p->fade, 2, p->field38 << 12, newSel == 0 ? 0 : 0xc0000, param3);
    func_02035ffc(&p->fade);
    func_ov025_02084cf0(1);
    p->sel = newSel;
    func_ov025_020a11c4(p);
    func_ov025_0208884c(ctx, func_ov025_0208843c(ctx, 0x47), 0);
    func_ov025_0208884c(ctx, func_ov025_0208843c(ctx, 0x48), 0);
}
