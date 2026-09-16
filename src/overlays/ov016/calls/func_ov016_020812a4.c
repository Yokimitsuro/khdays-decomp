/* func_ov016_020812a4 -- Ov016_ScriptOpCreateBreakable: script op that reads a slot, a kind and
 * an index, a packed GameState field / bit word (pc + 0x1c), the position (three fx32), an
 * angle in degrees (turned into a 16-bit facing by angle * 0x10000 / 360) and the drop key
 * and argument, then creates a breakable piece (Ov016_BreakableCreate 02080ec0) on the
 * slot's class table (ov002 02076468).  Always consumes the op (1). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov016_02080ec0(void *pClass, u16 nSlot, u16 nBucket, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, int nDropKey, int nDropArg);   /* Ov016_BreakableCreate */

int func_ov016_020812a4(int vm, u16 *pc)
{
    VecFx32 position;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nAngle;
    int nDropKey;
    int nDropArg;
    void *pClass;

    nSlot = func_02021980(vm, pc);
    nKind = func_02021980(vm, pc + 4);
    nIndex = func_02021980(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    position.x = func_02021994(vm, pc + 0x10);
    position.y = func_02021994(vm, pc + 0x14);
    position.z = func_02021994(vm, pc + 0x18);
    nAngle = func_02021980(vm, pc + 0x1c);
    nDropKey = func_02021980(vm, pc + 0x20);
    pc += 0x24;
    nDropArg = func_02021980(vm, pc);
    pClass = func_ov002_02076468(nSlot);
    func_ov016_02080ec0(pClass, nKind & 0xffff, nIndex & 0xffff, &position,
                        (short)func_02020400(nAngle << 16, 360), (u16)nRaw, (u16)(nRaw >> 16), nDropKey, nDropArg);
    return 1;
}
