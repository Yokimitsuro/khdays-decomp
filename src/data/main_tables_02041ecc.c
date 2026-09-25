/* main .rodata 0x02041ecc-0x02041fd4: BG-mode selection and GFX command tables of the BG setup
 * helpers (0x020243f4..0x02024b04).
 *
 * Each BG-mode table is indexed by the current BG mode (DISPCNT & 7, main or sub engine) and gives
 * the BG mode the helper switches to so that BG2/BG3 can take the requested layout;
 * func_020241f8 (main) and func_0202423c (sub) fold entries >= 8 back into 0..7 before calling
 * the SetGraphicsMode routine. */

typedef void (*GfxCallback)(void);

extern void func_0202417c(void);

/* BG3 as an affine BG (BG3CNT with the wrap bit): func_020244d4 / func_02024754. */
const int data_02041ecc[8] = { 1, 1, 2, 1, 2, 9, 9, 9 };

/* BG3 as a 256-colour text BG (BG3CNT bit 7): func_0202443c / func_020246bc. */
const int data_02041eec[8] = { 0, 0, 8, 0, 8, 8, 8, 8 };

/* BG2 as an extended (bitmap) BG: func_02024524 / func_020247a4. */
const int data_02041f0c[8] = { 13, 13, 13, 5, 5, 5, 13, 13 };

/* BG2 as an affine BG: func_02024484 / func_02024704. */
const int data_02041f2c[8] = { 10, 2, 2, 4, 4, 4, 12, 10 };

/* BG2 as a 256-colour text BG (BG2CNT bit 7): func_020243f4 / func_02024674; followed by the
 * per-BG character-load command ids (main BG0-3 = 8..11, sub BG0-3 = 24..27). */
const struct {
    int bg2TextMode[8];
    int charCmd[8];
} data_02041f4c = {
    { 0, 1, 1, 3, 3, 3, 11, 8 },
    { 8, 9, 10, 11, 24, 25, 26, 27 },
};

/* Per-BG screen-load command ids (main BG0-3 = 4..7, sub BG0-3 = 20..23) queued by
 * func_02024ae0. */
const int data_02041f8c[8] = { 4, 5, 6, 7, 20, 21, 22, 23 };

/* Per-BG character-load command ids queued by func_02024b04, then the handler slot that follows
 * the table (func_0202417c) and a terminating zero. */
const struct {
    int cmd[8];
    GfxCallback handler;
    int end;
} data_02041fac = {
    { 8, 9, 10, 11, 24, 25, 26, 27 },
    func_0202417c,
    0,
};
