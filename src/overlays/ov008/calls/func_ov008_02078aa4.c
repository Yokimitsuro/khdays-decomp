/* func_ov008_02078aa4 -- Ov008_OpenTutorialPage: initialise page B as the
 * tutorial page.  Clears the page, copies the 16-byte cue request into its
 * header, loads the tutorial archive ("UI/btlttr/ttr_&.dat.z", 14 chunks) and
 * hands it to the ov025 list at +0x200 selecting the page's entry from the
 * page-index table; raises bit 2 of the page flags; then programs the sub
 * screen's BG1..BG3 (screen bases 0x18/0x19/0x16 with char base 8 on BG3,
 * priorities 3/2/1), clears the first BG3 character tile and shows only BG1..3
 * on the sub display.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define PAGE_B_SIZE 0x214

typedef struct Ov008CueRequest {
    int aWord[4];
} Ov008CueRequest;

typedef struct Ov008PageB {
    Ov008CueRequest header;   /* 0x000 */
    u8  pad_010[0x28 - 0x10];
    u32 nFlags;               /* 0x028 */
    u8  pad_02c[0x1fc - 0x2c];
    void *pArchive;           /* 0x1fc */
    u8  list[0x214 - 0x200];  /* 0x200: ov025 list */
} Ov008PageB;

typedef struct DisplayRegisters {
    volatile u32 dispcnt;
    u8 pad04[4];
    volatile u16 bg0cnt;
    volatile u16 bg1cnt;
    volatile u16 bg2cnt;
    volatile u16 bg3cnt;
} DisplayRegisters;

static volatile DisplayRegisters *const SUB_DISPLAY = (volatile DisplayRegisters *)0x04001000;

extern char data_ov008_02090b40[];                                  /* "UI/btlttr/ttr_&.dat.z" */
extern const int data_ov008_02090a54[];                             /* page index -> tutorial entry */

extern Ov008PageB *func_ov008_02050cec(void);                        /* Ov008_GetPageB */
extern void MI_CpuFill8(void *pDst, int nValue, u32 nSize);
extern Ov008CueRequest *func_ov008_02051198(void);                  /* Ov008_GetCueRequest */
extern void *func_0201ef9c(const char *pPath, int nChunks);         /* Archive_LoadFile */
extern void func_ov025_020b07ec(void *pList, void *pArchive);
extern void func_ov025_020b0818(void *pList, u32 nEntry);
extern void *G2S_GetBG3CharPtr(void);
extern void MIi_CpuClearFast(u32 nValue, void *pDst, u32 nSize);

void func_ov008_02078aa4(void)
{
    Ov008PageB *pPage = func_ov008_02050cec();

    MI_CpuFill8(pPage, 0, PAGE_B_SIZE);
    pPage->header = *func_ov008_02051198();
    pPage->pArchive = func_0201ef9c(data_ov008_02090b40, 14);
    func_ov025_020b07ec(pPage->list, pPage->pArchive);
    func_ov025_020b0818(pPage->list, (u16)data_ov008_02090a54[pPage->header.aWord[0]]);
    pPage->nFlags |= 4;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & 0x43) | 0x1800;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & 0x43) | 0x1900;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & 0x43) | 0x1608;
    SUB_DISPLAY->bg1cnt = (SUB_DISPLAY->bg1cnt & ~3) | 3;
    SUB_DISPLAY->bg2cnt = (SUB_DISPLAY->bg2cnt & ~3) | 2;
    SUB_DISPLAY->bg3cnt = (SUB_DISPLAY->bg3cnt & ~3) | 1;
    MIi_CpuClearFast(0, G2S_GetBG3CharPtr(), 0x20);
    SUB_DISPLAY->dispcnt = (SUB_DISPLAY->dispcnt & ~0x1f00) | 0xe00;
}
