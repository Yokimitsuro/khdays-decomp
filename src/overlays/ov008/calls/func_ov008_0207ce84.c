/* func_ov008_0207ce84 -- Ov008_LobbyStep: one frame of the mission
 * lobby's member panel.  The four member rows are read (0207b960), the
 * local player's (0207b138) cursor resolved from its icon (0207bda4) and,
 * while the session is joined (02081694) by a guest (0207be38 == 0) in
 * state 5 (020816c0) with input allowed (0207ba08), the cursor moves
 * (0207d888 on a saved copy of the row, id + 1 when it moved, 0207ba68).
 * A guest then commits its icon (0207b908) when its row is set and either
 * the lobby is locked (+0x28) or no two set rows share an icon; the host
 * commits the local index's icon on button 1.  The panel updates
 * (020818a0, 020819a8 with the icon, 02081b74, 0208187c with 0207b7b4) and
 * in state 5 the icon list (0207bcdc: 0x13 without a cursor) refreshes when
 * the lobby is unlocked (+0x24) or the icon changed against the stored row
 * (+0x40 + 8 * i).  Each set row shows its slot (02081708, 020818e0) with
 * sounds for an icon change of the local row and for a flag change
 * (0x2e / 0x2f); a lobby result of 3 (0207b8f0) requests state 7 and returns
 * the next step 0207d5cc.  In states 4 .. 6 the text layers are rebuilt
 * (02081da0 .. 02081e08): the title (0x36 host / 0x33 guest), the cursor
 * text (0x1e or icon + 0xb), the icon name (+ 0x1f), the four column and
 * three row captions of 0208fc8c, each set (or local) row's icon text at
 * (0x44 / 0xc4, 0x9a / 0xb0) and the footer (0x3b / 0x38).  The rows are
 * stored back to +0x40.  Codegen: the next step, the host flag and the
 * cursor (address taken) are spilled; loop counters are u8; the saved row
 * is a halfword struct copy; the caption tables are two struct copies
 * (columns first); the pair scan is two nested for loops with a flag;
 * hoisted constants (0, 0x2e, 1, 0x87, 0xe4, 0x44, 0x9a, 2) sit in
 * callee-saved registers.  The 020818e0 prototype takes the icon as u16
 * (the ov006 twin's form): mwcc emits no narrowing for it, but the halfword
 * parameter is what schedules the slot copy after the row loads.
 */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define MEMBER_COUNT   4
#define STATE_LOBBY    5
#define ICON_NONE      0x13
#define TEXT_CURSOR_NONE 0x1e
#define TEXT_ICON_BASE 0xb
#define TEXT_NAME_BASE 0x1f
#define SOUND_FLAG_ON  0x2e
#define SOUND_FLAG_OFF 0x2f

typedef void (*Ov008LobbyStep)(void);

typedef struct MissionMenuRow {
    u16 id;
    u8  flags2;
    u8  flags3;
    s8  icon;
    s8  sprite;
    u8  field6;
    u8  pad7;
} MissionMenuRow;

typedef struct Ov008LobbyColumnTexts {
    u8 aText[4];
} Ov008LobbyColumnTexts;

typedef struct Ov008LobbyRowTexts {
    u8 aText[3];
} Ov008LobbyRowTexts;

typedef struct Ov008LobbyCaptions {
    Ov008LobbyRowTexts row;    /* 0x00 */
    u8 pad_03[3];
    Ov008LobbyColumnTexts col; /* 0x06 */
} Ov008LobbyCaptions;

typedef struct MissionMenuContext {
    void *sceneObject;        /* 0x00 */
    u16  inputHeader[13];     /* 0x04 */
    u8   pad_1e[6];
    int  bUnlocked;           /* 0x24 */
    int  bLocked;             /* 0x28 */
    u8   pad_2c[0x40 - 0x2c];
    MissionMenuRow aPlayer[MEMBER_COUNT]; /* 0x40 */
    u8   records[0xc];        /* 0x60 */
} MissionMenuContext;

