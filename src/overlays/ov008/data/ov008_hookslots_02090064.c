/* ov008 hook slots data_ov008_02090064, 0x02090064-0x0209009c (.data): the seven page classes dispatched by index in Ov008_Fn_1458 / 02051498 / 020514cc (five of ov008, two of ov025).
 */

typedef struct Ov008HookSlot {
    const void *pHooks;       /* 0x00: Ov008PageHooks / Ov008ScreenHooks, ov008's or ov025's */
    int nReserved;            /* 0x04: -1 */
} Ov008HookSlot;

extern char data_ov008_020907a0;
extern char data_ov008_0209082c;
extern char data_ov008_020908e0;
extern char data_ov008_020909d4;
extern char data_ov008_02090a14;
extern char data_ov025_020b54b8;
extern char data_ov025_020b56e4;

Ov008HookSlot data_ov008_02090064[7] = {
    { &data_ov008_020907a0, -1 },
    { &data_ov008_0209082c, -1 },
    { &data_ov008_020908e0, -1 },
    { &data_ov008_020909d4, -1 },
    { &data_ov008_02090a14, -1 },
    { &data_ov025_020b54b8, -1 },
    { &data_ov025_020b56e4, -1 },
};
