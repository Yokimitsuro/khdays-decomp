/* func_ov023_02082ee4 -- Ov023_LoadScripts: state that loads the event scripts.  Points the
 * script cursor (+0x1daf0) at the scene's script block (+0x1dc54), takes a copy of the
 * world-code table (data_ov023_02089d14: "TT", "AW", "HE", ...), builds the current text line
 * (ov002 0206d834 into a stack buffer) and keeps the sub-object (ov002 0206d86c, +0x1db3c) and
 * the ov002 handle (02076890, +0x1db40); opens the shared event text "ev/EV_S.p2" (+0x1db4c,
 * 02024ee8 heap 0xf) and, when the scene's world (+0x875e0) has a code, the world's own
 * "ev/EV_%s.p2" (+0x1db50).  Then the line is encoded against the sub-object (02024fe8) and
 * streamed into the message block at +0x4b88 (02020c7c with the packed descriptor, the scene
 * name +0x87598 as source and the staging tail +0x1d6b0); the word at +0x5118 becomes 0x10000
 * and the state moves on to Ov023_SceneReady (0208337c). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov023Scene {
    u8   pad_00000[0x4b88];
    u32  message[(0x5118 - 0x4b88) / 4]; /* 0x04b88 */
    int  nWord5118;           /* 0x05118 */
    u8   pad_0511c[0x1d6b0 - 0x511c];
    u8  *pStagingTail;        /* 0x1d6b0 */
    u8   pad_1d6b4[0x1daf0 - 0x1d6b4];
    u8  *pScriptCursor;       /* 0x1daf0 */
    u8   pad_1daf4[0x1db3c - 0x1daf4];
    int  nSubObject;          /* 0x1db3c */
    int  nHandle;             /* 0x1db40 */
    u8   pad_1db44[8];
    void *pSharedText;        /* 0x1db4c: ev/EV_S.p2 */
    void *pWorldText;         /* 0x1db50: ev/EV_<world>.p2 */
    u8   pad_1db54[0x1dc54 - 0x1db54];
    u8   script[0x87598 - 0x1dc54]; /* 0x1dc54 */
    char szName[0x875e0 - 0x87598]; /* 0x87598 */
    int  nWorld;              /* 0x875e0 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

typedef struct Ov023WorldTable {
    const char *apCode[12];   /* 0x00 */
} Ov023WorldTable;

extern void  func_ov002_0206d834(int nLine, char *pOut);            /* build a text line */
extern int   func_ov002_0206d86c(void);                             /* the text sub-object */
extern int   func_ov002_02076890(void);
extern void  OS_SPrintf(char *pBuffer, const char *pFormat, ...);
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open a text container */
extern u32   func_02024fe8(int nSubObject, char *pLine);            /* encode a line */
extern void  func_02020c7c(u32 *pDst, u32 nDescriptor, void *pSrc, u8 **ppStaging); /* stream into a message block */
extern void *func_ov023_0208337c(void);                             /* Ov023_SceneReady */
extern Ov023SceneRoot data_ov023_0208a784;
extern const Ov023WorldTable data_ov023_02089d14;                   /* world codes by world index */
extern char  data_ov023_0208a05c[];                                 /* "ev/EV_S.p2" */
extern char  data_ov023_0208a068[];                                 /* "ev/EV_%s.p2" */

void *func_ov023_02082ee4(void)
{
    char szLine[0x80];
    char szPath[0x20];
    Ov023WorldTable world;
    Ov023Scene *pScene;
    int nSubObject;
    u32 nEncoded;

    data_ov023_0208a784.pScene->pScriptCursor = data_ov023_0208a784.pScene->script;
    world = data_ov023_02089d14;
    func_ov002_0206d834(0, szLine);
    data_ov023_0208a784.pScene->nSubObject = func_ov002_0206d86c();
    data_ov023_0208a784.pScene->nHandle = func_ov002_02076890();
    OS_SPrintf(szPath, data_ov023_0208a05c);
    data_ov023_0208a784.pScene->pSharedText = func_02024ee8(szPath, 0xf);
    if (world.apCode[data_ov023_0208a784.pScene->nWorld] != 0) {
        OS_SPrintf(szPath, data_ov023_0208a068, world.apCode[data_ov023_0208a784.pScene->nWorld]);
        data_ov023_0208a784.pScene->pWorldText = func_02024ee8(szPath, 0xf);
    }
    pScene = data_ov023_0208a784.pScene;
    nSubObject = func_ov002_0206d86c();
    nEncoded = func_02024fe8(func_ov002_0206d86c(), szLine);
    func_02020c7c(data_ov023_0208a784.pScene->message,
                  (((nSubObject + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (nEncoded & (0xfffffc >> 15)),
                  pScene->szName, &pScene->pStagingTail);
    data_ov023_0208a784.pScene->nWord5118 = 0x10000;
    return func_ov023_0208337c;
}
