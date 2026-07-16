/* func_ov024_02082960 -- MobiClip: drive one step of the player's screen fade.
 *
 * The fade state lives in the control block at player + 0x8000, the same one
 * func_ov024_02082e04 fills in when it posts a stop request:
 *   +0xbe2  which screens (0 = main, 1 = sub, 2 = both)
 *   +0xbe4  direction (0 = fade to black, anything else = fade to white)
 *   +0xbe8  step counter, primed to -1
 *
 * A negative counter means no fade is running: the screens are simply forced black, and only
 * once func_ov024_02084e68 reports the clock has started. Once the counter reaches 0x10 the fade
 * is finished and nothing more happens. In between it steps and writes the master brightness,
 * negated for a fade to black.
 *
 * 0x0400006c / 0x0400106c are REG_MASTER_BRIGHT for the main and sub engines. They are pool
 * LITERALS, not symbols -- all seven relocs in this function are its bl's.
 *
 * NONMATCHING: 200/200 bytes, every instruction in the right place. Only an r1/r2 swap: the ROM
 * puts the control base in r1 and the step in r2, mwcc mirrors the pair, and it carries through.
 * Tried and rejected: swapping the locals' decl order, and naming `step` explicitly instead of
 * letting mwcc CSE the field read. Same diff at 0x5 -- regalloc permutation, see deferred-ties.md.
 *
 * Two knobs DID matter and must be kept -- the mix of addressing forms is deliberate:
 * 1. `ctl` must be a pointer local for the counter accesses. Folding them into constant offsets
 *    (`*(int *)(player + 0x8be8)`) makes mwcc materialise the full address for the STORE
 *    (add #0x3e8 ; add #0x8800), +8 B -- the same store/load asymmetry as func_ov024_02082e04.
 * 2. The +0xbe2 read stays FOLDED (`player + 0x8be2`) on purpose. The ROM really does derive
 *    player+0x8000 a second time for it (`add r0,r0,#0x8000 ; ldrb r0,[r0,#0xbe2]`) even though
 *    r1 already holds that address -- reaching it through `ctl` instead saves an instruction and
 *    comes out 4 B short.
 */
extern int func_ov024_02084e68(void);
extern void GXx_SetMasterBrightness_(volatile unsigned short *reg, int brightness);

#define REG_MASTER_BRIGHT     ((volatile unsigned short *)0x0400006c)
#define REG_DB_MASTER_BRIGHT  ((volatile unsigned short *)0x0400106c)

void func_ov024_02082960(int player) {
    char *ctl;
    int step;
    int level;

    ctl = (char *)(player + 0x8000);
    step = *(int *)(ctl + 0xbe8);
    if (step < 0) {
        if (func_ov024_02084e68() <= 0) {
            return;
        }
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, 0);
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, 0);
        return;
    }
    if (step >= 0x10) {
        return;
    }
    *(int *)(ctl + 0xbe8) = step + 1;

    level = *(int *)(ctl + 0xbe4) == 0 ? -*(int *)(ctl + 0xbe8) : *(int *)(ctl + 0xbe8);

    switch (*(unsigned char *)(player + 0x8be2)) {
    case 0:
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, level);
        break;
    case 1:
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, level);
        break;
    case 2:
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT, level);
        GXx_SetMasterBrightness_(REG_DB_MASTER_BRIGHT, level);
        break;
    }
}
