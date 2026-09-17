/* ov025 page hook slots data_ov025_020b4a78, 0x020b4a78-0x020b4ab0 (.data): the seven page classes of ov025 dispatched by index (02085208 .. 020858b0: the scrolling menu, mission list, mission menu, transition, mission detail, day list and report detail pages).
 */

typedef struct Ov008HookSlot {
    const void *pHooks;       /* 0x00: Ov008PageHooks */
    int nReserved;            /* 0x04: -1 */
} Ov008HookSlot;

extern char data_ov025_020b5284;
extern char data_ov025_020b5310;
extern char data_ov025_020b53c4;
extern char data_ov025_020b54b8;
extern char data_ov025_020b5508;
extern char data_ov025_020b5548;
extern char data_ov025_020b56e4;

Ov008HookSlot data_ov025_020b4a78[7] = {
    { &data_ov025_020b5284, -1 },
    { &data_ov025_020b5310, -1 },
    { &data_ov025_020b53c4, -1 },
    { &data_ov025_020b5508, -1 },
    { &data_ov025_020b5548, -1 },
    { &data_ov025_020b54b8, -1 },
    { &data_ov025_020b56e4, -1 },
};
