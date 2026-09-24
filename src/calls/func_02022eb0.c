#pragma thumb on
/* func_02022eb0 -- pause menu confirmation page (yes / no), MAIN (THUMB). B or an inactive menu
 * (func_020208e0) resets the page cursor (data_02042730, "no" by default) to 1, returns to the
 * pause menu (func_02022d7c) and closes. Otherwise the page cursor moves (func_02022cb0); A (or
 * key bit 1, which forces "no") acts on it: "yes" (0) confirms the pause menu entry (+0xd4) --
 * entry 1 just closes, entry 2 calls into the overlay (func_ov002_0206d8a0), closes and sets game
 * field 0x20ef --; "no" (1) restores the pause menu layout (3 entries when func_02020a9c bit 1 is
 * set, else 2), reselects its entry, redraws the panels and returns to func_02022d7c. Every other
 * frame refreshes the panels for the page cursor (func_02023364) and ends with func_020230e8. The
 * cursor is defined here (the ROM keeps two pool words for it). */
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
} TabContext;

typedef struct {
    char pad0000[4];
    TabContext *pCtx;                   /* +0x04 */
} Root0204be08;

extern Root0204be08 data_0204be08;
extern unsigned short data_0204c190;    /* keys pressed this frame */
/* khdays: shared-bss */
int data_02042730 = 1;                  /* two-tab page cursor */

extern int func_020208e0(void);
extern void func_02033b78(int a, int b);            /* play menu sound */
extern void func_02023008(void);                    /* close the menu */
extern void func_02022cb0(int *pIndex);
extern int func_02020a9c(void);
extern void func_02020888(int a, void (*step)(void), int b);
extern void func_02023204(void);
extern void MI_CpuFill8(void *dest, int data, unsigned int size);
extern void func_02023400(void *panel, int index, int state);
extern void func_020230e8(void);
extern void func_02023364(int cursor);
extern void func_ov002_0206d8a0(int a);
extern void func_020235e8(int flag, int a, int b);  /* GameState_SetFlag */
extern void func_02022d7c(void);

void func_02022eb0(void)
{
    TabContext *ctx = data_0204be08.pCtx;
    int i;

    if ((data_0204c190 & 8) || func_020208e0() == 0) {
        data_02042730 = 1;
        func_02033b78(0, 3);
        func_02020888(1, func_02022d7c, 0);
        func_02023008();
        return;
    }
    func_02022cb0(&data_02042730);
    if ((data_0204c190 & 1) || (data_0204c190 & 2)) {
        if (data_0204c190 & 2) {
            data_02042730 = 1;
        }
        switch (data_02042730) {
        case 0:
            func_02033b78(0, 1);
            data_02042730 = 1;
            switch (ctx->cursor) {
            case 2:
                func_ov002_0206d8a0(0);
                func_02023008();
                func_020235e8(0x20ef, 1, 0);
                return;
            case 1:
                func_02023008();
                return;
            }
            break;
        case 1:
            func_02033b78(0, 3);
            ctx->count = (func_02020a9c() & 2) ? 3 : 2;
            func_02023204();
            MI_CpuFill8(ctx->slots, 0, sizeof(ctx->slots));
            ctx->slots[ctx->cursor].selected = 1;
            for (i = 0; i < ctx->count; i++) {
                func_02023400(ctx->panel, i, ctx->slots[i].selected);
            }
            func_02020888(1, func_02022d7c, 0);
            break;
        }
    }
    func_02023364(data_02042730);
    func_020230e8();
}
#pragma thumb off
