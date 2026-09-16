/* ov008 .bss, 0x02090f00-0x02090f04: the overlay's zero-initialised globals.
 *
 * mwcc orders a translation unit's .bss by size and, within a size, by its
 * own symbol hashing, so the ROM's layout (a 4-byte word before two 8-byte
 * pairs, then 4-byte words before the 28- and 96-byte blocks) can only come
 * from several objects linked in address order: this is one of the four,
 * with its declarations in the order that reproduces the addresses
 * (tools/verify_bss.py proves the layout).
 */

/* pointer to the campaign menu context (Ov008_InitCampaignMenuContext) */
void *data_ov008_02090f00 = 0;
