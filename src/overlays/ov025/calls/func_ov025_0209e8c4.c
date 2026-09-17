/* func_ov025_0209e8c4 -- Ov025_Reports_InitPage: reset the reports / enemy profiles page (the first 0x278 bytes
 * of page A) and remember which set it shows: the mission-mode set (context word 02085078,
 * kept at +0x258) reads the eight 16-bit "seen" words of game field 0x3c6a, the story set those
 * of field 0x45b (GameState_GetField, 16 bits each, 0x10 apart) into +0x248; the page starts in
 * state 1 (+0xc8). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

typedef struct Ov025ReportsPage {
    u8   pad_000[0x6c];
    u8   text[0xc];           /* 0x06c: the report / enemy strings */
    u8   surface[0x3c];       /* 0x078 */
    u8   pad_0b4[0xc8 - 0xb4];
    int  nState;              /* 0x0c8 */
    u8   pad_0cc[0x248 - 0xcc];
    u16  aSeen[8];            /* 0x248: the seen bits per group */
    int  bMissionMode;        /* 0x258: enemy profiles rather than reports */
    u8   pad_25c[0x278 - 0x25c];
} Ov025ReportsPage;           /* 0x278: a view of page A (Ov008_GetPageA) */

extern Ov025ReportsPage *func_ov025_02084afc(void);                /* Ov008_GetPageA */
extern void  MI_CpuFill8(void *pDst, u8 nValue, u32 nSize);
extern int   func_ov025_02085078(void);                             /* Ov008_GetCtxField9768 */
extern u32   func_020235d0(int nField, int nBits);                  /* GameState_GetField */

void func_ov025_0209e8c4(void)
{
    Ov025ReportsPage *pPage;
    int i;
    u16 *pSeen;
    int nGroups;
    int nField;
    int bMissionMode;

    pPage = func_ov025_02084afc();
    pSeen = pPage->aSeen;
    MI_CpuFill8(pPage, 0, 0x278);
    bMissionMode = func_ov025_02085078();
    if (bMissionMode == 0) {
        nField = 0x45b;
        nGroups = 8;
    } else {
        nField = 0x3c6a;
        nGroups = 8;
    }
    pPage->bMissionMode = bMissionMode;
    for (i = 0; i < nGroups; i++) {
        *pSeen = func_020235d0(nField, 0x10);
        pSeen++;
        nField += 0x10;
    }
    pPage->nState = 1;
}
