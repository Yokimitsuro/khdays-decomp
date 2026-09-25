/* ov009 .data 0x020562f4-0x02056338: the ov009 menu's callback block -- three entry points
 * (02053c18, 02053e24, 02053ec8), a -1 slot and the 0x1f04 flag word -- followed by the twelve
 * per-state handlers of its state machine (02053770 .. 02053c14; 02053c14 is the shared no-op
 * state, 02053af0 appears twice). */

typedef void (*Ov009Fn)(void);

extern void func_ov009_02053c18(void);
extern void func_ov009_02053e24(void);
extern void func_ov009_02053ec8(void);
extern void func_ov009_02053770(void);
extern void func_ov009_020537b8(void);
extern void func_ov009_0205388c(void);
extern void func_ov009_02053804(void);
extern void func_ov009_02053918(void);
extern void func_ov009_02053af0(void);
extern void func_ov009_02053c14(void);

struct {
    Ov009Fn entry[3];
    int nSlot;
    int nFlags;
    Ov009Fn state[12];
} data_ov009_020562f4 = {
    { func_ov009_02053c18, func_ov009_02053e24, func_ov009_02053ec8 },
    -1,
    0x1f04,
    {
        func_ov009_02053770, func_ov009_020537b8, func_ov009_0205388c, func_ov009_02053804,
        func_ov009_02053918, func_ov009_02053af0, func_ov009_02053c14, func_ov009_02053c14,
        func_ov009_02053c14, func_ov009_02053c14, func_ov009_02053c14, func_ov009_02053af0,
    },
};
