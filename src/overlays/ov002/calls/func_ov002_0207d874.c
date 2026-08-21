typedef unsigned char u8;

typedef struct {
    int x, y, z;
} VecFx32;

/* One operand of a script command: a tag saying how the value is fetched and
 * the word that carries either the value itself or the reference to it. */
typedef struct {
    short kind;
    short pad;
    int   value;
} OperandSlot;

/* The packet published as session command 0x10.
 *
 * The two bitfields share the byte at +1 and are written at different points -
 * the style before the position, the slot after it - so each write is a
 * read-modify-write of that same byte, masking 0xfc and 3 respectively. */
typedef struct {
    u8 nKind;                       /* +0x00, not written by the publisher */
    u8 nSlot : 2;                   /* +0x01 bits 0-1 */
    u8 nStyle : 6;                  /* +0x01 bits 2-7 */
    u8 nEntry;                      /* +0x02 */
    u8 nKeyIndex;                   /* +0x03 */
    u8 nSeed;                       /* +0x04 */
    u8 pad05[3];
    VecFx32 vPos;                   /* +0x08 */
} Ov002SessionSpawnCmd;             /* 0x14 */

extern int func_02021980(void *pContext, OperandSlot *pOperand);
extern int func_02021994(void *pContext, OperandSlot *pOperand);
extern short func_02030788(void);
extern int func_ov002_02077b30(void);
extern int func_ov002_0206d144(int nKey);
extern int func_020307f4(int nRange);
extern void func_ov002_0206fb84(int nKind, void *pCmd);

/* Script command: read a spawn request out of the command's operands and, on
 * the session host only, publish it as session command 0x10.
 *
 * Seven operands: one read purely for its side effect, a key to look up, a
 * style, three fixed point coordinates and a slot. A client reads all of them
 * too and then drops the request, so both sides consume the same operands.
 *
 * Always returns 1.
 */
int func_ov002_0207d874(void *pContext, OperandSlot *pArgs)
{
    VecFx32 vPos;
    Ov002SessionSpawnCmd cmd;
    int nKey;
    int nStyle;
    int nSlot;

    func_02021980(pContext, &pArgs[0]);
    nKey = func_02021980(pContext, &pArgs[1]);
    nStyle = func_02021980(pContext, &pArgs[2]);
    vPos.x = func_02021994(pContext, &pArgs[3]);
    vPos.y = func_02021994(pContext, &pArgs[4]);
    vPos.z = func_02021994(pContext, &pArgs[5]);
    pArgs += 6;
    nSlot = func_02021980(pContext, pArgs);

    if (func_02030788() == 0) {
        cmd.nEntry = (u8)func_ov002_02077b30();
        cmd.nKeyIndex = (u8)func_ov002_0206d144((short)nKey);
        cmd.nStyle = (u8)nStyle;
        cmd.vPos = vPos;
        cmd.nSlot = (u8)nSlot;
        cmd.nSeed = (u8)func_020307f4(0x100);
        func_ov002_0206fb84(0x10, &cmd);
    }
    return 1;
}
