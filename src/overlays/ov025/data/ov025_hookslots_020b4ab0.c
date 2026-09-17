/* ov025 screen hook slots data_ov025_020b4ab0, 0x020b4ab0-0x020b4aec (.data): the eight screen
 * classes dispatched by index (0208512c .. 02085890: the records hub, main menu,
 * grid list menu, transition, grid, config, tutorial and reports screens), each
 * followed by a -1 word except the last, whose word is the class descriptor
 * that follows at 0x020b4aec.
 */

extern char data_ov025_020b4b70;
extern char data_ov025_020b4cb4;
extern char data_ov025_020b4d4c;
extern char data_ov025_020b4de8;
extern char data_ov025_020b4e2c;
extern char data_ov025_020b4f20;
extern char data_ov025_020b516c;
extern char data_ov025_020b51f8;

const void *data_ov025_020b4ab0[15] = {
    &data_ov025_020b4b70,
    (void *)0xffffffff,
    &data_ov025_020b4cb4,
    (void *)0xffffffff,
    &data_ov025_020b4d4c,
    (void *)0xffffffff,
    &data_ov025_020b4de8,
    (void *)0xffffffff,
    &data_ov025_020b4e2c,
    (void *)0xffffffff,
    &data_ov025_020b4f20,
    (void *)0xffffffff,
    &data_ov025_020b516c,
    (void *)0xffffffff,
    &data_ov025_020b51f8,
};
