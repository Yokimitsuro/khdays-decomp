/* ov008 .bss, 0x02090fa0-0x02090fc0: the overlay's zero-initialised globals.
 *
 * mwcc orders a translation unit's .bss by size and, within a size, by its
 * own symbol hashing, so the ROM's layout (a 4-byte word before two 8-byte
 * pairs, then 4-byte words before the 28- and 96-byte blocks) can only come
 * from several objects linked in address order: this is one of the four,
 * with its declarations in the order that reproduces the addresses
 * (tools/verify_bss.py proves the layout).
 */

/* the shop parameter table (Ov008ParamTable *, 0x02090fb0), the shared
 * panel context (Ov008PanelContext *, 0x02090fac), the reward list pointer
 * (0x02090fa8), the character select context (0x02090fa4), the mission menu
 * context (0x02090fa0) and the 12-byte card transfer context (0x02090fb4) */
void *data_ov008_02090fb0 = 0;
void *data_ov008_02090fac = 0;
void *data_ov008_02090fa8 = 0;
void *data_ov008_02090fa4 = 0;
void *data_ov008_02090fa0 = 0;
int data_ov008_02090fb4[3] = {0};
