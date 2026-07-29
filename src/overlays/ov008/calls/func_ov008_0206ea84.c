/* func_ov008_0206ea84 -- Ov008_SetupMenuButtons (224 B, 12 relocs).
 * One-time enable pass for a set of menu buttons. Bails unless the state is ready
 * (p->fieldC != 0, and both p->field14 and p->field0 are 0). Grabs the widget context
 * (02050a64/02050c64), then for each button id looks the widget up (func_ov008_02054788)
 * and sets its enabled flag (func_ov008_02054ba4): id 0x29 (enabled) only when p->field44 is 0
 * -- and in that case also pulses func_02033b78(0,0) -- then id 0x51 (enabled), id 5 and id 0x80
 * (disabled). Finishes with func_ov008_0206c90c(p, p->field50, 1, 0) and marks the pass done
 * (p->field10 = p->field8 = 1). The readiness test is a short-circuit `||` guard. */
typedef unsigned char  u8;

typedef struct Ov008State {
    int field0;              /* 0x00 */
    u8  pad_0004[4];
    int field8;              /* 0x08 */
    int fieldC;              /* 0x0c */
    int field10;             /* 0x10 */
    int field14;             /* 0x14 */
    u8  pad_0018[0x44 - 0x18];
    int field44;             /* 0x44 */
    u8  pad_0048[0x50 - 0x48];
    int field50;             /* 0x50 */
} Ov008State;

extern void  func_ov008_02050a64(int a);
extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054ba4(void *ctx, void *widget, int flag);
extern void  func_02033b78(int a, int b);
extern void  func_ov008_0206c90c(Ov008State *p, int a, int b, int c);

void func_ov008_0206ea84(Ov008State *p)
{
    void *ctx;

    if (p->fieldC == 0) {
        return;
    }
    if (p->field14 != 0 || p->field0 != 0) {
        return;
    }
    func_ov008_02050a64(0);
    ctx = func_ov008_02050c64();
    if (p->field44 == 0) {
        func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 0x29), 1);
        func_02033b78(0, 0);
    }
    func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 0x51), 1);
    func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 5), 0);
    func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 0x80), 0);
    func_ov008_0206c90c(p, p->field50, 1, 0);
    p->field10 = 1;
    p->field8 = 1;
}
