/* func_ov023_0208405c -- Ov023_CmdLoadActor: script command that loads an actor's resource
 * group.  Operand 0 is the actor id, operand 1 the group's name (resolved against the
 * context's table at +0x128 by 02020af0).  If the entity manager (data_0204c208) already holds
 * a block for that id, its record (+4 + id * 8, 0202b064) and block (+0x44 + id * 4) are
 * released first; then the group is registered under the id (0202b820).  For actor 0 the group
 * resources are requested (Ov023_RequestGroupResources 02083c14, with the extra set when game
 * field 0x2480 reads 1) and the camera distance set (02033f50): 0xa000 or operand 2 when
 * present, five times that, 0x7f. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023EntityManager {
    unsigned int nCount;      /* 0x0000 */
    u16  aRecord[8][4];       /* 0x0004 */
    void *apBlock[8];         /* 0x0044 */
} Ov023EntityManager;

typedef struct Ov023ScriptCtx {
    u8   pad_000[0x128];
    void *pTable;             /* 0x128 */
} Ov023ScriptCtx;

typedef struct Ov023Operand {
    s16  nType;               /* 0x00 */
    u8   pad_02[6];
} Ov023Operand;               /* 0x08 */

extern int   func_02021980(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandInt */
extern char *func_02021948(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandString */
extern int   func_02021994(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand);   /* ScriptVm_ReadOperandFx32 */
extern void  func_0202b064(u16 *pRecord);                           /* release an entity record */
extern void  NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern char *func_02020af0(void *pTable, char *pszName);            /* resolve a name */
extern void  func_0202b820(u16 nId, char *pszGroup);                /* register an entity group */
extern int   func_020235d0(int nField, int nArg);                   /* GameState_GetField */
extern void  func_ov023_02083c14(int nGroup, int bExtra);           /* Ov023_RequestGroupResources */
extern void  func_02033f50(int nNear, int nFar, int nArg);          /* set the camera distance */
extern Ov023EntityManager *data_0204c208;

int func_ov023_0208405c(Ov023ScriptCtx *pCtx, Ov023Operand *pOperand)
{
    int nId;
    char *pszGroup;
    int nDistance;

    nId = func_02021980(pCtx, pOperand);
    pszGroup = func_02021948(pCtx, pOperand + 1);
    nDistance = 0xa000;
    if (data_0204c208->apBlock[nId] != 0) {
        func_0202b064(data_0204c208->aRecord[nId]);
        NNSi_FndFreeFromDefaultHeap(data_0204c208->apBlock[nId]);
    }
    pszGroup = func_02020af0(pCtx->pTable, pszGroup);
    func_0202b820((u16)nId, pszGroup);
    if (nId == 0) {
        if (func_020235d0(0x2480, 1) == 1) {
            func_ov023_02083c14(nId, 1);
        } else {
            func_ov023_02083c14(nId, 0);
        }
        if (pOperand[2].nType != 0) {
            nDistance = func_02021994(pCtx, pOperand + 2);
        }
        func_02033f50(nDistance, nDistance * 5, 0x7f);
    }
    return 1;
}
