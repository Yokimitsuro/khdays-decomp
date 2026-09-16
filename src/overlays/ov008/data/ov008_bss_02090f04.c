/* ov008 .bss, 0x02090f04-0x02090f14: the overlay's zero-initialised globals.
 *
 * mwcc orders a translation unit's .bss by size and, within a size, by its
 * own symbol hashing, so the ROM's layout (a 4-byte word before two 8-byte
 * pairs, then 4-byte words before the 28- and 96-byte blocks) can only come
 * from several objects linked in address order: this is one of the four,
 * with its declarations in the order that reproduces the addresses
 * (tools/verify_bss.py proves the layout).
 */

/* the two mission-mode menu contexts (0205137c dispatch) and two words of page state */
void *data_ov008_02090f04[2] = {0, 0};
int data_ov008_02090f0c[2] = {0, 0};
