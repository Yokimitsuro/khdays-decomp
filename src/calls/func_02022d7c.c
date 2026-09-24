#pragma thumb on
/* func_02022d7c -- tab menu frame handler, MAIN (THUMB). Closes the menu (sound 3, func_02023008)
 * when func_020208e0 reports it inactive or B (bit 3 of the pressed keys) is pressed; while the
 * post-confirm timer (+0xc8) runs it counts down. Otherwise, unless game flag 0x2483 is set, it
 * moves the cursor (+0xd4, func_02022cb0) and on A (bit 0): tab 0 closes the menu, a later tab
 * either hands over to the overlay (func_ov023_02083aa8, +0xe0 set, next step func_02022fe4) or,
 * when func_02020a9c bit 1 is set, switches to the two-tab layout (+0xd0 = 2, tab 0 unselected,
 * tab 1 selected, panels redrawn) and re-enters through func_02022eb0. Each frame without a switch
 * refreshes the panels for the current cursor (func_02023364) and ends with func_020230e8. */
typedef struct {
    int debounce;                       /* +0x00 */
    int selected;                       /* +0x04 */
} PanelSlot;

typedef struct {
    char pad0000[0xc];
    char panel[0xa0];                   /* +0x0c -- opaque, passed to func_02023400 */
    PanelSlot slots[3];                 /* +0xac */
    int field_c4;
    int timer;                          /* +0xc8 */
    int field_cc;
    int count;                          /* +0xd0 */
    int cursor;                         /* +0xd4 */
    int field_d8;
    int field_dc;
    int handedOver;                     /* +0xe0 */
} TabContext;

typedef struct {
    char pad0000[4];
    TabContext *pCtx;                   /* +0x04 */
} Root0204be08;

extern Root0204be08 data_0204be08;
extern unsigned short data_0204c190;    /* keys pressed this frame */

extern int func_020208e0(void);
extern void func_02033b78(int a, int b);            /* play menu sound */
extern void func_02023008(void);                    /* close the menu */
extern int func_02023588(int flag);                 /* GameState_IsFlagSet */
extern void func_02022cb0(int *pIndex);
extern int func_02020a9c(void);
extern void func_02033bd4(void);
extern void func_ov023_02083aa8(void);
extern void func_02020888(int a, void (*step)(void), int b);
extern void func_020232d8(void);
extern void func_02023400(void *panel, int index, int state);
extern void func_020230e8(void);
extern void func_02023364(int cursor);
extern void func_02022fe4(void);
extern void func_02022eb0(void);

void func_02022d7c(void)
{
    TabContext *ctx = data_0204be08.pCtx;
    int i;

    if (func_020208e0() == 0) {
        func_02033b78(0, 3);
        func_02023008();
        return;
    }
    if (ctx->timer == 0) {
        if (data_0204c190 & 8) {
            func_02033b78(0, 3);
            func_02023008();
            return;
        }
        if (func_02023588(0x2483) == 0) {
            func_02022cb0(&ctx->cursor);
            if (data_0204c190 & 1) {
                if (ctx->cursor == 0) {
                    func_02023008();
                    func_02033b78(0, 1);
                    return;
                }
                if (!(func_02020a9c() & 2)) {
                    func_02033bd4();
                    func_02033b78(0, 1);
                    func_ov023_02083aa8();
                    ctx->handedOver = 1;
                    func_02020888(1, func_02022fe4, 0);
                    return;
                }
                func_02033b78(0, 1);
                ctx->count = 2;
                func_020232d8();
                ctx->slots[0].selected = 0;
                ctx->slots[1].selected = 1;
                for (i = 0; i < ctx->count; i++) {
                    func_02023400(ctx->panel, i, ctx->slots[i].selected);
                }
                func_02020888(1, func_02022eb0, 0);
                func_020230e8();
                return;
            }
        } else {
            func_020230e8();
            return;
        }
    } else {
        ctx->timer--;
    }
    func_02023364(ctx->cursor);
    func_020230e8();
}
#pragma thumb off
