/* ov008 .bss, 0x02090f14-0x02090fa0: the overlay's zero-initialised globals.
 *
 * mwcc orders a translation unit's .bss by size and, within a size, by its
 * own symbol hashing, so the ROM's layout (a 4-byte word before two 8-byte
 * pairs, then 4-byte words before the 28- and 96-byte blocks) can only come
 * from several objects linked in address order: this is one of the four,
 * with its declarations in the order that reproduces the addresses
 * (tools/verify_bss.py proves the layout).
 */

typedef unsigned short u16;

/* scene object handle (0x02090f14), transition counter (0x02090f20), var
 * text pointer (0x02090f1c), draw origin x / y (0x02090f18), the 28-byte
 * mission globals (0x02090f24) and the 96-byte mission name buffer (0x02090f40) */
void *data_ov008_02090f14 = 0;
int data_ov008_02090f20 = 0;
void *data_ov008_02090f1c = 0;
u16 data_ov008_02090f18[2] = {0, 0};
int data_ov008_02090f24[7] = {0};
u16 data_ov008_02090f40[48] = {0};
