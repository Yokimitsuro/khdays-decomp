/* func_ov008_020712f8 -- Ov008_UpdateScrollArrows (128 B, 6 relocs).
 * Enables/disables the menu's prev/next scroll arrows from the current index vs item count.
 * The prev-arrow widget id is chosen by func_ov008_02051028() (0x3f when non-zero, else 0x3d);
 * the next-arrow widget is id 0x3e. Both are disabled by default and only enabled when there is
 * something to scroll: with count = state->count > 0, the prev arrow is enabled if
 * state->index > 0 and the next arrow if state->index < count. Widget states are pushed via
 * func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, id), enabled). */
typedef unsigned char u8;

typedef struct Ov008ScrollState {
    u8  pad_0000[0x20];
    int index;              /* 0x20 */
    u8  pad_0024[4];
    int count;              /* 0x28 */
} Ov008ScrollState;

extern int   func_ov008_02051028(void);
extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054ba4(void *ctx, void *widget, int flag);

void func_ov008_020712f8(Ov008ScrollState *param_1)
{
    void *ctx;
    int id = func_ov008_02051028() != 0 ? 0x3f : 0x3d;
    int prevEnabled = 0;
    int nextEnabled = 0;
    int count = param_1->count;

    if (count > 0) {
        int idx = param_1->index;
        if (idx > 0) prevEnabled = 1;
        if (idx < count) nextEnabled = 1;
    }
    ctx = func_ov008_02050c64();
    func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, id), prevEnabled);
    func_ov008_02054ba4(ctx, func_ov008_02054788(ctx, 0x3e), nextEnabled);
}
