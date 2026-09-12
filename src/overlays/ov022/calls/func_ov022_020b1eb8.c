/* Ov022_LoadMarkerPanel -- load a marker panel's sprite sets for its kind.
 *
 * The panel is registered as the kind's panel (0 or 1) and stamped with
 * the kind. Kind 0 reads the info archive and lifts its markers 0x1800 up
 * and 0xc000 across; kind 1 reads the state archive of the current language
 * and lifts them 0x400 up. The archive's sprite list (kind 7) gives the
 * sprite count per slot; each of the four slots gets that many sprites,
 * loaded from the list in turn (the very first with the load flag up) and
 * marked 0x3f, with the slot's state cleared. The archive goes back.
 */

typedef unsigned char u8;
typedef unsigned int u32;

#define KIND_INFO 0
#define KIND_STATE 1
#define SLOT_COUNT 4
#define ARCHIVE_HEAP 0xf
#define LIST_SPRITES 7
#define INFO_Y_LIFT 0x1800
#define INFO_X_SHIFT 0xc000
#define STATE_Y_LIFT 0x400
#define SPRITE_MARK 0x3f

/* Ov022MarkerSprite */
struct MarkerSprite {
    u8 pad00[0x24];
    u8 nMark;                    /* 0x24 */
    u8 pad25[0xb];
};

/* Ov022MarkerSlot */
struct MarkerSlot {
    struct MarkerSprite *pSprites;  /* 0x00 one per state */
    u8 bShown;                   /* 0x04 */
    u8 nState;                   /* 0x05 */
    u8 pad06[2];
    int nTimer;                  /* 0x08 */
};

/* Ov022MarkerPanel */
struct MarkerPanel {
    u8 nKind;                    /* 0x00 */
    u8 nCount;                   /* 0x01 sprites per slot */
    u8 pad02[2];
    int nYLift;                  /* 0x04 added to the world y */
    int nXShift;                 /* 0x08 added to the screen x */
    struct MarkerSlot aSlots[SLOT_COUNT];   /* 0x0c one per actor id */
};

extern struct MarkerPanel *data_ov022_020b2ec0[2];   /* the two marker panels by kind */
extern char data_ov022_020b2e24[];          /* "%s" */
extern char data_ov022_020b2e28[];          /* "ba/ef/info.p.z" */
extern char data_ov022_020b2e38[];          /* "ba/ef/st_&.p.z" */

extern void OS_SPrintf(char *pszOut, char *pszFormat, char *pszArg);
extern char *func_02024e6c(char *pszPath);                                      /* Msg_BuildLangPath */
extern void *SND_RegisterSeq(char *pszPath, int nHeap);                         /* archive load */
extern void func_0201f390(int bPhase);                                          /* InstallHandlerPairByFlag */
extern void *func_0201f634(void *pArchive, int nArg);
extern int func_020255bc(void *pList, int nKind);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 nSize);
extern void *func_020255d4(void *pList, int nKind, int nIndex);                 /* Archive_GetMember */
extern void func_ov002_02050d28(struct MarkerSprite *pSprite, void *pResource, int bFirst);
extern void func_0201f5ac(void *pArchive);

void func_ov022_020b1eb8(struct MarkerPanel *pPanel, int nKind)
{
    char szPath[0x80];
    void *pList;
    void *pArchive;
    int nSlot;
    int i;
    int bFirst;
    struct MarkerSprite *pSprites;

    switch (nKind) {
    case KIND_INFO:
        data_ov022_020b2ec0[0] = pPanel;
        break;
    case KIND_STATE:
        data_ov022_020b2ec0[1] = pPanel;
        break;
    }
    pPanel->nKind = nKind;
    bFirst = 1;
    switch (nKind) {
    case KIND_INFO:
        OS_SPrintf(szPath, data_ov022_020b2e24, data_ov022_020b2e28);
        pPanel->nYLift = INFO_Y_LIFT;
        pPanel->nXShift = INFO_X_SHIFT;
        break;
    case KIND_STATE:
        OS_SPrintf(szPath, data_ov022_020b2e24, func_02024e6c(data_ov022_020b2e38));
        pPanel->nYLift = STATE_Y_LIFT;
        pPanel->nXShift = 0;
        break;
    }
    pArchive = SND_RegisterSeq(szPath, ARCHIVE_HEAP);
    func_0201f390(0);
    pList = func_0201f634(pArchive, 1);
    func_0201f390(1);
    pPanel->nCount = func_020255bc(pList, LIST_SPRITES);
    for (nSlot = 0; nSlot < SLOT_COUNT; nSlot++) {
        pPanel->aSlots[nSlot].pSprites = NNSi_FndAllocFromDefaultExpHeap(pPanel->nCount * sizeof(struct MarkerSprite));
        pPanel->aSlots[nSlot].nState = 0;
        for (i = 0; i < pPanel->nCount; i++) {
            pSprites = pPanel->aSlots[nSlot].pSprites;
            func_ov002_02050d28(&pSprites[i], func_020255d4(pList, LIST_SPRITES, i), bFirst);
            pSprites[i].nMark = SPRITE_MARK;
            bFirst = 0;
        }
    }
    func_0201f5ac(pArchive);
}
