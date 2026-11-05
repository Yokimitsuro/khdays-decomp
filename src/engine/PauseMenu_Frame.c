#pragma thumb on
/* PauseMenu_Frame -- pause menu frame handler, MAIN (THUMB). Closes the menu (sound 3, Callbacks_ClearByteAndRun2)
 * when PauseMenu_GetMode reports it inactive or B (bit 3 of the pressed keys) is pressed; while the
 * post-confirm timer (+0xc8) runs it counts down. Otherwise, unless game field 0x2483 is set, it
 * moves the entry cursor (+0xd4, TabPanel_HandleUpDown) and on A (bit 0): entry 0 resumes (closes the
 * menu); a later entry either hands over to the overlay (Ov023_RequestEventSkip, +0xe0 set, next step
 * PauseMenu_OpenIfAllowed) or, when LoadGlobalU16At0 bit 1 is set, switches to the yes/no confirmation layout
 * (+0xd0 = 2, "no" selected, panels redrawn) handled by PauseMenu_ConfirmFrame. Each frame without a
 * switch refreshes the panels for the current entry (Input_DebounceSlot) and ends with ForwardQuery64Result. */
typedef struct {
    int debounce;                       /* +0x00 */
    int selected;                       /* +0x04 */
} PanelSlot;

typedef struct {
    char pad0000[0xc];
    char panel[0xa0];                   /* +0x0c -- opaque, passed to SubObject_NudgeAndRedraw */
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
extern unsigned short gPadPressed;    /* keys pressed this frame */

extern int PauseMenu_GetMode(void);
extern void PlaySound(int a, int b);            /* play menu sound */
extern void Callbacks_ClearByteAndRun2(void);                    /* close the menu */
extern int GameState_IsFlagSet(int flag);                 /* GameState_IsFlagSet */
extern void TabPanel_HandleUpDown(int *pIndex);
extern int LoadGlobalU16At0(void);
extern void SoundMgr_StopAllSePlayers(void);
extern void Ov023_RequestEventSkip(void);
extern void setDualArrayEntry(int a, void (*step)(void), int b);
extern void SubObject_SetupDraws(void);
extern void SubObject_NudgeAndRedraw(void *panel, int index, int state);
extern void ForwardQuery64Result(void);
extern void Input_DebounceSlot(int cursor);
extern void PauseMenu_OpenIfAllowed(void);
extern void PauseMenu_ConfirmFrame(void);

void PauseMenu_Frame(void)
{
    TabContext *ctx = data_0204be08.pCtx;
    int i;

    if (PauseMenu_GetMode() == 0) {
        PlaySound(0, 3);
        Callbacks_ClearByteAndRun2();
        return;
    }
    if (ctx->timer == 0) {
        if (gPadPressed & 8) {
            PlaySound(0, 3);
            Callbacks_ClearByteAndRun2();
            return;
        }
        if (GameState_IsFlagSet(0x2483) == 0) {
            TabPanel_HandleUpDown(&ctx->cursor);
            if (gPadPressed & 1) {
                if (ctx->cursor == 0) {
                    Callbacks_ClearByteAndRun2();
                    PlaySound(0, 1);
                    return;
                }
                if (!(LoadGlobalU16At0() & 2)) {
                    SoundMgr_StopAllSePlayers();
                    PlaySound(0, 1);
                    Ov023_RequestEventSkip();
                    ctx->handedOver = 1;
                    setDualArrayEntry(1, PauseMenu_OpenIfAllowed, 0);
                    return;
                }
                PlaySound(0, 1);
                ctx->count = 2;
                SubObject_SetupDraws();
                ctx->slots[0].selected = 0;
                ctx->slots[1].selected = 1;
                for (i = 0; i < ctx->count; i++) {
                    SubObject_NudgeAndRedraw(ctx->panel, i, ctx->slots[i].selected);
                }
                setDualArrayEntry(1, PauseMenu_ConfirmFrame, 0);
                ForwardQuery64Result();
                return;
            }
        } else {
            ForwardQuery64Result();
            return;
        }
    } else {
        ctx->timer--;
    }
    Input_DebounceSlot(ctx->cursor);
    ForwardQuery64Result();
}
#pragma thumb off
