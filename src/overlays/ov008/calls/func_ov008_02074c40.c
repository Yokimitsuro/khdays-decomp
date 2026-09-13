/* func_ov008_02074c40 -- Ov008_DrawMissionInfoLines: draw the mission
 * info panel's text lines (+0xc, mode 6, bound to +0x13c) for the listed
 * entry -- the name node's description (+0x44) replaces the entry's when a
 * node is given -- and store the total text height in +0x148.  During a
 * page transition (02051028) without a transfer (+0x150): caption 5, then,
 * when set, the duration (+0x20: caption 7 + minutes (text 8) from 60 up +
 * remainder seconds (text 9) + text 10), the enemy count (+0x22: caption 7
 * + text 0xb), flags 1 / 2 / 4 of +0x24 (texts 0xc / 0xd / 0xe), the bytes
 * +0x26 / +0x27 / +0x28 (texts 0xf / 0x10 / 0x11) and the words +0x2a /
 * +0x2c (0x12 / 0x13), a blank line (0209092c), and -- without a transfer --
 * caption 6, the reward kind's line (+0x2e: caption 7 + text 0x15 .. 0x1e
 * with the value 1) and the record line (text 0x1f: the mission result
 * record of 0204be18 split by 02074258 into the time format 02090930 for
 * kind 0, the plain format 02090954 otherwise, or 02090960 when the stage
 * field is negative or no record exists) in colour 0xfd, another blank
 * line, and finally the description.  Lines are drawn through 020302ec at
 * x 3 (6 for the record) in colour 0xf5 / 0xfb, 16 rows apart, each
 * measured (02074b10) into the height.  Codegen: a static inline plain-line
 * helper and a caption-7 macro on one function-scope pTail (r7) inline into
 * the straight-line ROM; the entry pointer is volatile because the ROM
 * reloads every entry field after each call (a plain pointer keeps them in
 * a register across the calls), so the mission id is read once into a
 * local; the height / y initialisers precede the description select so the
 * join stops the compiler from reusing their registers for the constant
 * arguments 0 and 3; the duration divisions are magic multiplies; y starts
 * at 3 and steps by 0x10, the reward line advancing it before the record
 * line and the blank line drawn at y + 0x10; the record switch lists cases
 * 1 .. 8 with the default on the plain format inside the `stage >= 0 &&
 * record != -1` branch.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define MODE_INFO       6
#define COLOUR_TEXT     0xf5
#define SHADE_TEXT      0xfb
#define COLOUR_RECORD   0xfd
#define LINE_STEP       0x10
#define TEXT_CAPTION_A  5
#define TEXT_CAPTION_B  6
#define TEXT_PREFIX     7
#define TEXT_MINUTES    8
#define TEXT_SECONDS    9
#define TEXT_DURATION_END 10
#define TEXT_ENEMIES    0xb
#define TEXT_REWARD_FIRST 0x15
#define TEXT_RECORD     0x1f
#define FIELD_MISSION_STAGE 0x2a4c

typedef struct Ov008MissionListEntry {
    u8    pad_00[2];
    u16   missionId;          /* 0x02 */
    u8    pad_04[0x20 - 4];
    u16   nDuration;          /* 0x20 */
    u16   nEnemies;           /* 0x22 */
    u16   nInfoFlags;             /* 0x24 */
    u8    nStatA;             /* 0x26 */
    u8    nStatB;             /* 0x27 */
    u8    nStatC;             /* 0x28 */
    u8    pad_29;
    u16   nStatD;             /* 0x2a */
    u16   nStatE;             /* 0x2c */
    u16   nRewardKind;        /* 0x2e */
    u8    pad_30[0x44 - 0x30];
    u16  *pDesc;              /* 0x44 */
} Ov008MissionListEntry;

typedef struct Ov008MissionNameNode {
    u8    pad_00[0x44];
    u16  *pDesc;              /* 0x44: description text */
} Ov008MissionNameNode;

typedef struct Ov008MissionMenu {
    u8  pad_000[0xc];
    u8  surface[0x34 - 0xc];  /* 0x00c */
    int nMode;                /* 0x034 */
    u8  pad_038[0x13c - 0x38];
    int nLinesTarget;         /* 0x13c */
    u8  pad_140[8];
    int nTextHeight;          /* 0x148 */
    u8  pad_14c[4];
    int bTransfer;            /* 0x150 */
    u8  pad_154[0x530 - 0x154];
    u8  records[0xc];         /* 0x530: variable text records */
} Ov008MissionMenu;

typedef struct GameState {
    u8  pad_0000[0x198c];
    int missionResultRecords[200]; /* 0x198c */
} GameState;

extern GameState *data_0204be18;                                       /* g_pTallySource */
extern const u16 data_ov008_0209092c[];                                /* blank line */
extern const u16 data_ov008_02090930[];                                /* record time format */
extern const u16 data_ov008_02090954[];                                /* record plain format */
extern const u16 data_ov008_02090960[];                                /* no record format */
extern void  func_02030094(void *pSurface, int nTarget, int nUpdate);   /* TileSurface_SetCurrentItem */
extern void  func_02030158(void *pSurface);                            /* Obj_InvokeInnerVtable4 */
extern int   func_ov008_02051028(void);                                /* Ov008_GetCtxObject9634: page transition */
extern u16  *func_ov008_02055c84(void *pRecords, int nIndex);          /* GetVarRecordByIndex */
extern void  func_020302ec(void *pSurface, int nX, int nY, int nColour, int nShade, const u16 *pText); /* Obj_ForwardToSub1c */
extern int   func_ov008_02074b10(const u16 *pText);                    /* text height */
extern void  func_020200e4(u16 *pDst, const u16 *pSrc);                /* StrCopy16 */
extern int   func_020200c8(const u16 *pStr);                           /* Wcslen */
extern void  func_020262a0(u16 *pDst, int nCap, const u16 *pFormat, ...); /* Text_FormatUtf16 */
extern u32   func_020235d0(int nField, int nBits);                     /* GameState_GetField */
extern void  func_ov008_02074258(int nRecord, u8 *pMinutes, u8 *pSeconds, u8 *pFrames); /* split a time record */

