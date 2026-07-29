/* func_ov008_0205b438 -- Ov008_TickMenuTimer (180 B, 8 relocs).
 * Per-frame tick for a timed menu element. Once (guarded by flag14dc), when the 64-bit tick
 * counter has advanced past the stored deadline (stored + 0x7fd88 < func_020031d4()), it marks
 * the flag and fires the one-shot func_ov008_0205b4ec(field14e8, field14e4). It always ticks the
 * sub-object at +4 (func_ov008_0205c4c4). Then, if field14e0 is set and func_02023588(0x200d)
 * returns 0, it refreshes widget id 2 with the (u16) value from func_ov105_020bd7c4 via
 * func_ov008_02054c80. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct Ov008TimerState {
    u8  pad_0000[4];
    u8  sub_0004[0x14d4 - 4];   /* 0x4: sub-object ticked by func_ov008_0205c4c4 */
    u64 stored;                 /* 0x14d4: 64-bit deadline base */
    int flag14dc;               /* 0x14dc: one-shot fired flag */
    int field14e0;              /* 0x14e0 */
    int field14e4;              /* 0x14e4 */
    int field14e8;              /* 0x14e8 */
} Ov008TimerState;

extern u64   func_020031d4(void);
extern void  func_ov008_0205b4ec(int a, int b);
extern void  func_ov008_0205c4c4(void *sub);
extern int   func_02023588(int a);
extern void *func_ov008_02050c54(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern int   func_ov105_020bd7c4(void);
extern void  func_ov008_02054c80(void *ctx, void *widget, int value);

void func_ov008_0205b438(Ov008TimerState *param_1)
{
    void *ctx;
    void *widget;

    if (param_1->flag14dc == 0) {
        u64 now = func_020031d4();
        if (param_1->stored + 0x7fd88 < now) {
            param_1->flag14dc = 1;
            func_ov008_0205b4ec(param_1->field14e8, param_1->field14e4);
        }
    }
    func_ov008_0205c4c4(&param_1->sub_0004);
    if (param_1->field14e0 == 0) {
        return;
    }
    if (func_02023588(0x200d) != 0) {
        return;
    }
    ctx = func_ov008_02050c54();
    widget = func_ov008_02054788(ctx, 2);
    func_ov008_02054c80(ctx, widget, (u16)func_ov105_020bd7c4());
}
