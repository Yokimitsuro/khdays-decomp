/* ov008 screen hook slots data_ov008_0209009c, 0x0209009c-0x020900d8 (.data): the eight screen
 * classes dispatched by index in Ov008_Fn_137c / 020513bc / 020513f0 (six of
 * ov008, two of ov025), each followed by a -1 word except the last, whose
 * word is the class descriptor that follows at 0x020900d8.
 */

extern char data_ov008_02090148;
extern char data_ov008_020902e8;
extern char data_ov008_02090380;
extern char data_ov008_0209041c;
extern char data_ov008_02090460;
extern char data_ov008_02090554;
extern char data_ov025_020b516c;
extern char data_ov025_020b51f8;

const void *data_ov008_0209009c[15] = {
    &data_ov008_02090148,
    (void *)0xffffffff,
    &data_ov008_020902e8,
    (void *)0xffffffff,
    &data_ov008_02090380,
    (void *)0xffffffff,
    &data_ov008_0209041c,
    (void *)0xffffffff,
    &data_ov008_02090460,
    (void *)0xffffffff,
    &data_ov008_02090554,
    (void *)0xffffffff,
    &data_ov025_020b516c,
    (void *)0xffffffff,
    &data_ov025_020b51f8,
};
