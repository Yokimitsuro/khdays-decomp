/* func_ov011_0205c5e4 -- Ov011_TickTitleFadeOut (MATCHED, 280 B, 9 relocs).
 *
 * Title fade-out per-frame tick (a state-table entry). Interpolates a blend alpha from
 * the global frame timer between the scene's fade start/end times (pScene+0x2cf4c /
 * +0x2cf4e, func_0202060c, clamped to 0x10), then drives BOTH engines' master brightness
 * to -alpha (func_0201e374 / func_0201e3cc) to fade the title out. Once the timer passes
 * the fade end and func_02034014(0) is clear, it (optionally) fires func_02000fb4 when the
 * mode field is 1 and sets the next state (pScene+4) to 5 or 6 depending on pScene+0x23ac4.
 * Finally it dispatches the current sub-state via data_ov011_0205e8cc[pScene->mode](), and
 * when the mode is 3 forwards pScene+0x28508 to the scene-transition helper func_0203256c.
 *
 * Match idiom (mirrors the tick cb18, opposite of the fade tick c884): access
 * data_ov011_0205e960 BY NAME every time (the ROM reloads the globals pointer on each use;
 * caching pScene/timer in locals promotes them to callee-saved regs and inflates the frame).
 * The fade-complete threshold is written timer-first (`nTimer >= end`) to get the ROM's
 * `cmp timer,end; blo` rather than the reversed `cmp end,timer; bhi`.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef void (*Ov011StateFn)(void);

typedef struct Ov011FadePane { u16 startTime; u16 endTime; } Ov011FadePane;
typedef struct Ov011Globals { u32 nTimer; u8 *pScene; } Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern Ov011StateFn data_ov011_0205e8cc[];
extern int  data_ov011_0205e930;

extern long long func_0202060c(int a, int b);
extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern int  func_02034014(int a);
extern void func_02000fb4(int a, void *b);
extern void func_0203256c(void *a);

void func_ov011_0205c5e4(void)
{
    Ov011FadePane *fade;
    u16 end;
    int alpha, neg;

    fade = (Ov011FadePane *)(data_ov011_0205e960.pScene + 0x2cf4c);
    end = fade->endTime;
    if (end <= data_ov011_0205e960.nTimer) {
        alpha = 0x10;
    } else {
        u16 start = fade->startTime;
        alpha = (u16)func_0202060c((int)(data_ov011_0205e960.nTimer - start) * 0x10, end - start);
    }
    neg = -(int)(short)alpha;
    func_0201e374(neg);
    func_0201e3cc(neg);

    if (data_ov011_0205e960.nTimer >= *(u16 *)(data_ov011_0205e960.pScene + 0x2cf4e) &&
        func_02034014(0) == 0) {
        if (*(int *)(data_ov011_0205e960.pScene + 8) == 1) {
            func_02000fb4(1, &data_ov011_0205e930);
        }
        *(int *)(data_ov011_0205e960.pScene + 4) =
            (*(int *)(data_ov011_0205e960.pScene + 0x23ac4) == 1) ? 5 : 6;
    }

    data_ov011_0205e8cc[*(int *)(data_ov011_0205e960.pScene + 8)]();

    if (*(int *)(data_ov011_0205e960.pScene + 8) == 3) {
        func_0203256c(data_ov011_0205e960.pScene + 0x28508);
    }
}
