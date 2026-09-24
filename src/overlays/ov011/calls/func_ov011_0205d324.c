/* Ov011_InitTitleDisplay -- set up both display engines for the title: blank both screens,
 * map the VRAM banks, put both engines in 2D mode 0 with BG1 in 16 colours and BG0/2/3 in 256,
 * show every plane, use 1D 128K OBJ character mapping, order the BGs 3/0/1/2 and put the main
 * engine on the top screen. */
typedef unsigned short u16;
typedef unsigned int   u32;

typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;

#define reg_GX_DISPCNT      (*(REGType32v *)0x04000000)
#define reg_G2_BG0CNT       (*(REGType16v *)0x04000008)
#define reg_G2_BG1CNT       (*(REGType16v *)0x0400000a)
#define reg_G2_BG2CNT       (*(REGType16v *)0x0400000c)
#define reg_G2_BG3CNT       (*(REGType16v *)0x0400000e)
#define reg_GX_POWCNT       (*(REGType16v *)0x04000304)
#define reg_GXS_DB_DISPCNT  (*(REGType32v *)0x04001000)
#define reg_G2S_DB_BG0CNT   (*(REGType16v *)0x04001008)
#define reg_G2S_DB_BG1CNT   (*(REGType16v *)0x0400100a)
#define reg_G2S_DB_BG2CNT   (*(REGType16v *)0x0400100c)
#define reg_G2S_DB_BG3CNT   (*(REGType16v *)0x0400100e)

extern void func_0201e1d0(void);
extern void func_0201e374(int nBrightness);
extern void func_0201e3cc(int nBrightness);
extern void GX_SetBankForBG(int nBank);
extern void GX_SetBankForOBJ(int nBank);
extern void GX_SetBankForBGExtPltt(int nBank);
extern void GX_SetBankForSubBG(int nBank);
extern void GX_SetBankForSubOBJ(int nBank);
extern void GX_SetBankForSubBGExtPltt(int nBank);
extern void func_020056b4(int nDispMode, int nBgMode, int nBg0_2d3d);
extern void GXS_SetGraphicsMode(int nBgMode);

static inline void G2_SetBG0Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2_BG0CNT = (u16)((reg_G2_BG0CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                          | (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2_BG1CNT = (u16)((reg_G2_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                          | (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2_BG2CNT = (u16)((reg_G2_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                          | (screenBase << 8) | (charBase << 2));
}

static inline void G2_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2_BG3CNT = (u16)((reg_G2_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                          | (screenBase << 8) | (charBase << 2));
}

static inline void G2S_SetBG0Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2S_DB_BG0CNT = (u16)((reg_G2S_DB_BG0CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                              | (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2S_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    reg_G2S_DB_BG1CNT = (u16)((reg_G2S_DB_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                              | (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13));
}

static inline void G2S_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2S_DB_BG2CNT = (u16)((reg_G2S_DB_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                              | (screenBase << 8) | (charBase << 2));
}

static inline void G2S_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    reg_G2S_DB_BG3CNT = (u16)((reg_G2S_DB_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7)
                              | (screenBase << 8) | (charBase << 2));
}

static inline void GX_SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~0x1f00) | (plane << 8));
}

static inline void GXS_SetVisiblePlane(int plane)
{
    reg_GXS_DB_DISPCNT = (u32)((reg_GXS_DB_DISPCNT & ~0x1f00) | (plane << 8));
}

static inline void GX_SetOBJVRamModeChar(u32 mode)
{
    reg_GX_DISPCNT = (u32)(reg_GX_DISPCNT & ~(0x300000 | 0x10) | mode);
}

static inline void GXS_SetOBJVRamModeChar(u32 mode)
{
    reg_GXS_DB_DISPCNT = (u32)(reg_GXS_DB_DISPCNT & ~(0x300000 | 0x10) | mode);
}

static inline void G2_SetBG0Priority(int priority) { reg_G2_BG0CNT = (u16)((reg_G2_BG0CNT & ~3) | priority); }
static inline void G2_SetBG1Priority(int priority) { reg_G2_BG1CNT = (u16)((reg_G2_BG1CNT & ~3) | priority); }
static inline void G2_SetBG2Priority(int priority) { reg_G2_BG2CNT = (u16)((reg_G2_BG2CNT & ~3) | priority); }
static inline void G2_SetBG3Priority(int priority) { reg_G2_BG3CNT = (u16)((reg_G2_BG3CNT & ~3) | priority); }
static inline void G2S_SetBG0Priority(int priority) { reg_G2S_DB_BG0CNT = (u16)((reg_G2S_DB_BG0CNT & ~3) | priority); }
static inline void G2S_SetBG1Priority(int priority) { reg_G2S_DB_BG1CNT = (u16)((reg_G2S_DB_BG1CNT & ~3) | priority); }
static inline void G2S_SetBG2Priority(int priority) { reg_G2S_DB_BG2CNT = (u16)((reg_G2S_DB_BG2CNT & ~3) | priority); }
static inline void G2S_SetBG3Priority(int priority) { reg_G2S_DB_BG3CNT = (u16)((reg_G2S_DB_BG3CNT & ~3) | priority); }

void func_ov011_0205d324(void)
{
    func_0201e1d0();
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetBankForBGExtPltt(0x10);
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GX_SetBankForSubBGExtPltt(0x80);

    func_020056b4(1, 0, 0);
    G2_SetBG0Control(0, 1, 0, 0, 0);
    G2_SetBG1Control(0, 0, 1, 1, 0);
    G2_SetBG2ControlText(0, 1, 2, 4);
    G2_SetBG3ControlText(0, 1, 4, 1);
    GX_SetVisiblePlane(0x1f);
    GX_SetOBJVRamModeChar(0x200010);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(0);
    G2_SetBG2Priority(1);
    G2_SetBG3Priority(2);

    GXS_SetGraphicsMode(0);
    G2S_SetBG0Control(0, 1, 0, 0, 0);
    G2S_SetBG1Control(0, 0, 1, 1, 0);
    G2S_SetBG2ControlText(0, 1, 2, 4);
    G2S_SetBG3ControlText(0, 1, 4, 1);
    GXS_SetVisiblePlane(0x1f);
    GXS_SetOBJVRamModeChar(0x200010);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(0);
    G2S_SetBG2Priority(1);
    G2S_SetBG3Priority(2);

    reg_GX_POWCNT |= 0x8000;
}
