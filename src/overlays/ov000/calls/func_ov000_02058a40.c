/* Ov000_SetupSceneVideo -- scene video bring-up for the ov000 menu/load screens.
 *
 * Clears the three main BG screen buffers, assigns the VRAM banks for both engines,
 * programs the two display control words, the BG priorities and the BG
 * character/screen bases, and powers on the second LCD.
 *
 * THE THREE SCREEN POINTERS GO THROUGH A LOCAL. Writing the natural
 *     MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
 * for each of the three buffers produces the right instructions but leaves the tail
 * of the function scheduled differently: mwcc then materialises the four register
 * base addresses one per read-modify-write group, where the ROM front-loads all of
 * them right after the first `ldr`. Assigning each call`s result to a reused local
 * first is what makes the tail come out identical -- and the tail itself is
 * completely inert to source shape (locals vs raw casts, nested blocks, SDK-style
 * inline setters, every declaration order), so this is not where anyone would look.
 *
 * Everything else here was already byte-exact and is kept deliberately:
 *  - callee arities come from the tree: func_020056b4 takes 3 args and is called
 *    (1, 0, 1); GXS_SetGraphicsMode takes 1; every GX_SetBankFor* takes 1.
 *  - the ROM really does write BG1CNT TWICE in the main-screen block, priority 1 and
 *    then priority 2, before writing BG3CNT with priority 3. Verified in the raw
 *    encodings (E1D310B0, E1D310B0, E1D310B4: offsets 0, 0 and 4 from 0x0400000A),
 *    while the sub-screen block is the symmetric BG0/BG1/BG3. It looks like an
 *    off-by-one in the original source and is reproduced on purpose.
 */
typedef unsigned short u16;
typedef unsigned int   u32;

extern void  func_0201e1d0(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void  MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void  GX_SetBankForBG(int bank);
extern void  GX_SetBankForOBJ(int bank);
extern void  GX_SetBankForBGExtPltt(int bank);
extern void  func_020056b4(int a, int b, int c);
extern void  GX_SetBankForSubBG(int bank);
extern void  GX_SetBankForSubOBJ(int bank);
extern void  GX_SetBankForSubBGExtPltt(int bank);
extern void  GX_SetBankForSubOBJExtPltt(int bank);
extern int   GXS_SetGraphicsMode(int mode);

static volatile u32 *const REG_DISPCNT     = (volatile u32 *)0x04000000;
static volatile u16 *const REG_BG1CNT      = (volatile u16 *)0x0400000a;
static volatile u16 *const REG_BG2CNT      = (volatile u16 *)0x0400000c;
static volatile u16 *const REG_BG3CNT      = (volatile u16 *)0x0400000e;
static volatile u32 *const REG_DB_DISPCNT  = (volatile u32 *)0x04001000;
static volatile u16 *const REG_DB_BG0CNT   = (volatile u16 *)0x04001008;
static volatile u16 *const REG_DB_BG1CNT   = (volatile u16 *)0x0400100a;
static volatile u16 *const REG_DB_BG3CNT   = (volatile u16 *)0x0400100e;
static volatile u16 *const REG_POWCNT1     = (volatile u16 *)0x04000304;

void func_ov000_02058a40(void)
{
    func_0201e1d0();
    {
        void *p;

        p = G2_GetBG1ScrPtr();
        MIi_CpuClearFast(0, p, 0x800);
        p = G2_GetBG2ScrPtr();
        MIi_CpuClearFast(0, p, 0x800);
        p = G2_GetBG3ScrPtr();
        MIi_CpuClearFast(0, p, 0x800);
    }

    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetBankForBGExtPltt(0);
    *REG_DISPCNT = (*REG_DISPCNT & 0xffcfffef) | 0x10 | 0x200000;
    func_020056b4(1, 0, 1);

    *REG_BG1CNT = (*REG_BG1CNT & ~3) | 1;
    *REG_BG1CNT = (*REG_BG1CNT & ~3) | 2;
    *REG_BG3CNT = (*REG_BG3CNT & ~3) | 3;
    *REG_DISPCNT = (*REG_DISPCNT & ~0x1f00) | 0x1e00;

    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0);
    GX_SetBankForSubOBJExtPltt(0);
    *REG_DB_DISPCNT = (*REG_DB_DISPCNT & 0xffcfffef) | 0x10 | 0x200000;
    GXS_SetGraphicsMode(0);

    *REG_DB_BG0CNT = (*REG_DB_BG0CNT & ~3) | 1;
    *REG_DB_BG1CNT = (*REG_DB_BG1CNT & ~3) | 2;
    *REG_DB_BG3CNT = (*REG_DB_BG3CNT & ~3) | 3;
    *REG_DB_DISPCNT = (*REG_DB_DISPCNT & ~0x1f00) | 0x1b00;
    *REG_POWCNT1 |= 0x8000;

    *REG_BG1CNT = (*REG_BG1CNT & 0x43) | 0x410;
    *REG_BG2CNT = (*REG_BG2CNT & 0x43) | 0x208;
    *REG_BG3CNT = (*REG_BG3CNT & 0x43) | 4;
    *REG_DB_BG0CNT = (*REG_DB_BG0CNT & 0x43) | 0x210;
    *REG_DB_BG1CNT = (*REG_DB_BG1CNT & 0x43) | 0x108;
    *REG_DB_BG3CNT = (*REG_DB_BG3CNT & 0x43) | 8;
}
