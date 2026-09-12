/* Ov011_Mode2Teardown -- title tick handler for scene mode 2: reset the layout
 * animator (mode 3, animator table kOv011ModeTwoLayout, count 0x13, index 0),
 * free both pane tilesets and reload them from the archive base (entries 5 and
 * 6, bank 0xe), move the cursor object of manager B to (8.0, 6.0), kick fade
 * entry 0 for 2 frames, put both engines on display mode 1 with BG0/BG3, clear
 * the current pane's flag bit 0 and zero the scene's first word.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* UiLayoutPos */
struct LayoutPos {
    int nX;                      /* 0x00 */
    int nY;                      /* 0x04 */
};

/* Ov011Scene */
struct Scene {
    int nFirst;                  /* 0x00000 */
    int nMode;                   /* 0x00004 */
    u8 pad00008[4];
    u32 nArchiveBase;            /* 0x0000c */
    u8 pad00010[4];
    void *pTilesetA;             /* 0x00014 */
    u8 pad00018[0x1093c];
    void *pTilesetB;             /* 0x10954 */
    u8 pad10958[0x13165];
    u8 nPaneFlags;               /* 0x23abd */
    u8 pad23abe[0xa];
    u16 nAnimIndex;              /* 0x23ac8 */
    u16 nAnimCount;              /* 0x23aca */
    const void *pAnimTable;      /* 0x23acc */
    u8 pad23ad0[0x4a38];
    u8 managerB[0x4a38];         /* 0x28508 */
    int nCursorObject;           /* 0x2cf40 */
};


#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_DISPCNT_SUB (*(volatile u32 *)0x04001000)
#define DISPCNT_BG_MASK 0x1f00
#define DISPCNT_MODE2_BGS 0x1900
#define VRAM_BASE_MASK 0xfffffc
#define VRAM_BASE_ROUND 0x8000
#define ARCHIVE_TILESET_A 0x80000005
#define ARCHIVE_TILESET_B 0x80000006
#define ARCHIVE_BANK 0xe
#define MODE_ANIM 3
#define ANIM_COUNT 0x13
#define PANE_FLAG_ACTIVE 0x1

/* khdays: shared-bss */
int data_ov011_0205e960 = 0;                                                  /* gOv011Cursor */
struct Scene *data_ov011_0205e964 = 0;                                         /* gpOv011Scene */
extern const int data_ov011_0205dd70;                                          /* kOv011ModeTwoLayout */

extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void *func_0201ef9c(u32 nEntry, int nBank);                              /* Archive_LoadFile */
extern void func_0203257c(void *pManager, int nObject, struct LayoutPos *pPos); /* Slot_SetPosition */
extern void func_02033f88(int nEntry, int nFrames);

void func_ov011_0205c190(void)
{
    struct LayoutPos pos;

    data_ov011_0205e964->nMode = MODE_ANIM;
    data_ov011_0205e964->pAnimTable = &data_ov011_0205dd70;
    data_ov011_0205e964->nAnimCount = ANIM_COUNT;
    data_ov011_0205e964->nAnimIndex = 0;
    NNSi_FndFreeFromDefaultHeap(data_ov011_0205e964->pTilesetA);
    NNSi_FndFreeFromDefaultHeap(data_ov011_0205e964->pTilesetB);
    data_ov011_0205e964->pTilesetA =
        func_0201ef9c(((data_ov011_0205e964->nArchiveBase + VRAM_BASE_ROUND & VRAM_BASE_MASK) << 7) | ARCHIVE_TILESET_A, ARCHIVE_BANK);
    data_ov011_0205e964->pTilesetB =
        func_0201ef9c(((data_ov011_0205e964->nArchiveBase + VRAM_BASE_ROUND & VRAM_BASE_MASK) << 7) | ARCHIVE_TILESET_B, ARCHIVE_BANK);
    pos.nX = 0x80000;
    pos.nY = 0x60000;
    func_0203257c(data_ov011_0205e964->managerB, data_ov011_0205e964->nCursorObject, &pos);
    func_02033f88(0, 2);
    REG_DISPCNT = (REG_DISPCNT & ~DISPCNT_BG_MASK) | DISPCNT_MODE2_BGS;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~DISPCNT_BG_MASK) | DISPCNT_MODE2_BGS;
    data_ov011_0205e964->nPaneFlags &= ~PANE_FLAG_ACTIVE;
    data_ov011_0205e964->nFirst = 0;
}