static inline int Ov008_DrawInfoLine(Ov008MissionMenu *pMenu, int nY, const u16 *pText)
{
    func_020302ec(pMenu->surface, 3, nY, COLOUR_TEXT, SHADE_TEXT, pText);
    return func_ov008_02074b10(pText);
}

/* start a caption-7 line in pBuffer and leave pTail after it (the ROM keeps
 * the running pointer in one register variable for every line) */
#define Ov008_BeginPrefixedLine(pBuffer)                                        pTail = pBuffer;                                                            func_020200e4(pTail, func_ov008_02055c84(pMenu->records, TEXT_PREFIX));     pTail += func_020200c8(pTail)

void func_ov008_02074c40(Ov008MissionMenu *pMenu, volatile Ov008MissionListEntry *pEntry /* khdays: reloaded after every call */, Ov008MissionNameNode *pNode)
{
    u16 aLine[0x80];
    u16 aRecord[0x80];
    u8 nMinutes;
    u8 nSeconds;
    u8 nFrames;
    int nHeight;
    u16 *pDesc;
    int nY;
    u16 *pTail;
    u16 *pLabel;
    int nRecord;
    int nMissionId;

    nHeight = 0;
    nY = 3;
    pDesc = pEntry->pDesc;
    if (pNode != 0) {
        pDesc = pNode->pDesc;
    }
    func_02030094(pMenu->surface, pMenu->nLinesTarget, 0);
    pMenu->nMode = MODE_INFO;
    func_02030158(pMenu->surface);
    if (func_ov008_02051028() != 0) {
        if (pMenu->bTransfer == 0) {
            nHeight += Ov008_DrawInfoLine(pMenu, nY, func_ov008_02055c84(pMenu->records, TEXT_CAPTION_A));
            nY += LINE_STEP;
            if (pEntry->nDuration != 0) {
                Ov008_BeginPrefixedLine(aLine);
                if (pEntry->nDuration >= 60) {
                    func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_MINUTES), pEntry->nDuration / 60);
                    pTail += func_020200c8(pTail);
                }
                if (pEntry->nDuration % 60 != 0) {
                    func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_SECONDS), pEntry->nDuration % 60);
                    pTail += func_020200c8(pTail);
                }
                func_020200e4(pTail, func_ov008_02055c84(pMenu->records, TEXT_DURATION_END));
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nEnemies != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_ENEMIES), pEntry->nEnemies);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nInfoFlags & 1) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0xc), pEntry->nInfoFlags & 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nInfoFlags & 2) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0xd), pEntry->nInfoFlags & 2);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nInfoFlags & 4) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0xe), pEntry->nInfoFlags & 4);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nStatA != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0xf), pEntry->nStatA);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nStatB != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0x10), pEntry->nStatB);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nStatC != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0x11), pEntry->nStatC);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nStatD != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0x12), pEntry->nStatD);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            if (pEntry->nStatE != 0) {
                Ov008_BeginPrefixedLine(aLine);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, 0x13), pEntry->nStatE);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aLine);
                nY += LINE_STEP;
            }
            nHeight += Ov008_DrawInfoLine(pMenu, nY, data_ov008_0209092c);
            nY += LINE_STEP;
        }
        if (pMenu->bTransfer == 0) {
            nHeight += Ov008_DrawInfoLine(pMenu, nY, func_ov008_02055c84(pMenu->records, TEXT_CAPTION_B));
            nY += LINE_STEP;
            switch (pEntry->nRewardKind) {
            case 0:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 1:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 1), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 2:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 2), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 3:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 3), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 4:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 4), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 5:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 6), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 6:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 7), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 7:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 8), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            case 8:
                Ov008_BeginPrefixedLine(aRecord);
                func_020262a0(pTail, 0x100, func_ov008_02055c84(pMenu->records, TEXT_REWARD_FIRST + 9), 1);
                nHeight += Ov008_DrawInfoLine(pMenu, nY, aRecord);
                nY += LINE_STEP;
                break;
            }
            pLabel = func_ov008_02055c84(pMenu->records, TEXT_RECORD);
            nMissionId = pEntry->missionId;
            nRecord = data_0204be18->missionResultRecords[nMissionId];
            if ((int)func_020235d0(nMissionId * 3 + FIELD_MISSION_STAGE, 3) >= 0 && nRecord != -1) {
                switch (pEntry->nRewardKind) {
                case 0:
                    func_ov008_02074258(nRecord, &nMinutes, &nSeconds, &nFrames);
                    func_020262a0(aRecord, 0x100, data_ov008_02090930, pLabel, nMinutes, nSeconds, nFrames);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                default:
                    func_020262a0(aRecord, 0x100, data_ov008_02090954, pLabel, nRecord);
                    break;
                }
            } else {
                func_020262a0(aRecord, 0x100, data_ov008_02090960, pLabel);
            }
            func_020302ec(pMenu->surface, 6, nY, COLOUR_RECORD, COLOUR_RECORD, aRecord);
            nHeight += func_ov008_02074b10(aRecord);
            nHeight += Ov008_DrawInfoLine(pMenu, nY + LINE_STEP, data_ov008_0209092c);
            nY += 2 * LINE_STEP;
        }
    }
    nHeight += Ov008_DrawInfoLine(pMenu, nY, pDesc);
    pMenu->nTextHeight = nHeight;
}
