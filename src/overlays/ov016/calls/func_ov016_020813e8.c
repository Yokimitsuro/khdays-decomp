/* func_ov016_020813e8 -- Ov016_ScriptOpCreateKickable: script op that reads the position (three
 * fx32 at pc + 0x20), a packed GameState field / bit word (pc + 0x1c), an angle in degrees
 * (facing = angle * 0x10000 / 360) and, when the halfword at pc + 0x40 is 4, a second
 * packed field / bit word (pc + 0x44; field 0xffff / bit 0 by default), then the slot's class
 * table (ov002 02076468 on the first operand), the kind and the index, and creates a kickable
 * piece (Ov016_KickableCreate 02082020).  Always consumes the op (1). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov016_02082020(void *pClass, u16 nSlot, u16 nBucket, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, u16 nField2, u8 nBit2);   /* Ov016_KickableCreate */

int func_ov016_020813e8(int vm, u16 *pc)
{
    VecFx32 position;
    u32 nKind;
    u32 nIndex;
    void *pClass;
    u16 nField;
    u8 nBit;
    u16 nFacing;
    u32 nRaw;
    u16 nField2;
    u8 nBit2;

    position.x = func_02021994(vm, pc + 0x10);
    position.y = func_02021994(vm, pc + 0x14);
    position.z = func_02021994(vm, pc + 0x18);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nFacing = (u16)func_02020400(func_02021980(vm, pc + 0x1c) << 16, 360);
    nBit2 = 0;
    nField2 = 0xffff;
    if (((short *)pc)[0x20] == 4) {
        nRaw = *(u32 *)(pc + 0x22);
        nField2 = nRaw;
        nBit2 = (u16)(nRaw >> 16);
    }
    pClass = func_ov002_02076468(func_02021980(vm, pc));
    nKind = func_02021980(vm, pc + 4);
    pc += 8;
    nIndex = func_02021980(vm, pc);
    func_ov016_02082020(pClass, nKind & 0xffff, nIndex & 0xffff, &position, (short)nFacing, nField, nBit, nField2, nBit2);
    return 1;
}