extern MissionMenuContext *data_ov008_02090fa0;
extern u16 data_0204c190;
extern const Ov008LobbyCaptions data_ov008_0208fc8c;
extern void  func_ov008_0207d5cc(void);                                  /* next lobby step */
extern u16   func_ov008_0207b138(void);                                  /* local member index */
extern int   func_ov008_0207b7e4(void);
extern void  FS_UnloadOverlayImage_0x020362ec(u16 *pHeader);
extern void  func_ov008_0207b960(int nRow, MissionMenuRow *pOut);
extern int   func_ov008_0207be38(void);                                  /* is host */
extern int   func_ov008_0207bda4(int nIcon);                             /* cursor of an icon */
extern int   func_ov008_02081694(void);                                  /* session joined */
extern int   func_ov008_020816c0(void);                                  /* lobby state */
extern int   func_ov008_0207ba08(void);                                  /* input allowed */
extern int   func_ov008_0207d888(MissionMenuRow *aRows, int *pnCursor);  /* move the cursor */
extern void  func_ov008_0207ba68(MissionMenuRow *pRow);
extern void  func_ov008_0207b908(int nIcon);                             /* commit the icon */
extern u32   func_02030788(void);                                        /* Session_GetLocalPlayerIndex */
extern void  func_ov008_020818a0(int nValue);                            /* Ov008_Fn_18a0 */
extern void  func_ov008_020819a8(int nIcon);
extern void  func_ov008_02081b74(int bOn);
extern int   func_ov008_0207b7b4(void);
extern void  func_ov008_0208187c(int nSelection);
extern void  func_ov008_0207bcdc(int nIcon);                             /* refresh the icon list */
extern void  func_ov008_02081708(int nSlot, int bSet);
extern void  func_ov008_020818e0(int nSlot, u16 nIcon, int bVisible);
extern void  func_02033b78(int nBank, int nSound);                       /* PlaySound */
extern int   func_ov008_0207b8f0(void);                                  /* lobby result */
extern void  func_ov008_020817c4(int nState, int bAnimate, int nValue);  /* Ov008_RequestMenuState */
extern void  func_ov008_02081da0(void);                                  /* Ov008_ResetTextLayers */
extern void *func_ov008_02055c84(void *pRecords, int nIndex);            /* GetVarRecordByIndex */
extern void  func_ov008_02081ddc(void *pText, int nX, int nY, int nA, int nB, int nC, int nD); /* Ov008_ForwardSevenArgs */
extern void  func_ov008_02081e08(void);                                  /* Ov008_FlushTextLayers */

