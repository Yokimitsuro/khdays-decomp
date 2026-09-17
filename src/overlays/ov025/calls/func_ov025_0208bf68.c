/* func_ov025_0208bf68 -- Ov025_Hub_OnEntryHover: the hover callback of the records hub's menu
 * entries.  Only for the stylus / direction mask (bits 4-7 of nKeys): the cursor entry 0x15 of
 * the 4a7c block (02084a7c) moves to the hovered entry's position (Ov008_GetEntryPos 020884c8),
 * three tiles left of it for entries 7 / 8, else at its own x (Ov008_SetEntryPos 02088500); a
 * change of hovered entry id (+0xc, kept at +0x88 of the hub) plays the cursor sound (02033b78)
 * and the entry's help string (ids 1..6 and 9..13 map to strings 9, 10, 12, 15, 11, 16 and
 * 17..19, 13, 14; 02089894) is drawn on the body surface (+0x4c; cleared 02030158, drawn at
 * (0x56, 0) in colour 2 with a shadow 02030278, uploaded 020300f8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

typedef struct Ov008MenuEntry {
    u8   pad_00[0xc];
    int  nId;                 /* 0x0c */
} Ov008MenuEntry;

typedef struct Ov025HubScene {
    int  nField00;            /* 0x00 */
    u8   strings[0xc];        /* 0x04: the hub string set */
    u8   surfaceTitle[0x3c];  /* 0x10: the title surface */
    u8   surfaceBody[0x28];   /* 0x4c: the second surface */
    int  bTextReady;          /* 0x74 */
    u8   pad_78[0x10];
    int  nHoverId;            /* 0x88: the hovered entry id, -1 for none */
} Ov025HubScene;

extern Ov025HubScene *func_ov025_02084afc(void);                    /* Ov008_GetPageA */
extern int   func_ov025_02084a7c(void);                             /* Ov008_GetCtxBlock4a7c */
extern Ov008MenuEntry *func_ov025_0208843c(int nCtx, int nId);      /* FindEntryById */
extern UiLayoutPos *func_ov025_020884c8(int nCtx, Ov008MenuEntry *pEntry); /* Ov008_GetEntryPos */
extern void  func_ov025_02088500(int nCtx, Ov008MenuEntry *pEntry, UiLayoutPos *pPos); /* Ov008_SetEntryPos */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */
extern const u16 *func_ov025_02089894(void *pStrings, int nIndex);  /* Ov025_GetString */
extern void  func_02030158(void *pSurface);                         /* TileSurface_Clear */
extern void  func_02030278(void *pSurface, int nX, int nY, int nColour, const u16 *pText, int nShadow); /* Text_DrawWithShadow */
extern void  func_020300f8(void *pSurface);                         /* TileSurface_Upload */

void func_ov025_0208bf68(Ov008MenuEntry *pEntry, u32 nKeys)
{
    int nCtx;
    Ov008MenuEntry *pCursor;
    Ov025HubScene *pScene;
    UiLayoutPos *pCursorPos;
    UiLayoutPos *pEntryPos;
    UiLayoutPos pos;
    int nString;
    const u16 *pText;

    pScene = func_ov025_02084afc();
    if ((nKeys & 0xf0) == 0) {
        return;
    }
    nCtx = func_ov025_02084a7c();
    pCursor = func_ov025_0208843c(nCtx, 0x15);
    pCursorPos = func_ov025_020884c8(nCtx, pCursor);
    pEntryPos = func_ov025_020884c8(nCtx, pEntry);
    pos.y = pEntryPos->y;
    if ((u32)(pEntry->nId - 7) <= 1) {
        pos.x = pEntryPos->x - 0x30000;
    } else {
        pos.x = pCursorPos->x;
    }
    func_ov025_02088500(nCtx, pCursor, &pos);
    if (pScene->nHoverId != -1 && pScene->nHoverId != pEntry->nId) {
        func_02033b78(0, 0);
    }
    pScene->nHoverId = pEntry->nId;
    switch (pEntry->nId) {
    case 2:
        nString = 10;
        break;
    case 1:
        nString = 9;
        break;
    case 3:
        nString = 12;
        break;
    case 4:
        nString = 15;
        break;
    case 5:
        nString = 11;
        break;
    case 6:
        nString = 16;
        break;
    case 9:
        nString = 17;
        break;
    case 10:
        nString = 18;
        break;
    case 11:
        nString = 19;
        break;
    case 12:
        nString = 13;
        break;
    case 13:
        nString = 14;
        break;
    default:
        nString = -1;
        break;
    }
    if (nString < 0) {
        return;
    }
    pText = func_ov025_02089894(pScene->strings, nString);
    func_02030158(pScene->surfaceBody);
    func_02030278(pScene->surfaceBody, 0x56, 0, 2, pText, 1);
    func_020300f8(pScene->surfaceBody);
}
