/* Ov016_ScriptOpCreateKickable -- Ov016_ScriptOpCreateKickable: script op that reads the position (three
 * fx32 at pc + 0x20), a packed GameState field / bit word (pc + 0x1c), an angle in degrees
 * (facing = angle * 0x10000 / 360) and, when the halfword at pc + 0x40 is 4, a second
 * packed field / bit word (pc + 0x44; field 0xffff / bit 0 by default), then the slot's class
 * table (ov002 02076468 on the first operand), the kind and the index, and creates a kickable
 * piece (Ov016_KickableCreate 02082020).  Always consumes the op (1). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int   ScriptVm_ReadOperandInt(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *Ov002_GetModuleSlot(int nSlot);            /* class table of a slot */
extern void *Ov016_KickableCreate(void *pClass, u16 nSlot, u16 nRoom, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, u16 nField2, u8 nBit2);   /* Ov016_KickableCreate */

int Ov016_ScriptOpCreateKickable(int vm, u16 *pc)
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

    position.x = ScriptVm_ReadOperandFx32(vm, pc + 0x10);
    position.y = ScriptVm_ReadOperandFx32(vm, pc + 0x14);
    position.z = ScriptVm_ReadOperandFx32(vm, pc + 0x18);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nFacing = (u16)func_02020400(ScriptVm_ReadOperandInt(vm, pc + 0x1c) << 16, 360);
    nBit2 = 0;
    nField2 = 0xffff;
    if (((short *)pc)[0x20] == 4) {
        nRaw = *(u32 *)(pc + 0x22);
        nField2 = nRaw;
        nBit2 = (u16)(nRaw >> 16);
    }
    pClass = Ov002_GetModuleSlot(ScriptVm_ReadOperandInt(vm, pc));
    nKind = ScriptVm_ReadOperandInt(vm, pc + 4);
    pc += 8;
    nIndex = ScriptVm_ReadOperandInt(vm, pc);
    Ov016_KickableCreate(pClass, nKind & 0xffff, nIndex & 0xffff, &position, (short)nFacing, nField, nBit, nField2, nBit2);
    return 1;
}