Ov008LobbyStep func_ov008_0207ce84(void)
{
    MissionMenuRow aRow[MEMBER_COUNT];
    int nCursor;
    MissionMenuRow saved;
    MissionMenuRow rowLocal;
    Ov008LobbyColumnTexts col;
    Ov008LobbyRowTexts row;
    MissionMenuRow rowB;
    MissionMenuRow rowA;
    Ov008LobbyStep pfnNext;
    int bHost;
    u16 nLocal;
    int nSession;
    u8 i;
    u8 a;
    u8 b;
    u8 nSlot;
    int bReady;
    void *pText;
    int nX;
    int nY;
    int nState;
    int nIcon;
    s8 nIcon8;

    pfnNext = 0;
    nLocal = func_ov008_0207b138();
    nSession = func_ov008_0207b7e4();
    nCursor = 0;
    FS_UnloadOverlayImage_0x020362ec(data_ov008_02090fa0->inputHeader);
    for (i = 0; i < MEMBER_COUNT; i++) {
        func_ov008_0207b960(i, &aRow[i]);
    }
    bHost = func_ov008_0207be38();
    nCursor = func_ov008_0207bda4(aRow[nLocal].icon);
    if (func_ov008_02081694() != 0 && bHost == 0 && func_ov008_020816c0() == STATE_LOBBY && func_ov008_0207ba08()) {
        saved = aRow[nLocal];
        if (func_ov008_0207d888(aRow, &nCursor) != 0) {
            aRow[nLocal].id++;
        }
        func_ov008_0207ba68(&aRow[nLocal]);
        aRow[nLocal] = saved;
    }
    if (func_ov008_02081694() != 0) {
        if (bHost == 0) {
            func_ov008_0207b960(nLocal, &rowLocal);
            if (rowLocal.flags2 != 0 && rowLocal.flags3 != 0) {
                if (data_ov008_02090fa0->bLocked != 0) {
                    bReady = 1;
                } else {
                    for (a = 0; a < MEMBER_COUNT; a++) {
                        for (b = a + 1; b < MEMBER_COUNT; b++) {
                            func_ov008_0207b960(a, &rowA);
                            func_ov008_0207b960(b, &rowB);
                            if (rowA.flags2 != 0 && rowB.flags2 != 0 && rowA.icon == rowB.icon) {
                                bReady = 0;
                                goto checked;
                            }
                        }
                    }
                    bReady = 1;
                }
checked:
                if (bReady) {
                    func_ov008_0207b908(aRow[nLocal].icon);
                }
            }
        } else {
            nLocal = func_02030788();
            if (data_0204c190 & 1) {
                func_ov008_0207b908(aRow[nLocal].icon);
            }
        }
    }
    func_ov008_020818a0(nSession);
    func_ov008_020819a8(aRow[nLocal].icon);
    func_ov008_02081b74(0);
    func_ov008_0208187c(func_ov008_0207b7b4());
    if (func_ov008_020816c0() == STATE_LOBBY && (data_ov008_02090fa0->bUnlocked == 0 || aRow[nLocal].icon != data_ov008_02090fa0->aPlayer[nLocal].icon)) {
        func_ov008_0207bcdc(nCursor != 0 ? aRow[nLocal].icon : ICON_NONE);
    }
    nSlot = 0;
    for (i = 0; i < MEMBER_COUNT; i++) {
        func_ov008_02081708(nSlot, aRow[i].flags2);
        func_ov008_020818e0(nSlot, aRow[i].icon, aRow[i].flags3);
        if (aRow[i].flags2 != 0) {
            if (i == nLocal && (u8)aRow[i].icon != (u8)data_ov008_02090fa0->aPlayer[i].icon) {
                func_02033b78(0, 0);
            }
            if (aRow[i].flags3 != data_ov008_02090fa0->aPlayer[i].flags3) {
                if (aRow[i].flags3 != 0) {
                    func_02033b78(0, SOUND_FLAG_ON);
                } else {
                    func_02033b78(0, SOUND_FLAG_OFF);
                }
            }
        }
        if (aRow[i].flags2 != 0) {
            nSlot++;
        }
    }
    if (func_ov008_0207b8f0() == 3) {
        func_ov008_020817c4(7, 1, 0);
        pfnNext = func_ov008_0207d5cc;
    }
    nState = func_ov008_020816c0();
    if (!(nState != 4 && nState != 5 && nState != 6)) {
        col = data_ov008_0208fc8c.col;
        row = data_ov008_0208fc8c.row;
        func_ov008_02081da0();
        func_ov008_02081ddc(func_ov008_02055c84(data_ov008_02090fa0->records, bHost != 0 ? 0x36 : 0x33), 0xfa, 2, 1, 1, 1, 1);
        if (nCursor != 0) {
            pText = func_ov008_02055c84(data_ov008_02090fa0->records, aRow[func_ov008_0207b138()].icon + TEXT_ICON_BASE);
        } else {
            pText = func_ov008_02055c84(data_ov008_02090fa0->records, TEXT_CURSOR_NONE);
        }
        func_ov008_02081ddc(pText, 0x26, 0x1c, 1, 1, 2, 1);
        func_ov008_02081ddc(func_ov008_02055c84(data_ov008_02090fa0->records, aRow[func_ov008_0207b138()].icon + TEXT_NAME_BASE), 0x80, 0x1c, 1, 1, 2, 1);
        for (i = 0; i < 4; i++) {
            func_ov008_02081ddc(func_ov008_02055c84(data_ov008_02090fa0->records, col.aText[i]), 0x87, i * 0x10 + 0x38, 1, 1, 1, 1);
        }
        for (i = 0; i < 3; i++) {
            func_ov008_02081ddc(func_ov008_02055c84(data_ov008_02090fa0->records, row.aText[i]), 0xe4, i * 0x10 + 0x38, 1, 1, 1, 1);
        }
        for (i = 0; i < MEMBER_COUNT; i++) {
            switch (i) {
            case 0:
                nX = 0x44;
                nY = 0x9a;
                break;
            case 1:
                nX = 0xc4;
                nY = 0x9a;
                break;
            case 2:
                nX = 0x44;
                nY = 0xb0;
                break;
            case 3:
                nX = 0xc4;
                nY = 0xb0;
                break;
            default:
                nX = 0;
                nY = 0;
                break;
            }
            if (aRow[i].flags2 != 0 || i == func_ov008_0207b138()) {
                if (func_ov008_0207bda4(aRow[i].icon) != 0) {
                    pText = func_ov008_02055c84(data_ov008_02090fa0->records, aRow[i].icon + TEXT_ICON_BASE);
                } else {
                    pText = func_ov008_02055c84(data_ov008_02090fa0->records, TEXT_CURSOR_NONE);
                }
                func_ov008_02081ddc(pText, nX, nY, 1, 1, 2, 1);
            }
        }
        func_ov008_02081ddc(func_ov008_02055c84(data_ov008_02090fa0->records, bHost != 0 ? 0x3b : 0x38), 10, 0xb4, 1, 1, 0, 0);
        func_ov008_02081e08();
    }
    for (i = 0; i < MEMBER_COUNT; i++) {
        data_ov008_02090fa0->aPlayer[i] = aRow[i];
    }
    return pfnNext;
}
