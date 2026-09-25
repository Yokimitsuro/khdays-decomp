/* main .rodata 0x02041e6c-0x02041eac: two tables of the BG setup helpers. */

/* Per-BG screen-load command ids (main BG0-3 = 4..7, sub BG0-3 = 20..23), returned by
 * func_02024a18 for a BG index. */
const int data_02041e6c[8] = { 4, 5, 6, 7, 20, 21, 22, 23 };

/* BG3 as an extended (bitmap) BG, indexed by the current BG mode (DISPCNT & 7); entries >= 8 are
 * folded back into 0..7 (func_02024574 main / func_020247f4 sub). */
const int data_02041e8c[8] = { 3, 3, 4, 4, 4, 5, 11, 11 };
