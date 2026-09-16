/* func_ov015_02082380 -- Ov015_ScriptOpSpawnPickup: script op that reads a slot, a kind,
 * an index, two packed GameState field / bit words (pc + 0x1c and pc + 0x24), the
 * position (three fx32), an angle in degrees (turned into a 16-bit facing by
 * angle * 0x10000 / 360), a link-key count and that many link keys (from pc + 0x50, one
 * operand each), then spawns a pickup piece (020801c8) on the slot's class table (ov002
 * 02076468).  Always consumes the op (1).
 * Codegen: the operand pointer is advanced past the fixed operands before the key count is
 * read (through a pointer taken first) and then walks the keys; the packed words are split
 * into u16 / u8 locals as they are read; the vectors are declared before the scalars. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov015_020801c8(void *pClass, int nSlot, int nKind, u16 nField, u8 nBit, u16 nField2, u8 nBit2, VecFx32 *pPos, short nFacing, int nKeys, short *aKey);

int func_ov015_02082380(int vm, u16 *pc)
{
    VecFx32 position;
    short aKey[2];
    short nFacing;
    u16 nField;
    u8 nBit;
    u16 nField2;
    u8 nBit2;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    int nKeys;
    u32 nRaw;
    int i;
    u16 *pKey;
    short *pDst;

    nSlot = func_02021980(vm, pc);
    nKind = func_02021980(vm, pc + 4);
    nIndex = func_02021980(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nRaw = *(u32 *)(pc + 0x12);
    nField2 = nRaw;
    nBit2 = (u16)(nRaw >> 16);
    position.x = func_02021994(vm, pc + 0x14);
    position.y = func_02021994(vm, pc + 0x18);
    position.z = func_02021994(vm, pc + 0x1c);
    nFacing = (short)func_02020400(func_02021980(vm, pc + 0x20) << 16, 360);
    pKey = pc + 0x24;
    pc += 0x28;
    nKeys = func_02021980(vm, pKey);
    i = 0;
    if (nKeys > 0) {
        pDst = aKey;
        do {
            *pDst = func_02021980(vm, pc);
            i++;
            pc += 4;
            pDst++;
        } while (i < nKeys);
    }
    func_ov015_020801c8(func_ov002_02076468(nSlot), nKind & 0xffff, nIndex & 0xffff, nField, nBit, nField2, nBit2, &position, nFacing, nKeys, aKey);
    return 1;
}
