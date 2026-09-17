/* func_ov025_020a4cd0 -- Ov025_StatusPanel_SetWeapon: keep weapon nWeapon of the current
 * character (Ov025_GetCharacterSlot 020a0f30) on the status view of page B (Ov025_GetPageB
 * 02084b14) while the panel is active (data_ov025_020b575c).  The weapon table row is packed
 * by ov002 020522c8 (slot 0x13 / index 0 for no weapon, nWeapon < 0) and its halfwords +2 (or
 * +0xe with bAlt), +4, +6, the word +8 and the halfword +0xc are copied to +0x1e0.. / +0x1dc of
 * the page, the weapon index to +0x1d8. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov008MissionList {
    int  nSelected;           /* 0x000 */
    int  nPrevSelected;       /* 0x004 */
    int  nCursorRow;          /* 0x008 */
    int  nScroll;             /* 0x00c: in pixels, 32 a row */
    u8   pad_010[0x54 - 0x10];
    u8   nCursorSlot;         /* 0x054: the accepted slot the cursor is on */
} Ov008MissionList;

typedef struct UiLayoutPos {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
} UiLayoutPos;

typedef struct Ov002WeaponRow {
    u8   nField00;            /* 0x00 */
    u8   nField01;            /* 0x01 */
    s16  nField02;            /* 0x02 */
    s16  nField04;            /* 0x04 */
    s16  nField06;            /* 0x06 */
    int  nField08;            /* 0x08 */
    s16  nField0c;            /* 0x0c */
    s16  nField0e;            /* 0x0e: the alternate of +2 */
    u8   pad_10[0x20 - 0x10];
} Ov002WeaponRow;             /* 0x20: the packed weapon table row (ov002 02052308) */

typedef struct Ov025StatusPage {
    u8   pad_000[0x1d8];
    int  nWeapon;             /* 0x1d8 */
    int  nWeaponField08;      /* 0x1dc */
    s16  nWeaponField02;      /* 0x1e0 */
    s16  nWeaponField04;      /* 0x1e2 */
    s16  nWeaponField06;      /* 0x1e4 */
    s16  nWeaponField0c;      /* 0x1e6 */
} Ov025StatusPage;

extern Ov025StatusPage *func_ov025_02084b14(void);                  /* Ov025_GetPageB */
extern int   func_ov025_020a0f30(void);                             /* Ov025_GetCharacterSlot */
extern void  func_ov002_020522c8(Ov002WeaponRow *pRow, int nSlot, int nWeapon); /* Ov002_LoadWeaponRow */
extern int   data_ov025_020b575c;                                   /* the status panel is active */

void func_ov025_020a4cd0(int nWeapon, int bAlt)
{
    Ov025StatusPage *pPage;
    Ov002WeaponRow row;

    pPage = func_ov025_02084b14();
    if (data_ov025_020b575c == 0) {
        return;
    }
    if (nWeapon >= 0) {
        func_ov002_020522c8(&row, func_ov025_020a0f30(), nWeapon);
    } else {
        func_ov002_020522c8(&row, 0x13, 0);
    }
    pPage->nWeapon = nWeapon;
    pPage->nWeaponField02 = bAlt != 0 ? row.nField0e : row.nField02;
    pPage->nWeaponField04 = row.nField04;
    pPage->nWeaponField06 = row.nField06;
    pPage->nWeaponField08 = row.nField08;
    pPage->nWeaponField0c = row.nField0c;
}
