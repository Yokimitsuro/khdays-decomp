/* func_ov023_02083f1c -- Ov023_LoadSecondaryScript: stream a world's event text into the
 * scene's secondary script (+0x1511c).  Takes a copy of the second world-code table
 * (data_ov023_02089d44: "TT", "AW", "HE", ...), saves the two 0x104-byte staging blocks at
 * +0x1d6e0 and +0x1d8e8, opens "ev/EV_DP.p2" for world -1 or "ev/EV_%s.p2" for the world's
 * code (02024ee8, heap 0xf), encodes the argument's line (020200b4 on its +2) and streams the
 * container into the script (02020c7c with the packed descriptor, the argument as source and
 * the staging tail at +0x1d6b0), closes the container (02024fd4), restores the two blocks and
 * marks the secondary script running (+0x875e8). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov023Scene {
    u8   pad_00000[0x1511c];
    u32  script2[(0x1d6b0 - 0x1511c) / 4]; /* 0x1511c: the secondary script stream */
    u8  *pStagingTail;        /* 0x1d6b0 */
    u8   pad_1d6b4[0x1d6e0 - 0x1d6b4];
    u8   aStaging1[0x104];    /* 0x1d6e0 */
    u8   pad_1d7e4[0x1d8e8 - 0x1d7e4];
    u8   aStaging2[0x104];    /* 0x1d8e8 */
    u8   pad_1d9ec[0x875e8 - 0x1d9ec];
    int  nScript2Running;     /* 0x875e8 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

typedef struct Ov023WorldTable {
    const char *apCode[12];   /* 0x00 */
} Ov023WorldTable;

extern void  MI_CpuCopy8(const void *pSrc, void *pDst, u32 nSize);
extern void  OS_SPrintf(char *pBuffer, const char *pFormat, ...);
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open a text container */
extern u32   func_020200b4(void *pLine);                            /* encode a line */
extern void  func_02020c7c(u32 *pDst, u32 nDescriptor, void *pSrc, u8 **ppStaging); /* stream into a script */
extern void  func_02024fd4(void *pContainer);                       /* close a text container */
extern Ov023SceneRoot data_ov023_0208a784;
extern const Ov023WorldTable data_ov023_02089d44;                   /* world codes by world index */
extern char  data_ov023_0208a0b8[];                                 /* "ev/EV_DP.p2" */
extern char  data_ov023_0208a068[];                                 /* "ev/EV_%s.p2" */

void func_ov023_02083f1c(int nWorld, u8 *pLine)
{
    u8   aSaved2[0x104];
    u8   aSaved1[0x104];
    char szPath[0x20];
    Ov023WorldTable world;
    void *pText;

    world = data_ov023_02089d44;
    MI_CpuCopy8(data_ov023_0208a784.pScene->aStaging1, aSaved1, 0x104);
    MI_CpuCopy8(data_ov023_0208a784.pScene->aStaging2, aSaved2, 0x104);
    if (nWorld == -1) {
        OS_SPrintf(szPath, data_ov023_0208a0b8);
    } else {
        OS_SPrintf(szPath, data_ov023_0208a068, world.apCode[nWorld]);
    }
    pText = func_02024ee8(szPath, 0xf);
    func_02020c7c(data_ov023_0208a784.pScene->script2,
                  ((((u32)pText + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (func_020200b4(pLine + 2) & (0xfffffc >> 15)),
                  pLine, &data_ov023_0208a784.pScene->pStagingTail);
    func_02024fd4(pText);
    MI_CpuCopy8(aSaved1, data_ov023_0208a784.pScene->aStaging1, 0x104);
    MI_CpuCopy8(aSaved2, data_ov023_0208a784.pScene->aStaging2, 0x104);
    data_ov023_0208a784.pScene->nScript2Running = 1;
}
