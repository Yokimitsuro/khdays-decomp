/* func_ov025_02097de8 -- Ov008_UpdateReadyState (212 B, 11 relocs).
 * Enables the confirm widgets once the screen is "ready". Bails unless flag bit 2 of p->flags380
 * is set and both sentinel counters p->field384 and p->field388 have reached 0x7fffffff. Then it
 * clears p->field4, pulses func_ov025_02084868(1) and func_ov025_02084ccc(0), and enables widget
 * id 3 (func_ov025_0208884c on the widget from func_ov025_0208843c). Finally, when p->field10 == 2
 * it re-enables widget 3 and re-links widget 0x51 (only if p->field8 == 1); otherwise it just
 * re-enables widget 3. */
typedef unsigned char u8;
typedef struct Ov008EndState {
    u8  pad_0000[4];
    int field4;          /* 0x4 */
    int field8;          /* 0x8 */
    u8  pad_000c[0x10 - 0xc];
    int field10;         /* 0x10 */
    u8  pad_0014[0x380 - 0x14];
    struct { unsigned b0:1; unsigned b1:1; unsigned b2:1; unsigned rest:29; } flags380; /* 0x380 */
    int field384;        /* 0x384 */
    int field388;        /* 0x388 */
} Ov008EndState;

extern void *func_ov025_02084a7c(void);
extern void  func_ov025_02084868(int a);
extern void  func_ov025_02084ccc(int value);
extern void *func_ov025_0208843c(void *ctx, int id);
extern void  func_ov025_0208884c(void *ctx, void *widget, int flag);
extern void  func_ov025_0208f144(void *widget);

void func_ov025_02097de8(Ov008EndState *p)
{
    void *ctx = func_ov025_02084a7c();
    if (p->flags380.b2 == 0) {
        return;
    }
    if (p->field384 != 0x7fffffff || p->field388 != 0x7fffffff) {
        return;
    }
    p->field4 = 0;
    func_ov025_02084868(1);
    func_ov025_02084ccc(0);
    func_ov025_0208884c(ctx, func_ov025_0208843c(ctx, 3), 1);
    if (p->field10 == 2) {
        if (p->field8 != 1) {
            return;
        }
        func_ov025_0208884c(ctx, func_ov025_0208843c(ctx, 3), 1);
        func_ov025_0208f144(func_ov025_0208843c(ctx, 0x51));
    } else {
        func_ov025_0208884c(ctx, func_ov025_0208843c(ctx, 3), 1);
    }
}
