/* func_ov008_02071468 -- Ov008_PositionListCursor (160 B, 6 relocs).
 * Positions menu widget id 1 (the list cursor). When param->field0 >= 0 the position is
 * computed from the row: x = 0, y = (((field0 << 5) - field0C) << 12) - 0x20000 (a fixed-point
 * row offset); the point is zero-initialized first (both x and y written 0) before y is set.
 * When field0 < 0 it uses the stored default point data_ov008_0208f8c8[0..1] (y assigned before
 * x, matching the ROM's store order). The widget is fetched with func_ov008_02054788(ctx, 1) and
 * moved with func_ov008_020548bc(ctx, widget, &point). */
typedef unsigned char u8;
typedef struct Vec2 { int x; int y; } Vec2;
typedef struct Ov008PosState { int field0; u8 pad_0004[8]; int field0C; } Ov008PosState;

extern void *func_ov008_02050c64(void);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_020548bc(void *ctx, void *widget, Vec2 *pt);
extern int   data_ov008_0208f8c8[2];

void func_ov008_02071468(Ov008PosState *param_1)
{
    void *ctx = func_ov008_02050c64();
    if (param_1->field0 >= 0) {
        Vec2 pt = {0, 0};
        pt.y = (((param_1->field0 << 5) - param_1->field0C) << 12) - 0x20000;
        func_ov008_020548bc(ctx, func_ov008_02054788(ctx, 1), &pt);
    } else {
        Vec2 pt;
        pt.y = data_ov008_0208f8c8[1];
        pt.x = data_ov008_0208f8c8[0];
        func_ov008_020548bc(ctx, func_ov008_02054788(ctx, 1), &pt);
    }
}
